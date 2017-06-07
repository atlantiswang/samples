//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeriveKeyTest.h"
DeriveKeyTest::DeriveKeyTest()
{
}

DeriveKeyTest::~DeriveKeyTest()
{
}

void DeriveKeyTest::Testkey(DWORD ulALG)
{
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTKEY hKey = 0;
	HCRYPTHASH hHash = 0;
	char *szPassword = "Derive key test!";
	DWORD dwLength = 0;

	cout << endl << "Test CSP: " << CSP_NAME << endl << endl;

	// Create a keyset(aka container), if the keyset already exists,
	// delete it and re-create it.

	BeginAction("CryptAcquireContext() CRYPT_NEWKEYSET");
	if(!CryptAcquireContext(&hCryptProv,
				CONTAINER,
				CSP_NAME,
				PROV_RSA_FULL,
				CRYPT_NEWKEYSET))
	{
		DWORD dwLastErr = GetLastError();
		ActionFailed(dwLastErr);

		if(0x8009000F == dwLastErr) //  Object already exists.
		{
			BeginAction("CryptAcquireContext() CRYPT_DELETEKEYSET");
			if(!CryptAcquireContext(&hCryptProv,
						CONTAINER,
						CSP_NAME,
						PROV_RSA_FULL,
						CRYPT_DELETEKEYSET))
			{
				ActionFailed(GetLastError());
				return;
			}
			else
			{
				ActionSuccess();
				BeginAction("CryptAcquireContext() CRYPT_NEWKEYSET");
				if(!CryptAcquireContext(&hCryptProv,
							CONTAINER,
							CSP_NAME,
							PROV_RSA_FULL,
							CRYPT_NEWKEYSET))
				{
					ActionFailed(dwLastErr);
					return;
				}
				else
				{
					ActionSuccess();
				}
			}
		}
		else
			return;
	}
	else
	{
		ActionSuccess();
	}

	// Hold the handle and release when this function return.
	HCRYPTPROV_Holder holder(hCryptProv);

	// Create a hash object.
	BeginAction("CryptCreateHash()");
	if(!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	// Hash the password string.
	dwLength = lstrlen(szPassword);

	BeginAction("CryptHashData()");
	if(!CryptHashData(hHash, (BYTE *) szPassword, dwLength, 0))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	// Create a block cipher session key based on the hash of the password.
	BeginAction("CryptDeriveKey()");
	if(!CryptDeriveKey(hCryptProv, ulALG, hHash, CRYPT_EXPORTABLE, &hKey))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	//Encrypt Data with RC2 key:
	BYTE pData[1024] = "USB Token: Encrypt Data with the derive key!\0";
	DWORD dwLen = lstrlen((LPCTSTR) pData);//60;
	cout << "Data to be encrypted:" << endl; 
	ShowData(pData, dwLen);

	//encrypt:
	BeginAction("CryptEncrypt()");
	if(!CryptEncrypt(hKey, NO_HASH, LAST_DATA, 0, pData, &dwLen, 1024))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data after encrypted:" << endl;
		ShowData(pData, dwLen);
	}

	//Decrypt Data with RC2 key:
	BeginAction("CryptDecrypt()");
	if(!CryptDecrypt(hKey, NO_HASH, LAST_DATA, 0, pData, &dwLen))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data after decrypted:" << endl;
		ShowData(pData, dwLen);
	}
}
