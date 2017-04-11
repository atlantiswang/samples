#include "stdafx.h"
#include "RSA.h"

#define DATALEN 100

CRSA::CRSA()
{
}

CRSA::~CRSA()
{
}

void CRSA::TestRSA(void)
{
	HCRYPTPROV hCryptProv = NULL;

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

	HCRYPTKEY hKey;
	BeginAction("CryptGenKey()");
	if(!CryptGenKey(hCryptProv, AT_KEYEXCHANGE, 0, &hKey))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	BYTE pData[DATALEN] = {0};
	unsigned long ulDataLen = DATALEN;
	DWORD ulEncryptedLen = ulDataLen;
	BYTE *pOut = NULL;
	for(int i = 0; i < DATALEN; i++)
	{
		pData[i] = i % 255;
	}

	cout << "Data to be encrypt:" << endl;
	ShowData(pData, ulDataLen);

	BeginAction("CryptEncrypt()");
	if(!CryptEncrypt(hKey, 0, TRUE, 0, NULL, &ulEncryptedLen, ulDataLen))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	pOut = new BYTE[ulEncryptedLen];

	memset(pOut, 0, ulEncryptedLen);
	memcpy(pOut, pData, ulDataLen);
	DWORD ulTemp = ulDataLen;
	ulDataLen = ulEncryptedLen;
	ulEncryptedLen = ulTemp;

	BeginAction("CryptEncrypt()");
	if(!CryptEncrypt(hKey, 0, TRUE, 0, pOut, &ulEncryptedLen, ulDataLen))
	{
		delete[] pOut;
		pOut = NULL;
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data encrypted:" << endl;
		ShowData(pOut, ulEncryptedLen);
	}

	BeginAction("CryptDecrypt()");
	if(!CryptDecrypt(hKey, 0, TRUE, 0, pOut, &ulEncryptedLen))
	{
		delete[] pOut;
		pOut = 0;
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data to decrypted:" << endl;
		ShowData(pOut, ulEncryptedLen);
	}

	if(0 != memcmp(pData, pOut, ulEncryptedLen))
	{
		delete[] pOut;
		pOut = NULL;
		cout << "Data not equal, encrypt/decrypt failed." << endl;
	}
}
