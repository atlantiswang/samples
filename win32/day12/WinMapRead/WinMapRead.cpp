#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
	HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,"WH");//true 让子进程用
	char*pszText = (char*)MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,
		0,0,0);
	printf("%s\n",pszText);
	UnmapViewOfFile(pszText);
	CloseHandle(hMap);
	return 0;
}
