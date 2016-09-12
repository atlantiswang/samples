/*mfc's afxBeginThread:
	1. user 2. nogui 
	except 0 param,others have default value

  thread-create param only these:
  1. threadpro
  2. param
  3. createflag(0:immediately|suspended)
  4. nid
  5. static size (0 is ok)
  6. security-attribute
  7. priority

  threadpro: all can see in declare
  1. Createthread: DWORD WINAPI (__stdcall) threadpro(LPVOID pParam)
  2. _beginthread: void __cdecl theadpro(void * pParam)
  3. AfxBeginThread: UINT __cdecl threadpro(LPVOID pParam)|AfxBeginThread(RUNTIME_CALSS(threadclass))

  CreateThread:the base method invoked,but isn't safe,the other two add security.
 */

#include <stdio.h>
#include <process.h>
#include <windows.h>

DWORD __stdcall _createthread(LPVOID pParam);
void __cdecl __beginthread(void *pParam);

int main()  
{   
	char *pbuffer = "hello world";
	DWORD nID = 0;
	HANDLE hcreatethread = CreateThread(NULL, 0, _createthread, pbuffer, 0, &nID);
	_beginthread(__beginthread/*3*/, 0/*2*/, pbuffer/*4*/);

	WaitForSingleObject(hcreatethread, INFINITE);
} 

DWORD __stdcall _createthread(LPVOID pParam)
{
	puts((const char *)pParam);
	getchar();
	return 0;
}

void __cdecl __beginthread(void *pParam)
{
	puts((const char *)pParam);
}
