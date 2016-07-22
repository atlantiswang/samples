// SKF.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "struct.h"
#include "fun.h"
#include "SKFFun.h"

HINSTANCE hin;


int _tmain(int argc, _TCHAR* argv[])
{
	 
	BOOL fFreeResult;

	// Get a handle to the DLL module.

	hin = LoadLibrary(TEXT("mtoken_k5")); 

	// If the handle is valid, try to get the function address.

	if (hin != NULL) 
	{ 
		puts("load dll library success");
		BYTE *pbSignatures = NULL;
		BYTE **pbSignature = &pbSignatures;
		ULONG pulSignLen = 0;

		//verify others
#ifdef VERIFYOTHER
		if(VerifyOther())
			puts("VerifyOther success");
		else
			puts("VerifyOther failed");
		goto FREELIB;
#endif
		//sign
		if(SKF_Sign(pbSignature, &pulSignLen))
			puts("SKF Sign success");
		else
		{
			puts("SKF Sign failed");
			goto FREELIB;
		}
		//verify
		if (SKF_Verify(pbSignatures, pulSignLen))
		{
			puts("SKF Verify success");
		}
		else
		{
			puts("SKF Verify failed");
		}
FREELIB:
		// Free the DLL module.
		fFreeResult = FreeLibrary(hin); 
	}
	else
	{
		puts("error");
	}
	

	system("pause");
	return 0;
}

