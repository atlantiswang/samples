// dllmain.cpp : 定义 DLL 应用程序的入口点。
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

