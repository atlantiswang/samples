// TestAutomation.h : main header file for the TESTAUTOMATION application
//

#if !defined(AFX_TESTAUTOMATION_H__8D1C1BC2_AC12_4E85_89DA_28217200A26E__INCLUDED_)
#define AFX_TESTAUTOMATION_H__8D1C1BC2_AC12_4E85_89DA_28217200A26E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestAutomationApp:
// See TestAutomation.cpp for the implementation of this class
//

class CTestAutomationApp : public CWinApp
{
public:
	CTestAutomationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAutomationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestAutomationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAUTOMATION_H__8D1C1BC2_AC12_4E85_89DA_28217200A26E__INCLUDED_)
