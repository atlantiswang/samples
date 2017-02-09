// MFCDlg.h : main header file for the MFCDLG application
//

#if !defined(AFX_MFCDLG_H__F9982AB0_A310_4A12_B64E_714499AE298B__INCLUDED_)
#define AFX_MFCDLG_H__F9982AB0_A310_4A12_B64E_714499AE298B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCDlgApp:
// See MFCDlg.cpp for the implementation of this class
//

class CMFCDlgApp : public CWinApp
{
public:
	CMFCDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDLG_H__F9982AB0_A310_4A12_B64E_714499AE298B__INCLUDED_)
