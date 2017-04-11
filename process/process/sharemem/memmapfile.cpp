// MemMapFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD nRet = 0;
	HANDLE lhShareMemory=
	CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0, 1024,
		_T("wanghao")
		);
	if (lhShareMemory == NULL)
	{
		puts("CreateFileMapping failed");
		nRet = -1;
		goto EXIT_POINT;
	}
	char *pstrBuffer;
	//获取文件地址
	pstrBuffer = (char *)MapViewOfFile(lhShareMemory, FILE_MAP_WRITE, 0, 0, 1024);
	char buff[128] = {0};
	puts("input:");
	scanf("%s", buff);
	strcpy(pstrBuffer, buff);//写入数据到文件中
	getchar();
	//////////////////////////////////////////////////////////////////////////
EXIT_POINT:	
	getchar();
	if(pstrBuffer)
		UnmapViewOfFile(pstrBuffer);
	if(lhShareMemory)
		CloseHandle(lhShareMemory);
	return 0;
}

