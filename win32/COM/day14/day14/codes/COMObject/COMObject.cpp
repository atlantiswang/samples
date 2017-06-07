// COMObject.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

//ATL中需要的全局变量，保存了ATL库的信息
CComModule _Module;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

