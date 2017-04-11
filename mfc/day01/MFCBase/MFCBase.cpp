#include "stdafx.h"
class CMyFrameWnd : public CFrameWnd
{
};
class CMyWinApp : public CWinApp
{
public:
	CMyWinApp();
	virtual BOOL InitInstance();
	virtual BOOL InitApplication();
	virtual int Run();
	virtual BOOL OnIdle( LONG lCount );
	virtual int ExitInstance();
};
int CMyWinApp::ExitInstance()
{
	AfxMessageBox("善后处理");
	return CWinApp::ExitInstance();
}
BOOL CMyWinApp::OnIdle(LONG lCount)
{
//	AfxMessageBox("空闲处理");
	return CWinApp::OnIdle(lCount);
}
BOOL CMyWinApp::InitApplication()
{
	AfxMessageBox("初始化");
	return CWinApp::InitApplication();
}
int CMyWinApp::Run()
{
	AfxMessageBox("消息循环");
	return CWinApp::Run();
}
CMyWinApp::CMyWinApp(){}

CMyWinApp theApp;//爆破点
BOOL CMyWinApp::InitInstance()
{//此函数的this为&theApp
	CMyFrameWnd *pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCBase");
	m_pMainWnd = pFrame;
	pFrame ->ShowWindow(SW_SHOW);
	pFrame ->UpdateWindow();
	return TRUE;
}