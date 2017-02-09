#include "stdafx.h"
#include <stdio.h>
#define UNICODE
#include <windows.h>
void T_char()
{
	TCHAR *pszText = __TEXT("hello");
#ifdef UNICODE
	wprintf(L"%s\n",pszText);
#else
	printf("单：%s\n",pszText);
#endif
}/*
//标准输出、输入、错误三个句柄不是用来找内存的
//标准错误与标准错误的区别：标准错误没有缓冲区
BOOL WriteConsole(//此函数比wprintf支持的好，怎么输出看UNICODE
  HANDLE hConsoleOutput,           // handle to screen buffer
  CONST VOID *lpBuffer,            // write buffer
  DWORD nNumberOfCharsToWrite,     // number of characters to write
  LPDWORD lpNumberOfCharsWritten,  // number of characters written
  LPVOID lpReserved                // reserved备用
);
HANDLE GetStdHandle(
  DWORD nStdHandle   // input, output, or error device
  //STD_INPUT_HANDLE STD_OUTPUT_HANDLE STD_ERROR_HANDLE
);
*/

/*
void T_char()
{
#ifdef WIDECHAR //本文件内具有向上溯源性，不具有向下溯源性
	wchar_t *pszText=L"hello";
	wprintf(L"%s\n",pszText);
#else
	char* pszText = "hello";
	printf("单:%s\n",pszText);
#endif
}*/
void C_char()
{
	char* pszText="hello char";
	printf("%s\n",pszText);
}
void W_char()
{
	wchar_t* pwszText=L"hello wchar";
	int nlen = wcslen(pwszText);
	wprintf(L"%s %d\n",pwszText,nlen);//11 len求的都是字符的个数
}
void PrintfUnicode()
{
	HANDLE hStd=GetStdHandle(STD_OUTPUT_HANDLE);
	for(WORD nHigh=100;nHigh<200;nHigh++)
	{
		for(WORD nLow=100;nLow<200;nLow++)
		{
			wchar_t wChar=nHigh*256+nLow;
		//	wprintf(L"%s",&wChar);
			WriteConsole(hStd,&wChar,1,NULL,NULL);
		}
		printf("\n");
	}
}
int main(int argc, char* argv[])
{
//	C_char();
//	W_char();
//	T_char();
	PrintfUnicode();
	return 0;
}
