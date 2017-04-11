#define DLLCALSS_EXPORTS
#include "dllclass.h"
#include "stdio.h"
#include "windows.h"
BOOL CALLBACK DllMain(HINSTANCE hDll,
					  DWORD fdwReason,LPVOID pVoid)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		//初始化工作
		printf("Load......\n");
		break;
	case DLL_PROCESS_DETACH:
		//善后处理
		printf("UnLoading......\n");
		break;
	}
	return TRUE;
}
int CMath::Add(int add1, int add2)
{
	return add1+add2;
}
int CMath::Sub(int sub1, int sub2)
{
	return sub1-sub2;
}