// low_init.h : main header file for the LOW_INIT application
//

#if !defined(AFX_LOW_INIT_H__84489C2D_4441_425C_831B_A5A3D751FD62__INCLUDED_)
#define AFX_LOW_INIT_H__84489C2D_4441_425C_831B_A5A3D751FD62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLow_initApp:
// See low_init.cpp for the implementation of this class
//

class CLow_initApp : public CWinApp
{
public:
	CLow_initApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLow_initApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLow_initApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOW_INIT_H__84489C2D_4441_425C_831B_A5A3D751FD62__INCLUDED_)
