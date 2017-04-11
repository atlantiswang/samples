// threaddll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "threaddll.h"


// This is an example of an exported variable
THREADDLL_API int nthreaddll=0;

// This is an example of an exported function.
THREADDLL_API int fnthreaddll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see threaddll.h for the class definition
Cthreaddll::Cthreaddll()
{
	return;
}
