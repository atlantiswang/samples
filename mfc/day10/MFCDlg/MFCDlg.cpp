#include "stdafx.h"
#include "resource.h"
//对话框类
class CMyDlg : public CDialog
{
public:
	CMyDlg():CDialog(IDD_DIALOG1){}
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
void CMyDlg::OnOK()
{
	DestroyWindow();
}
void CMyDlg::OnCancel()
{
	DestroyWindow();
};
void CMyDlg::PostNcDestroy()
{
	delete this;
}
//应用程序类
class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	/*
	//模式对话框
	CMyDlg dlg;
	m_pMainWnd =&dlg;
	dlg.DoModal();
	*/
	//非模式对话框
	CMyDlg *pDlg = new CMyDlg;
	pDlg->Create(IDD_DIALOG1);
	m_pMainWnd=pDlg;
	pDlg->ShowWindow(SW_SHOW);
	pDlg->UpdateWindow();

	return TRUE;
}