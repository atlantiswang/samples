// UseMcd.h : main header file for the USEMCD application
//

#if !defined(AFX_USEMCD_H__4B1A256E_36C9_4022_85C5_63A093D45F1C__INCLUDED_)
#define AFX_USEMCD_H__4B1A256E_36C9_4022_85C5_63A093D45F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUseMcdApp:
// See UseMcd.cpp for the implementation of this class
//

class CUseMcdApp : public CWinApp
{
public:
	CUseMcdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseMcdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUseMcdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEMCD_H__4B1A256E_36C9_4022_85C5_63A093D45F1C__INCLUDED_)
