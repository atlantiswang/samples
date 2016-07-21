// base64.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "b64code.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BYTE bSource[128] = {0x32, 0x32, 0x12, 0x89, 0xA3};
	unsigned int nlen =128;
	
	int nRlen = 
	Base64EncodeGetRequiredLength(nlen);
	
	LPSTR szDest = new char[nRlen];
	BOOL nRet = Base64Encode(bSource, 128, szDest, &nRlen);
	if (nRet == TRUE)
		puts("base64 success");
	else
		puts("base64 failed");
	//////////////////////
	getchar();
	return 0;
}

