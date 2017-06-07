// DLLInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ImpMath.h"
//#include "ImpMath2.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
IMath *CreateInstance()
{
	return new CImpMath;
}

