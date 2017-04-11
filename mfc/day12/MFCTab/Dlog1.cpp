// Dlog1.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTab.h"
#include "Dlog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlog1 dialog


CDlog1::CDlog1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlog1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlog1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlog1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlog1, CDialog)
	//{{AFX_MSG_MAP(CDlog1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlog1 message handlers
