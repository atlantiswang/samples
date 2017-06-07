// dllmain.cpp : 定义 DLL 应用程序的入口点。
/*
DLL_PROCESS_ATTACH:当一个dll文件被映射到进程空间时，系统调用该dll的DllMain函数
DLL_PROCESS_DETACH:当DLL被从进程的地址空间解除映射时，系统调用了它的dllmain,但如果是terminateprocess，则不会被调用
DLL_THREAD_ATTACH:当进程创建一线程时，系统查看当前映射到进程地址空间中的所有DLL文件映像。每次创建线程都是会调用的
DLL_THREAD_DETACH:如果线程调用了exitthread来结束线程（线程函数返回时，系统也会自动调用exitthread），系统查看当前映射到进程空间
中的所有DLL文件映像，调用DllMain函数，通知所有的DLL去执行线程级的清理工作。如果是TerminateThread，系统不会调用DllMain。
*/
#include "stdafx.h"
#include <tchar.h>


HHOOK hHook = NULL;

LRESULT CALLBACK KeyboardProc(          int code,
							  WPARAM wParam,
							  LPARAM lParam
							  )
{
	MessageBox(NULL, _T("key down or key up"), NULL, MB_OK|MB_SYSTEMMODAL);
	return CallNextHookEx(hHook,code,wParam,lParam); 
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hHook =
		SetWindowsHookEx(          WH_KEYBOARD,
			KeyboardProc,
			hModule,
			0
			);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		UnhookWindowsHookEx(hHook);
		break;
	}
	return TRUE;
}

