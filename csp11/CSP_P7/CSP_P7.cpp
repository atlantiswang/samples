// CSP_P7.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EncryptMsgDecryptMsg.h"
#include "SignVerify.h"

#pragma comment (lib, "crypt32.lib")



int _tmain(int argc, _TCHAR* argv[])
{

	//p7加解密：
#if 0
	puts("input:");
	char data[128] = {0};
	scanf("%s", data);
	BYTE szEnCryptData[1024] = {0};
	DWORD dwEnCryptData = 1024;

	if (!MyEncryptMessageStep(data, szEnCryptData, dwEnCryptData))
	{
		puts("P7 Encrypt failed");
	}else
	{
		puts("P7 Encrypt success");
		if (!MyDecryptMessage(szEnCryptData, dwEnCryptData))
			puts("P7 Decrypt failed");
		else
			puts("P7 Decrypt success");
	}
#endif
	puts("input:");
	char data[128] ={0};

	BYTE SignedBlob[2048] = {0};
	DWORD dwLen = 2048;
	scanf("%s", data);
	if (!MySignMessage(data,dwLen, SignedBlob))
		puts("MySignMessage failed");
	else
	{
		puts("MySignMessage success");
		if (!MyVerifyMessageSignature(SignedBlob, dwLen))
			puts("MyVerifyMessageSignature failed");
		else
			puts("MyVerifyMessage success");
	}
///////////////////////
	getchar();
	return 0;
}

