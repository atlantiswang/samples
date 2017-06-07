// AutoMath.h : main header file for the AUTOMATH application
//

#if !defined(AFX_AUTOMATH_H__0A9203E7_F3BB_43B4_9319_E1604A829B76__INCLUDED_)
#define AFX_AUTOMATH_H__0A9203E7_F3BB_43B4_9319_E1604A829B76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoMathApp:
// See AutoMath.cpp for the implementation of this class
//

class CAutoMathApp : public CWinApp
{
public:
	CAutoMathApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoMathApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CAutoMathApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOMATH_H__0A9203E7_F3BB_43B4_9319_E1604A829B76__INCLUDED_)
