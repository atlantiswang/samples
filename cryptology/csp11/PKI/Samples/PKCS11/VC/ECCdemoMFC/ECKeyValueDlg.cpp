// ECKeyValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eccdemomfc.h"
#include "ECKeyValueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CECKeyValueDlg dialog


CECKeyValueDlg::CECKeyValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CECKeyValueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CECKeyValueDlg)
	m_strPublic = _T("");
	m_strPrivate = _T("");
	//}}AFX_DATA_INIT
}


void CECKeyValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CECKeyValueDlg)
	DDX_Text(pDX, IDC_EDIT_PUBLIC, m_strPublic);
	DDX_Text(pDX, IDC_EDIT_PRIVATE, m_strPrivate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CECKeyValueDlg, CDialog)
	//{{AFX_MSG_MAP(CECKeyValueDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECKeyValueDlg message handlers

void CECKeyValueDlg::OnOK() 
{
	CDialog::OnOK();
	
}
