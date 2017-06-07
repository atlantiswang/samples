#include "stdafx.h"
#include "SysKeyTest.h"

SysKeyTest::SysKeyTest()
{
}

SysKeyTest::~SysKeyTest()
{
}

void SysKeyTest::TestKey(DWORD ulALG)
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
		printf("Last Error = 0x%08X\n", GetLastError());
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

	HCRYPTKEY hKey = NULL;
	BeginAction("CryptGenKey()"); 
	if (!CryptGenKey(hCryptProv, ulALG, /*CRYPT_EXPORTABLE*/0,  &hKey))//RC4/DES are similar!!!!!!!!!!!!!!!!!!!
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	//Encrypt Data with a key:
	#define BUF_SIZE  1024

	BYTE pData[BUF_SIZE] = "USB Token: Encrypt Data with the derive key!\0";
	BYTE pOrinData[BUF_SIZE] = {0};
	DWORD dwLen = 60;
	DWORD dwRetLen = dwLen;
	memcpy(pOrinData, pData, dwLen);

	cout << "Data to be encrypted:" << endl; 
	ShowData(pData, dwLen);

	//encrypt, first get size.
	BeginAction("CryptEncrypt()"); 
	if(!CryptEncrypt(hKey, NO_HASH, LAST_DATA, 0, NULL, &dwRetLen, BUF_SIZE))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	//Get encrypted value:
	BeginAction("CryptEncrypt()"); 
	if(!CryptEncrypt(hKey, NO_HASH, LAST_DATA, 0, pData, &dwLen, BUF_SIZE))
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

	//Decrypt Data with a key:
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

	if(0 != memcmp(pData, pOrinData, dwLen))
	{
		cout << "Data not equal, encrypt/decrypt failed." << endl;
	}

	//////////////////////////////////////////////////////////////////////////
	// encrypt dulplicate
	dwLen = 60;
	memcpy(pData, pOrinData, dwLen);
	BYTE buf[1024] = {0};
	memcpy(buf, pOrinData, dwLen);
	dwRetLen = dwLen/2;

	BeginAction("CryptEncrypt() first block"); 
	DWORD enclen = dwLen/2;
	if(!CryptEncrypt(hKey, NO_HASH, FALSE, 0, NULL, &enclen, BUF_SIZE))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	//Get encrypted value:
	BeginAction("Get the first block result"); 
	enclen = dwLen/2;
	if(!CryptEncrypt(hKey, NO_HASH, FALSE, 0, buf, &enclen, BUF_SIZE))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data after encrypted:" << endl;
		ShowData(buf, enclen);
	}

	BeginAction("CryptEncrypt() second block"); 
	if(!CryptEncrypt(hKey, NO_HASH, TRUE, 0, NULL, &dwRetLen, BUF_SIZE))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	//Get encrypted value:
	BeginAction("Get the second block result"); 
	dwRetLen = dwLen/2;
	memcpy(buf + enclen, pData + dwLen/2, dwRetLen);
	if(!CryptEncrypt(hKey, NO_HASH, TRUE, 0, buf + enclen, &dwRetLen, BUF_SIZE))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data after encrypted:" << endl;
		ShowData(buf + enclen, dwRetLen);
	}

	//Decrypt Data with a key:

	// the first block
	BeginAction("CryptDecrypt() the first block"); 
	dwLen = enclen + dwRetLen;
	enclen = 16;
	if(!CryptDecrypt(hKey, NO_HASH, FALSE, 0, buf, &enclen))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data after decrypted:" << endl;
		ShowData(buf, enclen);
	}

	BeginAction("CryptDecrypt() the second block"); 
	dwRetLen = dwLen - 16;
	if(!CryptDecrypt(hKey, NO_HASH, TRUE, 0, buf + 16, &dwRetLen))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
		cout << "Data after decrypted:" << endl;
		ShowData(buf + 16, dwRetLen);
	}
	memcpy(buf + enclen, buf + 16, dwRetLen);
	
	if (dwRetLen + enclen != 60)
	{
		cout << "Data not equal, encrypt/decrypt failed." << endl;
	}
	cout << "the whole decrypt data is" << endl;
	ShowData(buf, dwRetLen + enclen);

	if(0 != memcmp(buf, pOrinData, dwRetLen + enclen))
	{
		cout << "Data not equal, encrypt/decrypt failed." << endl;
	}
	
}





















