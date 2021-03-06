#include <Windows.h>
#include <stdio.h>

BOOL Is64BitOS()
{
	typedef VOID (WINAPI *LPFN_GetNativeSystemInfo)( __out LPSYSTEM_INFO lpSystemInfo );
	LPFN_GetNativeSystemInfo fnGetNativeSystemInfo = (LPFN_GetNativeSystemInfo)GetProcAddress( GetModuleHandleW(L"kernel32"),"GetNativeSystemInfo");
	if(fnGetNativeSystemInfo)
	{
		SYSTEM_INFO stInfo = {0};
		fnGetNativeSystemInfo( &stInfo);
		if( stInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64
			|| stInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
		{
			return TRUE;
		}
	}
	return FALSE;
}

//如果是本进程ID，则可以使用（sizeof(int*) *8）来表示
BOOL Is64BitProcess(DWORD dwProcessID)
{
	if (!Is64BitOS())
	{
		return FALSE;
	}else
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,dwProcessID);
		if(hProcess)
		{
			typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
			LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandleW(L"kernel32"),"IsWow64Process");
			if (NULL != fnIsWow64Process)
			{
				BOOL bIsWow64 = FALSE;
				fnIsWow64Process(hProcess,&bIsWow64);
				CloseHandle(hProcess);
				if (bIsWow64)
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

int main()
{
	while(true)
	{
		puts("input prcess id:");
		unsigned int nid;
		scanf("%d", &nid);
		if(Is64BitProcess(nid) == TRUE)
		{
			puts("is 64 bit");
		}
		else puts("isn't 64 bit");
		getchar();
	}
}