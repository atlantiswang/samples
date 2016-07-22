// OS Version.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	OSVERSIONINFO osVer = {0};
	osVer.dwOSVersionInfoSize = sizeof(osVer);
	GetVersionEx(&osVer);
	
	char *szVer = NULL;
	if (osVer.dwMajorVersion == 6 && osVer.dwMinorVersion == 1)
		szVer = "win 7";
	else if (osVer.dwMajorVersion == 5 && osVer.dwMinorVersion == 1)
		szVer = "win xp";
	else 
		printf("Majorversion:%d\tMinorVersion%d\n", 
		osVer.dwMajorVersion, osVer.dwMinorVersion);

	printf("os version: %s\n", szVer);

	return 0;
}

