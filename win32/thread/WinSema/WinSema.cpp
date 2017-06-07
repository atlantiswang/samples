#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
HANDLE g_hSema = 0;
DWORD CALLBACK TestProc(LPVOID pParam)
{
	while(1)
	{
		WaitForSingleObject(g_hSema,INFINITE);
		printf("*********\n");
		Sleep(1000);
	}
	return 0;
}
DWORD CALLBACK TestProc2(LPVOID pParam)
{
	while (1)
	{
//	ReleaseSemaphore(g_hSema,1,NULL);
	Sleep(3000);
	}
	return 0;
}
int main(int argc, char* argv[])
{
	g_hSema = CreateSemaphore(NULL,3,11,NULL);
	DWORD nID = 0,nID2=0;
	HANDLE hThread = CreateThread(NULL,0,TestProc,
		NULL,0,&nID);
//	HANDLE hThread2 = CreateThread(NULL,0,TestProc2,NULL,0,&nID2);
	getchar();
//	WaitForSingleObject(hThread,INFINITE);
	CloseHandle(hThread);
	getchar();
	CloseHandle(g_hSema);
	return 0;
}
