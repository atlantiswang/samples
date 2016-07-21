
// GetFlights.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "GetFlights.h"
#include "GetFlightsDlg.h"
#include "DbCenter.h"
#include <algorithm>
#include "common/CharConvert.h"


#include  <dbghelp.h> 
#pragma comment(lib,  "dbghelp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGetFlightsApp

BEGIN_MESSAGE_MAP(CGetFlightsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGetFlightsApp 构造

CGetFlightsApp::CGetFlightsApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中

	m_listIP.clear();
}


// 唯一的一个 CGetFlightsApp 对象

CGetFlightsApp theApp;

CGetFlightsApp::TTestIpThreadPara CGetFlightsApp::m_testIpThread1;
CGetFlightsApp::TTestIpThreadPara CGetFlightsApp::m_testIpThread2;

CWinThread*	CGetFlightsApp::m_pTestIpThread1 = NULL;
CWinThread*	CGetFlightsApp::m_pTestIpThread2 = NULL;

CZlProxyIp	CGetFlightsApp::m_tProxyIpBuf[2];
UINT CGetFlightsApp::m_uCurWriteBufId = 0;	
UINT CGetFlightsApp::m_uCurReadBufId = 0;
MBOOL	CGetFlightsApp::m_bWaitPrepareIp;

// CGetFlightsApp 初始化

BOOL CGetFlightsApp::InitInstance()
{
	//设置异常处理回调函数
	SetUnhandledExceptionFilter(ExceptionFilter);
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	if (0 != CDbCenter::GetInstance()->Connect())
	{
		AfxMessageBox(_T("数据库连接失败!"));
		return FALSE;
	}

	BOOL bWaitPrepareIp = TRUE;
	m_bWaitPrepareIp.Set(bWaitPrepareIp);
#ifndef CEAIR_MOBILE_E
	//启动线程检测ip是否可用
	m_testIpThread1.id = 0;
	m_testIpThread1.pThis = this;
	m_pTestIpThread1 = AfxBeginThread(ThreadTestProxyIP, &m_testIpThread1);
	m_pTestIpThread1->SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
	m_testIpThread2.id = 1;
	m_testIpThread2.pThis = this;
	m_pTestIpThread2 = AfxBeginThread(ThreadTestProxyIP, &m_testIpThread2);
	m_pTestIpThread2->SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
#endif

	CGetFlightsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

UINT CGetFlightsApp::ThreadTestProxyIP( LPVOID pParam )
{
	TTestIpThreadPara* pTestIpPara = (TTestIpThreadPara*)pParam;
	//CGetFlightsApp* app = (CGetFlightsApp*)pParam;
	CGetFlightsApp* app = pTestIpPara->pThis;
	CStringA straIP;
	//WinHttpClient http(L"https://passport.china-sss.com/Default/LoginFrame");
#ifdef CEAIR_MOBILE_E
	WinHttpClient http(L"http://www.ceair.com/");
#else
	#ifndef GET_KN_FLIGHT
		#ifndef GET_CA_FLIGHT
			#ifdef GET_AQ_FLIGHT
				WinHttpClient http(L"http://www.9air.com/");
			#else
					#ifdef GET_FLIGHT_FROM_NEW_SITE
						WinHttpClient http(L"http://www.ch.com/");
					#else
						WinHttpClient http(L"http://www.china-sss.com/");
					#endif//#ifdef GET_FLIGHT_FROM_NEW_SITE
			#endif
		#else //#ifdef GET_CA_FLIGHT
			WinHttpClient http(L"http://tuan.airchina.com/index.htm");
		#endif
	#else
		WinHttpClient http(L"http://www.flycua.com/");
	#endif
#endif//#ifdef CEAIR_MOBILE_E

	http.SetTimeouts(0,6000U,4000U,4000U);
	CStringA strLog;
	CString strTmp;

	wstring strHeaderBase = L"Accept: text/html";
	strHeaderBase += L"Accept-Language: zh-cn\r\n";
	strHeaderBase += L"User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET4.0C; .NET4.0E)\r\n";
	strHeaderBase += L"Content-Type: application/x-www-form-urlencoded\r\n";

	//wstring strHeaderBase = L"Accept: text/html, application/xhtml+xml,*/*";
	//strHeaderBase += L"Accept-Language: zh-CN\r\n";
	//strHeaderBase += L"User-Agent: Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/5.0; .NET CLR 2.0.50727; .NET4.0C; .NET4.0E)\r\n";
	//strHeaderBase += L"Content-Type: application/x-www-form-urlencoded\r\n";

	int nSize = 0;
	DWORD dwStartMs = 0;//毫秒
	DWORD dwEndMs = 0;
	DWORD dwMaxSpanMs = 4000;//毫秒
	bool bTimeOut = true;
	bool bIPValiable = false;

	int id = 0;
	eDbResult eRet = DBR_Fail;
	int nStartFlag = PROXY_IP_BUF_MAX_COUNT;
	DWORD dwCheckSpan = 2000;
	int nGetCount = 0;
	SGetIp* pGetIpBuf = new SGetIp[PROXY_IP_BUF_MAX_COUNT];
	SGetIp* pTmpGetIpBuf = pGetIpBuf;

	TRACE(_T("\r\n%d"), pTestIpPara->id);
_find:
	//app->m_lockListIP.Lock();
	//nSize = app->m_listIP.size();
	//app->m_lockListIP.Unlock();

	app->m_lockIpBuf.Lock();
	nSize = m_tProxyIpBuf[m_uCurWriteBufId].GetIpCount();
	app->m_lockIpBuf.Unlock();

	//TRACE(_T("\n test ip thread Id=%d, threadId=%d\n"), pTestIpPara->id, pTestIpPara->pThis->m_nThreadID);

	//strTmp.Format(_T("sss available ip count:%d"), nSize);
	//OutputDebugString(strTmp);

	if (m_bWaitPrepareIp.Get() && nSize >= nStartFlag)
	{
		HWND hWnd = CGetFlightsDlg::GetDlgConfigHwnd();
		if (NULL != hWnd)
		{
			BOOL bWait = FALSE;
			m_bWaitPrepareIp.Set(bWait);
			::PostMessage(hWnd, WM_PREPARE_PROXY_IP_PROGRESS, TRUE, 0);
		}
	}

	if (nSize >= nStartFlag)
	{
		//app->m_lockIpBuf.Lock();
		//m_tProxyIpBuf[m_uCurWriteBufId].dump();
		//app->m_lockIpBuf.Unlock();

		//strLog.Format("\n-------------------ip thread%d sleep", pTestIpPara->id);
		//OutputDebugStringA(strLog);

		Sleep(dwCheckSpan);

		//strLog.Format("\n~------------------ip thread%d wake", pTestIpPara->id);
		//OutputDebugStringA(strLog);

		if(0 == pTestIpPara->id)//只让一个线程负责切换ip buf
		{
			if (m_tProxyIpBuf[m_uCurReadBufId].IsAllIpUsed())
			{
				app->m_lockIpBuf.Lock();
				{
					m_uCurReadBufId = m_uCurWriteBufId;
					m_uCurWriteBufId = (m_uCurWriteBufId + 1) % MAX_PROXY_IP_OBJ;
					m_tProxyIpBuf[m_uCurWriteBufId].Reset();
				}
				app->m_lockIpBuf.Unlock();
				OutputDebugStringA("\n--------------------------------sss ip proxy ip buf switch");
			}
		}

		goto _find;
	}

	nGetCount = 0;
	//OutputDebugString(_T("从db中取出IP"));
	eRet = CDbCenter::GetInstance()->QueryProxyIP(pGetIpBuf, &nGetCount, PROXY_IP_BUF_MAX_COUNT, pTestIpPara->id);
	//OutputDebugString(_T("~~从db中取出IP"));

	if (DBR_Succ != eRet)
	{
		//OutputDebugStringA("\r\n没有查找到代理IP\r\n");
		goto _find;
	}
	pTmpGetIpBuf = pGetIpBuf;
	for (int i = 0; i < nGetCount; i++)
	{
		id = pTmpGetIpBuf->iRowId;
		straIP.Format("%s", pTmpGetIpBuf->szIpBuf);
		pTmpGetIpBuf++;
		http.SetProxy(wstring(CStrA2CStrW(straIP).GetBuffer(0)));

		//strLog.Format("sss已有%d，测试IP:%s",nSize, straIP);
		//OutputDebugStringA(strLog);

		bTimeOut = true;
		dwStartMs = GetTickCount();
		//OutputDebugString(_T("\r\nGetResponseStatusCode\r\n"));
		http.SendHttpRequest(L"GET");
		wstring strcode = http.GetResponseStatusCode();
		dwEndMs = GetTickCount();
		//wstring httpResponseContent = http.GetResponseContent();
		//if (httpResponseContent.length() > 100)
		//	bIPValiable = true;
		//else 
		//	bIPValiable = false;

		if ((dwEndMs - dwStartMs) > dwMaxSpanMs)
			bTimeOut = true;
		else
			bTimeOut = false;

		//可用的ip加1，不可用的加10
		//if (0 != strcode.compare(L"200") || bTimeOut || !bIPValiable)
		if ((0 != strcode.compare(L"200")) || bTimeOut)
		{
			//strLog.Format("\r\n无效IP:%s\r\n",straIP);
			//OutputDebugStringA(strLog);
			CDbCenter::GetInstance()->UpdateProxyUsedCount(id, 30);
			//		theApp.AddLog(CStrA2CStrT(strLog));
		}
		else
		{
			//OutputDebugString(_T("\r\n～～Ip有效\r\n"));
			CDbCenter::GetInstance()->UpdateProxyUsedCount(id, 1);
			wstring wstrIp(CStrA2CStrW(straIP).GetBuffer(0));

			app->m_lockIpBuf.Lock();
			m_tProxyIpBuf[m_uCurWriteBufId].AppendProxyIp(straIP.GetBuffer(0));
			app->m_lockIpBuf.Unlock();	
		}

		app->m_lockIpBuf.Lock();
		nSize = m_tProxyIpBuf[m_uCurWriteBufId].GetIpCount();
		app->m_lockIpBuf.Unlock();
		if (m_bWaitPrepareIp.Get())
		{
			HWND hWnd = CGetFlightsDlg::GetDlgConfigHwnd();
			::PostMessage(hWnd, WM_PREPARE_PROXY_IP_PROGRESS, FALSE, nSize);
		}
		if (nSize >= nStartFlag )
			break;
	}
	Sleep(1);
	goto _find;

	delete [] pGetIpBuf;
	pGetIpBuf = NULL;
	return 0;
}

std::wstring CGetFlightsApp::GetValidIP()
{
	int nCount = 0;
	char szIp[PROXY_IP_MAX_CHAR+1] = {0};

	m_lockIpBuf.Lock();
	m_tProxyIpBuf[m_uCurReadBufId].GetProxyIp(szIp, PROXY_IP_MAX_CHAR);
	m_lockIpBuf.Unlock();

	CCharConvert chConvert;
	std::string strIp(szIp);
	std::wstring wstrip = chConvert.StringToWstring(strIp);

	return wstrip;


//	std::wstring strwip;
//_ReFind:
//	m_lockListIP.Lock();
//	nCount = m_listIP.size();
//
//	if (nCount > 0)
//	{
//		strwip = m_listIP.front();
//		m_listIP.pop_front();
//		m_listIP.push_back(strwip);
//		m_lockListIP.Unlock();
//	}
//	else
//	{
//		m_lockListIP.Unlock();
//		Sleep(1);
//		goto _ReFind;
//	}
//
//	return strwip;
}

LONG WINAPI CGetFlightsApp::ExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	CString strPath = CDataProcess::GetInstance()->GetExePath() + "\\DMP\\";
	CreateDirectory(strPath,NULL);
	CString   strDumpFile; 
	CTime t = CTime::GetCurrentTime();
	strDumpFile.Format(_T("C%d-%02d-%02d-%02d%02d%02d"),t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	strDumpFile += ".dmp"; 
	strPath += strDumpFile;
	HANDLE hFile = CreateFile(strPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{ 
		MINIDUMP_EXCEPTION_INFORMATION ExInfo; 

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = ExceptionInfo;
		ExInfo.ClientPointers = NULL;

		//   write   the   dump
		BOOL bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
		if (bOK)
		{
			AfxMessageBox(_T("程序出现了异常，需要退出！\r\n请把下面的文件发给开发人员，以便解决问题：\r\n" + strPath));
		}
		CloseHandle(hFile); 
	} 

	theApp.PostThreadMessage(WM_QUIT,0,0);
	return EXCEPTION_EXECUTE_HANDLER;
}