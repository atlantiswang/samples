// DlgModel.cpp : implementation file
//

#include "stdafx.h"
#include "SDI.h"
#include "DlgModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgModel dialog


CDlgModel::CDlgModel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgModel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgModel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgModel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgModel, CDialog)
	//{{AFX_MSG_MAP(CDlgModel)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgModel message handlers
