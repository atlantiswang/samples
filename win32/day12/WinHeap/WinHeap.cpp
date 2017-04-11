#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

void HeapInfo()
{
	HANDLE hHeap = GetProcessHeap();
	printf("µÚÒ»¸ö¶Ñ:%d\n",hHeap);
	HANDLE hHeaps[256] = {0};
	DWORD nCount = GetProcessHeaps(256,hHeaps);
	for(DWORD i=0;i<nCount;i++)
	{
		printf("%d-%d\n",i,hHeaps[i]);
	}
}
void Heap()
{
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE,
		1024*1024,0);
	char *pszText = (char*)HeapAlloc(hHeap,
		HEAP_ZERO_MEMORY,2*1024*1024);
	strcpy(pszText,"hello heap");
	printf("%s\n",pszText);
	HeapFree(hHeap,0,pszText);
	HeapDestroy(hHeap);
}
int main(int argc, char* argv[])
{
//	HeapInfo();
	Heap();
	return 0;
}
