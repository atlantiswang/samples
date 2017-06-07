// UseCOMMath.h : main header file for the USECOMMATH application
//

#if !defined(AFX_USECOMMATH_H__18BE1A5A_25D4_42D1_A587_0C7C849304DB__INCLUDED_)
#define AFX_USECOMMATH_H__18BE1A5A_25D4_42D1_A587_0C7C849304DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUseCOMMathApp:
// See UseCOMMath.cpp for the implementation of this class
//

class CUseCOMMathApp : public CWinApp
{
public:
	CUseCOMMathApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseCOMMathApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUseCOMMathApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USECOMMATH_H__18BE1A5A_25D4_42D1_A587_0C7C849304DB__INCLUDED_)
