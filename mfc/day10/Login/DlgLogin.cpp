// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "Login.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
	m_ssUserName = _T("");
	m_sPassword = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Text(pDX, IDC_USER_NAME, m_ssUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

void CDlgLogin::OnOK() 
{
	// 登录的验证
	UpdateData(TRUE);
	if(m_ssUserName=="csd1404"&&m_sPassword=="456")
	{
		CDialog::OnOK();
	}
	else
	{
		MessageBox("登录名称或者密码错误，请重新登录");
	}
}
