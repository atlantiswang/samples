// MFCMdiWizard.h : main header file for the MFCMDIWIZARD application
//

#if !defined(AFX_MFCMDIWIZARD_H__59A85B08_C72E_4548_BEAA_C43C41596AD9__INCLUDED_)
#define AFX_MFCMDIWIZARD_H__59A85B08_C72E_4548_BEAA_C43C41596AD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardApp:
// See MFCMdiWizard.cpp for the implementation of this class
//

class CMFCMdiWizardApp : public CWinApp
{
public:
	CMFCMdiWizardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMdiWizardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCMdiWizardApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIWIZARD_H__59A85B08_C72E_4548_BEAA_C43C41596AD9__INCLUDED_)
