// MyDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "SingleWnd.h"
#include "MyDlg1.h"
#include "SingleWndDlg.h"

// CMyDlg1 对话框

IMPLEMENT_DYNAMIC(CMyDlg1, CDialog)

CMyDlg1::CMyDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg1::IDD, pParent)
{
	m_style = false;
}

CMyDlg1::~CMyDlg1()
{
}

void CMyDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDlg1, CDialog)
	ON_BN_CLICKED(IDOK, &CMyDlg1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyDlg1::OnBnClickedCancel)
END_MESSAGE_MAP()



void CMyDlg1::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialog::PostNcDestroy();

	if (m_style ==DOMAL)
		return ;
	CSingleWndDlg *pDlg = (CSingleWndDlg*)AfxGetApp()->m_pMainWnd;
	pDlg->m_pDlgShowing = NULL;
	delete this;
}

void CMyDlg1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_style == DOMAL)
		OnOK();
	else
		DestroyWindow();
}

void CMyDlg1::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_style == DOMAL)
		OnCancel();
	else
		DestroyWindow();
}
