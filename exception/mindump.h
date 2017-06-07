#ifndef __MINI_DUMP_H__
#define __MINI_DUMP_H__
#include <Windows.h>
#include <dbghelp.h>
#include <string>


typedef BOOL (WINAPI *MINIDUMP_WRITER)(HANDLE hProcess, 
                                         DWORD dwPid, HANDLE hFile,
                                         MINIDUMP_TYPE DumpType,
                                         CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                         CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                         CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);
typedef void (*PFN_EXCEPTION_CALLBACK)(void* pContext);

class CMiniDumper
{
private:
    CMiniDumper(){}
    ~CMiniDumper()
	{
	if (s_pContext != NULL)
	{
		free(s_pContext);
		s_pContext = NULL;
	}
	}

public:
    static void Setup(LPCSTR szAppName, PFN_EXCEPTION_CALLBACK pfnExpCallBack = NULL, void* pContext = NULL, BOOL bIgnoreErrorBox = FALSE);

private:
    static std::string s_dmpFileName;
    static MINIDUMP_WRITER s_miniDumpWriter;
    static void* s_pContext;
    static LONG WINAPI TopLevelFilter( struct _EXCEPTION_POINTERS *pExceptionInfo );
    static PFN_EXCEPTION_CALLBACK s_pfnExpCallBack;
};

#endif