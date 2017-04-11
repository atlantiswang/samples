// DlgDDX.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
//对话框类
class CMyDlg : public CDialog
{
public:
	CMyDlg():CDialog(IDD_DIALOG1){} 
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual void OnOK();
protected:
	CButton m_btnOK;//与OK绑定的成员变量
	CString m_sText;//与文本框绑定的值类型的成员变量
};
void CMyDlg::OnOK()
{
	//将用户在控件中输入的值传递给变量
	UpdateData(TRUE);
	MessageBox(m_sText);
	CDialog::OnOK();
}
void CMyDlg::DoDataExchange( CDataExchange* pDX )
{
	//变量m_btnOK与OK按钮绑定
	DDX_Control(pDX,IDOK,m_btnOK);
	//值类型的绑定
	DDX_Text(pDX,IDC_EDIT1,m_sText);
}
BOOL CMyDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
	{
		return FALSE;
	}
	//控件的初始化操作
	CWnd *pWnd=GetDlgItem(IDCANCEL);
	pWnd->EnableWindow(FALSE);
	//使用DDX操作OK按钮
	m_btnOK.MoveWindow(0,0,100,100);
	m_btnOK.SetWindowText("DDXOK");
	//值类型的操作
	m_sText="Hello World";
	UpdateData(FALSE);
	return TRUE;
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
	CMyDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();
	return TRUE;
}



