// CSP_aes.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "wincrypt.h"

BYTE enData[512] = {0};
DWORD dwDataLen = 512;

void printByte(BYTE *pData, DWORD dwSize)
{
	printf("bit total:%d\n", dwSize);
	for (int i =0; i<dwSize; i++)
	{
		printf("%02X ", pData[i]);
		if ((i+1)%10 == 0)
			putchar('\n');
	}
	putchar('\n');
}

bool 
testAesEncrypt(char *buff, DWORD *pdwLen)
{
	DWORD nRet = true;
	HCRYPTPROV hProv = NULL;
	if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, 0))
	{
		if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_NEWKEYSET))
		{
			printf("CryptAcquireContext failed:%X",GetLastError());
			nRet = false;
			goto EXIT_POINT;
		}
	}

	HCRYPTHASH hHash = 0;
	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))    
	{   
		printf("CryptCreateHash failed\n");
		nRet = false;
		goto EXIT_POINT;    
	}    

	if(!CryptHashData(hHash, (BYTE*)buff, *pdwLen, 0))    
	{   
		nRet = false;
		printf("CryptHashData failed\n");
		goto EXIT_POINT;
	}    

	HCRYPTKEY hKey = 0;
	if(!CryptDeriveKey(hProv, CALG_AES_128, hHash, CRYPT_EXPORTABLE, &hKey))
	{
		nRet = false;
		printf("CryptDeriveKey failed:%x",GetLastError());
		goto EXIT_POINT;
	}

	char pPwd[128] = {0};
	puts("input:");
	scanf("%s", pPwd);
	DWORD dwPwdLen = strlen(pPwd) + 1;

	if(!CryptEncrypt(hKey, NULL, TRUE, 0, (BYTE*)pPwd, &dwPwdLen, 512))
	{
		printf("CryptEncrypt failed\n");
		goto EXIT_POINT;
	}
	memcpy(enData, pPwd, dwPwdLen);
	dwDataLen = dwPwdLen;
	printByte((BYTE*)buff, *pdwLen);

EXIT_POINT:	
	if (hProv)
		CryptReleaseContext(hProv, 0);
	if (hHash)
		CryptDestroyHash(hHash);
	if(hKey)
		CryptDestroyKey(hKey);

	return nRet;

}

bool
testAesDecrypt(char *buff, DWORD dwLen)
{
	DWORD nRet = true;
	HCRYPTPROV hProv = NULL;

	if (!CryptAcquireContext(&hProv, NULL, NULL ,PROV_RSA_AES, 0))
	{
		printf("CryptAcquireContext failed\n");
		nRet = false;
		goto EXIT_POINT;
	}

	HCRYPTHASH hHash = 0;
	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		printf("CryptCreateHash failed\n");
		nRet = false;
		goto EXIT_POINT;
	}

	if(!CryptHashData(hHash, (BYTE*)buff, dwLen, 0))    
	{   
		nRet = false;
		printf("CryptHashData failed\n");
		goto EXIT_POINT;
	}

	HCRYPTKEY hKey = 0;
	if(!CryptDeriveKey(hProv, CALG_AES_128, hHash, CRYPT_EXPORTABLE, &hKey))
	{
		nRet = false;
		printf("CryptDeriveKey failed:%x",GetLastError());
		goto EXIT_POINT;
	}

	if (!(CryptDecrypt(hKey, NULL, TRUE, 0, (BYTE*)enData, &dwDataLen)))
	{
		printf("CryptDecrypt failed:%X\n", GetLastError());
		nRet = false;
		goto EXIT_POINT;
	}

	printf("%s\n", enData);
EXIT_POINT:
	if(hProv) CryptReleaseContext(hProv, 0);
	if(hKey)  CryptDestroyKey(hKey);
	if(hHash) CryptDestroyHash(hHash);
	return nRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char buff[128] = {0};
	puts("input random:");
	scanf("%s", buff);
	DWORD dwLen = strlen(buff);

	if(!testAesEncrypt(buff, &dwLen))
		puts("testAesEncrypt failed");
	else
	{
		if (!testAesDecrypt(buff, dwLen))
			puts("testAesDecrypt failed");
		else
			puts("testAesDecrypt success");
	}
	//////////////////////////////
	getchar();
	return 0;
}

