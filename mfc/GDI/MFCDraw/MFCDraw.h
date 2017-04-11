// MFCDraw.h : main header file for the MFCDRAW application
//

#if !defined(AFX_MFCDRAW_H__6F647CF0_A57D_479C_B2D4_7F5533F027BD__INCLUDED_)
#define AFX_MFCDRAW_H__6F647CF0_A57D_479C_B2D4_7F5533F027BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawApp:
// See MFCDraw.cpp for the implementation of this class
//

class CMFCDrawApp : public CWinApp
{
public:
	CMFCDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCDrawApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDRAW_H__6F647CF0_A57D_479C_B2D4_7F5533F027BD__INCLUDED_)
