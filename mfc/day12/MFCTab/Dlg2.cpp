// Dlg2.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTab.h"
#include "Dlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog


CDlg2::CDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg2, CDialog)
	//{{AFX_MSG_MAP(CDlg2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg2 message handlers
