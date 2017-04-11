#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

#pragma comment(lib, "threaddll.lib")
_declspec(dllimport) void fun();
DWORD CALLBACK TestProc(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while(1)
	{
// 		printf("%s\n",pszText);
// 		Sleep(1000);
		fun();
	}
	return 0;
}
DWORD CALLBACK TestProc2(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while(1)
	{
		printf("%s\n",pParam);
		Sleep(1000);
	}
	return 0;
}
int main(int argc, char* argv[])
{
	DWORD nID = 0;
	char* pszText="****************";
	HANDLE hThread = CreateThread(NULL,0,TestProc,
		pszText,0,&nID);
	char* pszText2="-----------------";
	HANDLE hThread2 = CreateThread(NULL,0,TestProc2,
		pszText2,0,&nID);
	int a = 3;
	printf("%d\n", a);
	getchar();
	SuspendThread(hThread);
	ResumeThread(hThread2);
	CloseHandle(hThread);
	getchar();
	return 0;
}
