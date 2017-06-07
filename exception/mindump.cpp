#include "stdafx.h"
#include "MinDump.h"
#include "time.h"
using namespace std;

string CMiniDumper::s_dmpFileName;
void* CMiniDumper::s_pContext = NULL;
MINIDUMP_WRITER CMiniDumper::s_miniDumpWriter = NULL;
PFN_EXCEPTION_CALLBACK CMiniDumper::s_pfnExpCallBack = NULL;

void CMiniDumper::Setup(LPCSTR szAppName, PFN_EXCEPTION_CALLBACK pfnExpCallBack /* = NULL */, void* pContext /* = NULL */, BOOL bIgnoreErrorBox /* = FALSE */)
{
//	ASSERT( s_dmpFileName.size() == 0 );

    if (bIgnoreErrorBox)
    {
        SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
    }
    s_pfnExpCallBack = pfnExpCallBack;
    s_pContext = pContext;

    time_t nowTime = time(NULL);
    struct tm tmNow = *(localtime(&nowTime));
    char szDmpFileName[1024];

    _stprintf(szDmpFileName, _T("%s_%d%d%d-%d%d%d"), szAppName, tmNow.tm_year+1900, 
        tmNow.tm_mon+1, tmNow.tm_mday, tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
	s_dmpFileName = szDmpFileName;

    HMODULE hDll = NULL;

    hDll = ::LoadLibrary( "DBGHELP.DLL" );

    if (!hDll)
    {
 //       TRACE0(_T("DBGHELP.DLL not found"));
        return;
    }

    s_miniDumpWriter = (MINIDUMP_WRITER)::GetProcAddress( hDll, "MiniDumpWriteDump" );
    if (!s_miniDumpWriter)
    {
  //      TRACE0(_T("MiniDumpWriteDump not found"));
        FreeLibrary(hDll);
        return;
    }

	::SetUnhandledExceptionFilter( TopLevelFilter );
}

LONG CMiniDumper::TopLevelFilter( struct _EXCEPTION_POINTERS *pExceptionInfo )
{
	LONG retval = EXCEPTION_CONTINUE_SEARCH;
    char szDumpPath[_MAX_PATH];

    if (!GetTempPath( _MAX_PATH, szDumpPath ))
    {
        _tcscpy( szDumpPath, _T("c:\\temp\\") );
    }

    _tcscat( szDumpPath, s_dmpFileName.c_str() );
    _tcscat( szDumpPath, _T(".dmp"));

    HANDLE hFile = ::CreateFile( szDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL );

	if (hFile == INVALID_HANDLE_VALUE)
    {
//        TRACE2(_T("Failed to create dump file '%s' (error %d)"), szDumpPath, GetLastError());
        return retval; 
    }

    _MINIDUMP_EXCEPTION_INFORMATION ExInfo;

    ExInfo.ThreadId = ::GetCurrentThreadId();
    ExInfo.ExceptionPointers = pExceptionInfo;
    ExInfo.ClientPointers = NULL;

    if(s_miniDumpWriter(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL))
    {
        retval = EXCEPTION_EXECUTE_HANDLER;
    }
    else
    {
 //       TRACE2(_T("Failed to save dump file to '%s' (error %d)"), szDumpPath, GetLastError());
    }
    ::CloseHandle(hFile);

    if (s_pfnExpCallBack)
    {
        s_pfnExpCallBack(s_pContext);
    }

	return retval;
}