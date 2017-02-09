#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
	HANDLE hFile = CreateFile("g:/map.dat",
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ,NULL,CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,NULL);
	HANDLE hMap = CreateFileMapping(hFile,NULL,PAGE_READWRITE,
		0,1024*1024,"WH");
	//如果第一个参数为NULL，申请1M内存
	//如果第一个参数为hFile,将硬盘文件扩至1M大小
	char*pszText = (char*)MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,
		0,0,0);
	//将地址  和 内存/硬盘文件 建立映射关系
	strcpy(pszText,"hello map");
//	printf("%s\n",pszText);
	UnmapViewOfFile(pszText);
	getchar();
	CloseHandle(hMap);//一旦关闭就没有了
	CloseHandle(hFile);
	return 0;
}
