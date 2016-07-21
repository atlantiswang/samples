
// GetFlights.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include <list>
#include <string>
#include "ZlProxyIp.h"
#include "common/xgmvar.h"
// CGetFlightsApp:
// 有关此类的实现，请参阅 GetFlights.cpp
//
class CGetFlightsApp : public CWinApp
{
public:
	CGetFlightsApp();

// 重写
public:
	virtual BOOL InitInstance();
	static LONG WINAPI ExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);

public:
	std::list<std::wstring>	m_listIP;
	CCriticalSection	m_lockListIP;

	std::wstring GetValidIP();

// 实现

	DECLARE_MESSAGE_MAP()

	//测试代理ip
	static UINT ThreadTestProxyIP( LPVOID pParam );

	typedef struct __tagTestIpThreadPara
	{
		int		id;
		CGetFlightsApp* pThis;
	}TTestIpThreadPara;

	static CWinThread*		m_pTestIpThread1;
	static CWinThread*		m_pTestIpThread2;
	static TTestIpThreadPara m_testIpThread1;
	static TTestIpThreadPara m_testIpThread2;

	static CZlProxyIp	m_tProxyIpBuf[2];
	static UINT		m_uCurWriteBufId;
	static UINT		m_uCurReadBufId;
	CCriticalSection	m_lockIpBuf;
	static MBOOL	m_bWaitPrepareIp;

};

extern CGetFlightsApp theApp;