// MFCCtrl.h : main header file for the MFCCTRL application
//

#if !defined(AFX_MFCCTRL_H__2AFE0105_25FC_42DC_A085_98D9383FF757__INCLUDED_)
#define AFX_MFCCTRL_H__2AFE0105_25FC_42DC_A085_98D9383FF757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCCtrlApp:
// See MFCCtrl.cpp for the implementation of this class
//

class CMFCCtrlApp : public CWinApp
{
public:
	CMFCCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCTRL_H__2AFE0105_25FC_42DC_A085_98D9383FF757__INCLUDED_)
