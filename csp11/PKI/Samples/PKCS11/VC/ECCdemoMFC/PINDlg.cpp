// PINDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ECCdemoMFC.h"
#include "PINDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPINDlg dialog


CPINDlg::CPINDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPINDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPINDlg)
	m_PIN = _T("");
	//}}AFX_DATA_INIT
}


void CPINDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPINDlg)
	DDX_Text(pDX, IDC_EDIT_PIN, m_PIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPINDlg, CDialog)
	//{{AFX_MSG_MAP(CPINDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPINDlg message handlers
