#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

void status()
{
	MEMORYSTATUS ms= {0};
	ms.dwLength = sizeof(ms);
	GlobalMemoryStatus(&ms);
	printf("load:%d\n",ms.dwMemoryLoad);
	printf("TotalPhys:%u\n",ms.dwTotalPhys);
	printf("AvliaPhys:%u\n",ms.dwAvailPageFile);
	printf("TotalVirt:%u\n",ms.dwTotalPageFile);
	printf("AvliaVirt:%u\n",ms.dwAvailPageFile);

	printf("TotalAddr:%u\n",ms.dwTotalVirtual);
	printf("AvliaAddr:%u\n",ms.dwAvailVirtual);
	printf("***************************\n");
}
void Virtual_Info()
{
	status();
	char * pszText = (char*)VirtualAlloc(NULL,1024*1024*1024,MEM_COMMIT,
		PAGE_READWRITE);
	status();
	VirtualFree(pszText,0,MEM_RELEASE);
	status();
}
void Virtual_Commit()
{
	char *pszText=(char*)VirtualAlloc(NULL,1024*1024,
		MEM_COMMIT,PAGE_READWRITE);
	strcpy(pszText,"hello commit");
	printf("%s\n",pszText);
	VirtualFree(pszText,0,MEM_RELEASE);
}
void Virtual_Reserve()
{
	char* pszText = (char*)VirtualAlloc(NULL,1024*1024*1024,
		MEM_RESERVE,PAGE_READWRITE);
	VirtualAlloc(pszText,1,MEM_COMMIT,PAGE_READWRITE);
	strcpy(pszText,"hello reserve");
	printf("%s\n",pszText);
	VirtualFree(pszText,0,MEM_RELEASE);
}
int main(int argc, char* argv[])
{
//	Virtual_Info();
//	Virtual_Commit();
	Virtual_Reserve();
	return 0;
}
