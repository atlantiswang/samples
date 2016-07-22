// CSP_encrypt_decrypt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../CSP_sign_verify/fun.h"

PCCERT_CONTEXT pCert = NULL;

bool 
EnCrypt(BYTE *data, DWORD* pcblen)
{
	bool bRet = true;
	pCert = ImportCert(L"FEITIAN ePassNG RSA Cryptographic Service Provider", _T("签名加密"));

	HCRYPTPROV hProv = NULL;
	if (!CryptAcquireContext(
		&hProv,
		_T("CSP_encrypt_decrypt"),
		NULL,
		PROV_RSA_FULL,
		0))
	{
		if (CryptAcquireContext(
			&hProv, 
			_T("CSP_encrypt_decrypt"),
			NULL,
			PROV_RSA_FULL,
			CRYPT_NEWKEYSET))
		{
			puts("a new container is create");
		}else
		{
			puts("create container failed");
			system("pause");
			bRet = false;
			goto EXIT_POINT;
		}
	}

	HCRYPTKEY hPubKey = NULL;
	pCert->dwCertEncodingType;
	pCert->pCertInfo->SubjectPublicKeyInfo;
	if(!CryptImportPublicKeyInfoEx(hProv, pCert->dwCertEncodingType,
		&pCert->pCertInfo->SubjectPublicKeyInfo, CALG_RSA_KEYX, 0, NULL, &hPubKey))
	{
		printf("CryptImportPublicKeyInfoEx failed:%x\n",GetLastError());
		bRet = false;
		goto EXIT_POINT;
	}
	
	puts("input:");
	scanf("%s", data);
	*pcblen = strlen((const char*)data);
	if (!CryptEncrypt(hPubKey, NULL, TRUE, 0, data ,pcblen , 128))
	{
		printf("CryptEncrypt failed:%x\n", GetLastError());
		bRet = false;
		goto EXIT_POINT;
	}


EXIT_POINT:
	if(hProv)
		CryptReleaseContext(hProv, 0);
	if(pCert)
		CertCloseStore(pCert, 0);
	if(hPubKey)
		CryptDestroyKey(hPubKey);

	return bRet;
}

bool DeCrypt(BYTE *data, DWORD *pcblen)
{
	bool bRet = true;
 	HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hKeyProv = NULL;
	//这种方式得到CSP也是可以的(通过证书找到容器CSP)
#if 0	
	DWORD dwKeyType;
	BOOL bFreeKeyProv = FALSE;
	if (!CryptAcquireCertificatePrivateKey(pCert, 0, 0, &hKeyProv, &dwKeyType, &bFreeKeyProv))
	{
		printf("CryptAcquireCertificatePrivateKey error:0X%x.\n",GetLastError());  
		bRet = false;
		goto EXIT_POINT;
	}
#endif

	if (!CryptAcquireContext(
		&hKeyProv, 
		_T("698D363C-1FF8-4AAE-872B-D7C428777B07"),
		_T("FEITIAN ePassNG RSA Cryptographic Service Provider"),
		PROV_RSA_FULL,
		0))
	{
		puts("CryptAcquireContext failed");
		bRet = false;
		goto EXIT_POINT;
	}

	HCRYPTKEY hKey;
	if (!CryptGetUserKey(hKeyProv, AT_KEYEXCHANGE, &hKey))
	{
		printf("CryptGetUserKey error:%x\n", GetLastError());
		bRet = false;
		goto EXIT_POINT;
	}

	if (!CryptDecrypt(hKey, NULL, true, 0, data, pcblen))
	{
		printf("CryptDecrypt failed:%x", GetLastError());
		bRet = false;
		goto EXIT_POINT;
	}

	char buff[128] = {0};
	strncpy(buff, (const char*)data, *pcblen);
	printf("%s\n", buff);

EXIT_POINT:
	if(hKeyProv)
		CryptReleaseContext(hKeyProv, 0);
	if(hKey)
		CryptDestroyKey(hKey);
	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BYTE data[1024] = {0};
	DWORD cblen = 1024;

	if (!EnCrypt(data, &cblen))
	{
		puts("EnCrypt failed");
		return -1;
	}
	else
	{
		puts("EnCrypt success");
		if(!DeCrypt(data, &cblen))
		{
			puts("DeCrypt failed");
		}
		else
		{
			puts("DeCrypt success");
		}
	}
	
	/////////////////////////
	system("pause");
	return 0;
}

