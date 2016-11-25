//sc create myserver binpath= path
//sc delete myserver

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include "mylog.h"
#include <time.h>
DWORD dwThreadID;
SERVICE_STATUS_HANDLE hServiceStatus;
SERVICE_STATUS status;
TCHAR szServiceName[] = _T("myserver");

void MainProcess(LPVOID pParam)
{	
	FILE *fp = NULL;
	fp = fopen("c:/myserver.log", "a");
	if (!fp)
	{
		::MessageBox(NULL, "error", NULL, MB_OK);
		return ;
	}
	char buff[128] = {0};
	time_t tt;
	while (true)
	{
		time(&tt);
		sprintf(buff, "%d", tt);
		fwrite(buff, 1, strlen(buff), fp);
		fputs("\n",fp);
		fflush(fp);
		Sleep(1000);
	}
	fclose(fp);
	getchar();
}

void WINAPI ServiceStrl(DWORD dwOpcode)
{
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		status.dwCurrentState = SERVICE_STOP_PENDING;
		SetServiceStatus(hServiceStatus, &status);
		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		status.dwCurrentState = SERVICE_STOP_PENDING;
		SetServiceStatus(hServiceStatus, &status);
		break;
	default:
		break;
	}
}

void WINAPI ServiceMain()
{
	// Register the control request handler
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_CONTROL_INTERROGATE;

	//注册服务控制
	hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
	if (hServiceStatus == NULL)
	{
		return;
	}
	SetServiceStatus(hServiceStatus, &status);

	status.dwWin32ExitCode = S_OK;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
	status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hServiceStatus, &status);


	MainProcess(NULL);


	status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(hServiceStatus, &status);
}

BOOL SetAttribOFService(int number, int flag)
{
	HKEY hKey;
	char lpdata[MAX_PATH] = { 0 };
	DWORD len = MAX_PATH;
	DWORD type = 0;
	RegOpenKey(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\myserver"), &hKey);
	if (!hKey)
	{
		return FALSE;
	}
	LONG lRet = RegQueryValueEx(hKey, _T("FailureActions"), 0, &type, (BYTE*)lpdata, &len);

	lpdata[12] = 3;
	lpdata[16] = 'S';
	lpdata[18] = 'e';
	lpdata[number * 2 * 4 + 20] = flag;
	RegSetValueEx(hKey, _T("FailureActions"), 0, type, (BYTE*)lpdata, 44);
	RegCloseKey(hKey);
	return TRUE;
}

void Init()
{
	hServiceStatus = NULL;
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_CONTROL_INTERROGATE;
	status.dwWin32ExitCode = 0;
	status.dwServiceSpecificExitCode = 0;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
}

int startSrv(_TCHAR* lpCmdLine)
{

	//设置错误重启
	SetAttribOFService(0,1);

	Init();

	dwThreadID = ::GetCurrentThreadId();

	SERVICE_TABLE_ENTRY st[] =
	{
		{ szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
		{ NULL, NULL }
	};

	if (!::StartServiceCtrlDispatcher(st))
	{

		FILE *hFile = fopen("c:\\myserver.txt", "a+");

		fwrite("start error3\r\n", strlen("start error2\r\n"), 1, hFile);

		fclose(hFile);
	}
	return 0;
}

int _tmain(int argc, TCHAR *argv[])
{
	startSrv(argv[1]);
	return 0;
}