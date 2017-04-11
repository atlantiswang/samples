// low_init.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "formatkey.h"
#include "formatkeydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLow_initApp

BEGIN_MESSAGE_MAP(CLow_initApp, CWinApp)
	//{{AFX_MSG_MAP(CLow_initApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLow_initApp construction

CLow_initApp::CLow_initApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLow_initApp object

CLow_initApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLow_initApp initialization

BOOL CLow_initApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CK_RV rv;
	// Load PKCS#11 library
	rv = C_Initialize(NULL);
	if(CKR_OK != rv)
	{
		AfxMessageBox("Can't Load PKCS#11 Library!", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CFormatKeyDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	C_Finalize(NULL);
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
