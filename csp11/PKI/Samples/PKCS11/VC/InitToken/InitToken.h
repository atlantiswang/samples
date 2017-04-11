// InitToken.h : main header file for the INITTOKEN application
//

#if !defined(AFX_INITTOKEN_H__455F37BF_A270_4D98_A795_E4FE590D348D__INCLUDED_)
#define AFX_INITTOKEN_H__455F37BF_A270_4D98_A795_E4FE590D348D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInitTokenApp:
// See InitToken.cpp for the implementation of this class
//

class CInitTokenApp : public CWinApp
{
public:
	CInitTokenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitTokenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInitTokenApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITTOKEN_H__455F37BF_A270_4D98_A795_E4FE590D348D__INCLUDED_)
