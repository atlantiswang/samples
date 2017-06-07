// KSPDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <bcrypt.h>
#include <ksp_ext.h>

#define ES_KEY_STORAGE_PROVIDER	KSP_NAME
#define NT_SUCCESS(Status)		(((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL		((NTSTATUS)0xC0000001L)

// This class is used to free resources(key,provider,buffer...)
class NCryptProviderHolder
{
public:
	NCryptProviderHolder(NCRYPT_PROV_HANDLE hProv, NCRYPT_KEY_HANDLE hKey = NULL, PVOID pRes = NULL, BOOL bDelKey = FALSE) :
	  m_hProv(hProv), m_hKey(hKey), m_pRes(pRes), m_bDelKey(bDelKey)
	  {

	  }

	  ~NCryptProviderHolder()
	  {
		  SECURITY_STATUS Status  = ERROR_SUCCESS;

		  if (NULL != m_pRes)
		  {
			  Status = NCryptFreeBuffer(m_pRes);
			  if (FAILED(Status))
			  {
				  printf("ERROR: NCryptFreeBuffer : 0x%x\n", Status);
				  //exit(0);
			  }
			  printf("OK: NCryptFreeBuffer : 0x%x\n", Status);
			  m_pRes = NULL;
		  }

		  if (m_bDelKey && NULL != m_hKey)
		  {
			  Status = NCryptDeleteKey(m_hKey, 0);
			  if (FAILED(Status))
			  {
				  printf("ERROR: NCryptDeleteKey : 0x%x\n", Status);
				  //exit(0);
			  }
			  printf("OK: NCryptDeleteKey : 0x%x\n", Status);
			  m_hKey = NULL;
		  }
		  else if (NULL != m_hKey)
		  {
			  Status = NCryptFreeObject(m_hKey);
			  if (FAILED(Status))
			  {
				  printf("ERROR: NCryptFreeObject(key) : 0x%x\n", Status);
				  //exit(0);
			  }
			  printf("OK: NCryptFreeObject(key) : 0x%x\n", Status);
			  m_hProv = NULL;
		  }

		  if (NULL != m_hProv)
		  {
			  Status = NCryptFreeObject(m_hProv);
			  if (FAILED(Status))
			  {
				  printf("ERROR: NCryptFreeObject(Prov) : 0x%x\n", Status);
				  //exit(0);
			  }
			  printf("OK: NCryptFreeObject(Prov) : 0x%x\n", Status);
			  m_hProv = NULL;
		  }
	  }

private:
	NCRYPT_PROV_HANDLE m_hProv;
	NCRYPT_KEY_HANDLE m_hKey;
	PVOID m_pRes;
	BOOL m_bDelKey;
};

int _tmain(int argc, _TCHAR* argv[])
{
	NCRYPT_PROV_HANDLE hProvider = 0;
	NCRYPT_KEY_HANDLE hKey = 0;

	BYTE rgbHash[20] = {0};
	DWORD cbSignature = 0;
	DWORD i = 0;
	BCRYPT_PKCS1_PADDING_INFO PKCS1PaddingInfo = {0};
	VOID *pPaddingInfo = NULL;
	DWORD dwKeyLen = 0;

	typedef struct _KEY_PARAM_
	{
		wstring strName;
		DWORD LegacySpec;
		DWORD dwBitLen;
	}KEY_PARAM;

	KEY_PARAM KeyParams[] = {
		{L"MyKey1", AT_KEYEXCHANGE, 1024},
		{L"MyKey1", AT_KEYEXCHANGE, 1024},
		{L"MyKey2", AT_SIGNATURE,   1024},

	};

	printf("======= Entersafe KSP Test Demo =======\n");

	// ========================================================================================================
	// Open the KSP
	SECURITY_STATUS Status  = ERROR_SUCCESS;
	Status = NCryptOpenStorageProvider(&hProvider,
		ES_KEY_STORAGE_PROVIDER,
		0);
	if (FAILED(Status))
	{
		printf("ERROR: NCryptOpenStorageProvider : %s  0x%x\n", ES_KEY_STORAGE_PROVIDER, Status);
		return 0;
	}
	wprintf(L"OK: NCryptOpenStorageProvider : %s 0x%x\n", ES_KEY_STORAGE_PROVIDER, Status);
	NCryptProviderHolder ProHolder(hProvider); // Freeing hProvider automatically.

	// Enum algorithm which the ksp support.
	DWORD dwAlgCount = 0;
	NCryptAlgorithmName *pAlgList = NULL;
	Status = NCryptEnumAlgorithms(hProvider, 
		NCRYPT_ASYMMETRIC_ENCRYPTION_OPERATION,
		&dwAlgCount,
		&pAlgList,
		0);
	if (FAILED(Status))
	{
		printf("ERROR: NCryptEnumAlgorithms : 0x%x\n", Status);
		return 0;
	}
	wprintf(L"OK: NCryptEnumAlgorithms : 0x%x, %s support:\n", Status, ES_KEY_STORAGE_PROVIDER);

	DWORD nAlgIndex = 0;
	NCryptAlgorithmName *pTmpAlgList = pAlgList;
	for (nAlgIndex = 0; nAlgIndex < dwAlgCount; nAlgIndex++)
	{
		wprintf(L"%d Algorithm Name : %s\n", nAlgIndex + 1, pTmpAlgList->pszName);
		pTmpAlgList++;
	}

	// We need to use NCryptFreeBuffer to free algorithm lists.
	Status = NCryptFreeBuffer(pAlgList);
	if (FAILED(Status))
		printf("ERROR: NCryptFreeBuffer(Algorithm Name) : 0x%x\n", Status);
	printf("OK: NCryptFreeBuffer(Algorithm Name) : 0x%x\n", Status);
	pAlgList = NULL;

	// ========================================================================================================
	printf("\n======= Enum keys and delete them =======\n");
	NCryptKeyName *pKeyName = NULL;
	PVOID pState = NULL;

	do 
	{
		// Enum keys in the ksp.
		Status = NCryptEnumKeys(hProvider, 0, &pKeyName, &pState, 0);
		if (Status == NTE_NO_MORE_ITEMS)
			break;

		if (Status != ERROR_SUCCESS && Status != ERROR_SUCCESS)
		{
			printf("ERROR: NCryptEnumKeys : 0x%x\n", Status);
			return 0;
		}
		printf("OK: NCryptEnumKeys : 0x%x\n", Status);

		{
			NCryptProviderHolder NameHolder(NULL, NULL, pKeyName);
			Status = NCryptOpenKey(
				hProvider,
				&hKey,
				pKeyName->pszName,
				pKeyName->dwLegacyKeySpec,
				0);
			if(FAILED(Status))
			{
				wprintf(L"ERROR: NCryptOpenKey(%s): 0x%x\n", pKeyName->pszName, Status);
				continue;
			}

			wprintf(L"OK: NCryptOpenKey : 0x%x, Key Name: %s\n", Status, pKeyName->pszName);

			wprintf(L"The Key %s will be delete\n", pKeyName->pszName);
			NCryptProviderHolder KeyHolder(NULL, hKey, NULL, TRUE); // Deleting key autimatically.
		}

	} while (1);

	// ========================================================================================================
	printf("\n======= Create new keys =======\n");
	for (int i = 0; i < sizeof(KeyParams)/sizeof(KEY_PARAM); i++)
	{
		wprintf(L"==== %d Create %s key ====\n", i, 0 == KeyParams[i].strName.length() ? L"Empty Name" : KeyParams[i].strName.c_str());
		Status = NCryptCreatePersistedKey(hProvider,
			&hKey,
			NCRYPT_RSA_ALGORITHM,
			0 == KeyParams[i].strName.length() ? NULL : KeyParams[i].strName.c_str(),
			KeyParams[i].LegacySpec,
			0);
		if (FAILED(Status))
		{
			printf("ERROR: NCryptCreatePersistedKey : 0x%x\n", Status);
			continue;
		}
		printf("OK: NCryptCreatePersistedKey : 0x%x\n", Status);

		NCryptProviderHolder KeyHolder(NULL, hKey);
		Status = NCryptSetProperty(hKey,
			NCRYPT_LENGTH_PROPERTY,
			(PBYTE)(&(KeyParams[i].dwBitLen)),
			sizeof(DWORD),
			0);
		if (FAILED(Status))
		{
			printf("ERROR: NCryptSetProperty(HWND) : 0x%x\n", Status);
			continue;
		}
		printf("OK: NCryptSetProperty : 0x%x\n", Status);

		printf("Call NCryptFinalizeKey to generate key ...\n");
		Status = NCryptFinalizeKey(hKey, 0);
		if (FAILED(Status))
		{
			printf("ERROR: NCryptFinalizeKey : 0x%x\n", Status);
			continue;
		}
		printf("OK: NCryptFinalizeKey : 0x%x\n", Status);

	}

	// ========================================================================================================
	printf("\n======= Enum keys and do sign/verify/export/encrypt/decrypt operations =======\n");
	pKeyName = NULL;
	pState = NULL;
	do 
	{
		Status = NCryptEnumKeys(hProvider, 0, &pKeyName, &pState, 0);
		if (Status == NTE_NO_MORE_ITEMS)
			break;

		if (Status != ERROR_SUCCESS && Status != ERROR_SUCCESS)
		{
			printf("ERROR: NCryptEnumKeys : 0x%x\n", Status);
			return 0;
		}
		printf("OK: NCryptEnumKeys : 0x%x\n", Status);

		{
			NCryptProviderHolder NameHolder(NULL, NULL, pKeyName);
			Status = NCryptOpenKey(
				hProvider,
				&hKey,
				pKeyName->pszName,
				pKeyName->dwLegacyKeySpec,
				0);
			if(FAILED(Status))
			{
				wprintf(L"ERROR: NCryptOpenKey(%s): 0x%x\n", pKeyName->pszName, Status);
				continue;
			}
			NCryptProviderHolder KeyHolder(NULL, hKey);
			wprintf(L"OK: NCryptOpenKey : 0x%x, Key Name: %s\n", Status, pKeyName->pszName);
			wprintf(L"Using key : %s to do operations(sign/verify/export/ecrypt/decrypt)\n", pKeyName->pszName);

			// 			for(i = 0; i < sizeof(rgbHash); i++)
			// 			{
			// 				rgbHash[i] = (BYTE)(i + 1);
			// 			}

			// Open a hash algorithm provider and do hash operation
			// ========================================================================================================
			printf("======= Do hash operations =======\n");
			{
				BCRYPT_ALG_HANDLE       hAlg            = NULL;
				BCRYPT_HASH_HANDLE      hHash           = NULL;
				NTSTATUS                status          = STATUS_UNSUCCESSFUL;
				DWORD                   cbData          = 0,
					cbHash          = 0,
					cbHashObject    = 0;
				PBYTE                   pbHashObject    = NULL;

				static const BYTE rgbMsg[] = 
				{
					0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68
				};

				//open an algorithm handle
				if(!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
					&hAlg,
					BCRYPT_SHA1_ALGORITHM,
					NULL, // We can pass third-party name here.
					0)))
				{
					wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
					continue;
				}
				printf("BCryptOpenAlgorithmProvider(BCRYPT_SHA1_ALGORITHM) OK\n");

				if(!NT_SUCCESS(status = BCryptGetProperty(
					hAlg, 
					BCRYPT_OBJECT_LENGTH, 
					(PBYTE)&cbHashObject, 
					sizeof(DWORD), 
					&cbData, 
					0)))
				{
					wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
					BCryptCloseAlgorithmProvider(hAlg,0);
					continue;
				}
				vector<BYTE> vHashObject(cbHashObject, 0);

				if(!NT_SUCCESS(status = BCryptGetProperty(
					hAlg, 
					BCRYPT_HASH_LENGTH, 
					(PBYTE)&cbHash, 
					sizeof(DWORD), 
					&cbData, 
					0)))
				{
					wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
					BCryptCloseAlgorithmProvider(hAlg,0);
					continue;
				}
				vector<BYTE> vHashData(cbHash, 0);
				if (20 != vHashData.size())
				{
					printf("Wrong hash length!\n");
					continue;
				}

				//create a hash
				if(!NT_SUCCESS(status = BCryptCreateHash(
					hAlg, 
					&hHash, 
					&vHashObject[0], 
					cbHashObject, 
					NULL, 
					0, 
					0)))
				{
					wprintf(L"**** Error 0x%x returned by BCryptCreateHash\n", status);
					BCryptCloseAlgorithmProvider(hAlg,0);
					continue;
				}
				printf("BCryptCreateHash OK\n");


				//hash some data
				if(!NT_SUCCESS(status = BCryptHashData(
					hHash,
					(PBYTE)rgbMsg,
					sizeof(rgbMsg),
					0)))
				{
					wprintf(L"**** Error 0x%x returned by BCryptHashData\n", status);
					BCryptDestroyHash(hHash);
					BCryptCloseAlgorithmProvider(hAlg,0);
					continue;
				}
				printf("BCryptHashData OK\n");

				//close the hash
				if(!NT_SUCCESS(status = BCryptFinishHash(
					hHash, 
					&vHashData[0], 
					cbHash, 
					0)))
				{
					wprintf(L"**** Error 0x%x returned by BCryptFinishHash\n", status);
					BCryptDestroyHash(hHash);
					BCryptCloseAlgorithmProvider(hAlg,0);
					continue;
				}
				printf("BCryptFinishHash OK\n");

				memcpy(rgbHash, &vHashData[0], sizeof(rgbHash)/sizeof(BYTE));
			}

			PKCS1PaddingInfo.pszAlgId = NCRYPT_SHA1_ALGORITHM;
			pPaddingInfo = &PKCS1PaddingInfo;

			Status = NCryptSignHash(hKey,
				pPaddingInfo,
				rgbHash,
				sizeof(rgbHash),
				NULL,
				0,
				&cbSignature,
				NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptSignHash(size) : 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptSignHash(size) : 0x%x\n", Status);

			vector<BYTE> pbSignature(cbSignature, 0);
			Status = NCryptSignHash(hKey,
				pPaddingInfo,
				rgbHash,
				sizeof(rgbHash),
				&pbSignature[0],
				cbSignature,
				&cbSignature,
				NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptSignHash() : 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptSignHash() : 0x%x\n", Status);

			Status = NCryptVerifySignature(hKey,
				pPaddingInfo,
				rgbHash,
				sizeof(rgbHash),
				&pbSignature[0],
				cbSignature,
				NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptVerifySignature() : 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptVerifySignature() : 0x%x\n", Status);


			DWORD dwPubBlobLen = 0;
			Status = NCryptExportKey(hKey, NULL, BCRYPT_RSAPUBLIC_BLOB, 
				NULL, NULL, 0, &dwPubBlobLen, 0);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptExportKey(size) BCRYPT_RSAPUBLIC_BLOB : 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptExportKey(size) : 0x%x\n", Status);

			vector<BYTE> pbPubBlob(dwPubBlobLen, 0);
			Status = NCryptExportKey(hKey, NULL, BCRYPT_RSAPUBLIC_BLOB, 
				NULL, &pbPubBlob[0], dwPubBlobLen, &dwPubBlobLen, 0);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptExportKey() BCRYPT_RSAPUBLIC_BLOB: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptExportKey() BCRYPT_RSAPUBLIC_BLOB: 0x%x\n", Status);

			dwPubBlobLen = 0;
			Status = NCryptExportKey(hKey, NULL, LEGACY_RSAPUBLIC_BLOB, 
				NULL, NULL, 0, &dwPubBlobLen, 0);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptExportKey(size) LEGACY_RSAPUBLIC_BLOB: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptExportKey(size) LEGACY_RSAPUBLIC_BLOB: 0x%x\n", Status);

			vector<BYTE> pbPubBlobLegacy(dwPubBlobLen, 0);
			Status = NCryptExportKey(hKey, NULL, LEGACY_RSAPUBLIC_BLOB, 
				NULL, &pbPubBlobLegacy[0], dwPubBlobLen, &dwPubBlobLen, 0);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptExportKey() LEGACY_RSAPUBLIC_BLOB: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptExportKey() LEGACY_RSAPUBLIC_BLOB: 0x%x\n", Status);

			DWORD dwEDeLen = 0;
			Status = NCryptEncrypt(hKey, rgbHash, sizeof(rgbHash), NULL, NULL, 0, &dwEDeLen, NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptEncrypt(size) NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptEncrypt(size) NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);

			vector<BYTE> edBuf(dwEDeLen, 0);
			Status = NCryptEncrypt(hKey, rgbHash, sizeof(rgbHash), NULL, &edBuf[0], dwEDeLen, &dwEDeLen, NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptEncrypt() NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptEncrypt() NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);

			dwEDeLen = 0;
			Status = NCryptDecrypt(hKey, &edBuf[0], static_cast<DWORD>(edBuf.size()), NULL, NULL, 0, &dwEDeLen, NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptDecrypt(size) NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptDecrypt(size) NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);

			vector<BYTE> deBuf(dwEDeLen, 0);
			Status = NCryptDecrypt(hKey, &edBuf[0], static_cast<DWORD>(edBuf.size()), NULL, &deBuf[0], dwEDeLen, &dwEDeLen, NCRYPT_PAD_PKCS1_FLAG);
			if (FAILED(Status))
			{
				printf("ERROR: NCryptDecrypt() NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);
				continue;
			}
			printf("OK: NCryptDecrypt() NCRYPT_PAD_PKCS1_FLAG: 0x%x\n", Status);

			wprintf(L"Success!\n");
		}
	} while (1);

	return 0;

}
