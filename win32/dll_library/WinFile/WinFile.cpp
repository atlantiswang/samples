#include "stdafx.h"
#include "stdio.h"
#include "windows.h"
void Create()
{
	HANDLE hFile = CreateFile(
				"g:/file.txt",GENERIC_WRITE,
				FILE_SHARE_READ,NULL,CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,NULL);
	CloseHandle(hFile);
}
void Write()
{
	HANDLE hFile = CreateFile("G:/file.txt",
		GENERIC_WRITE,FILE_SHARE_READ,
		NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	char szText[]="hello txt";
	DWORD nCount = 0;
	WriteFile(hFile,szText,strlen(szText),&nCount,
		NULL);
	printf("准备写入长度:%d,实际写入长度:%d\n",
		strlen(szText),nCount);
	CloseHandle(hFile);
}
void Read()
{
	HANDLE hFile = CreateFile(
		"g:/file.txt",GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD nHight = 0;
	DWORD nLow = GetFileSize(hFile,&nHight);
	char szText[256] = {0};
	DWORD nCount = 0;
	ReadFile(hFile,szText,9,&nCount,NULL);
	printf("准备读取:%d,实际读取:%d,数据:%s\n",
		nLow,nCount,szText);
}
void Copy()
{
	CopyFile("g:/file.txt","g:/others/nofile.txt",false);
}
void Delete()
{
	DeleteFile("g:/others/nofile.txt");
}
void Move()
{
	MoveFile("g:/file.txt","g:/others/file.txt");
}
void Find()
{
	char szPath[]="c:/*.*";
	WIN32_FIND_DATA wfd = {0};
	HANDLE hFind = FindFirstFile(szPath,&wfd);
	BOOL goFind = TRUE;
	while(goFind)
	{
		if(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("[%s]\n",wfd.cFileName);
		}else{
			printf("%s\n",wfd.cFileName);
		}
		goFind = FindNextFile(hFind,&wfd);
	}
	FindClose(hFind);
}
int main(int argc, char* argv[])
{
//	Create();
//	Write();
//	Read();
//	Copy();
//	Delete();
//	Move();
	Find();
	return 0;
}
