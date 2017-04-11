// MyThread.cpp : implementation file
//

#include "stdafx.h"
#include "MFCThread.h"
#include "MyThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
{
}

CMyThread::~CMyThread()
{
}
#include "MyDlg.h"
BOOL CMyThread::InitInstance()
{
	CMyDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();
	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
	//{{AFX_MSG_MAP(CMyThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyThread message handlers
