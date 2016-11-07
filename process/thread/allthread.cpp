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
  ----------------------------------------------------------------------------------
  CreateThread后要调用 CloseHandle()
  CloseHandle()是关闭内核对象：使其引用计数减1，如果为0就删除内核对象。
  而ExitThread\TerminateThread都是结束一个线程的，线程内部也可以通过return 等方式退出。
  由于内核对象是资源，所以如果不再想通过内核对象对线程操作时就Close掉，以免浪费资源，但不会影响线程的执行
  只是我们无法再操作这个线程。
  _beginthread/_beginthreadex
  内部都会自动调用_endthread/_endthreadex（结束线程使用，自杀用）。此函数的作用是释放beginthread创建的内部数据。
  而且_endthread还可以自动调用CloseHandle。而_endthreadex不会，需要用CloseHandle。
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
