// LabelProp.h : main header file for the LABELPROP application
//

#if !defined(AFX_LABELPROP_H__835AFE63_6770_40DB_8780_961689110C4C__INCLUDED_)
#define AFX_LABELPROP_H__835AFE63_6770_40DB_8780_961689110C4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLabelPropApp:
// See LabelProp.cpp for the implementation of this class
//

class CLabelPropApp : public CWinApp
{
public:
	CLabelPropApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelPropApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLabelPropApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELPROP_H__835AFE63_6770_40DB_8780_961689110C4C__INCLUDED_)
