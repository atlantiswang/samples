// UseDispMath.h : main header file for the USEDISPMATH application
//

#if !defined(AFX_USEDISPMATH_H__FF8B24CA_5B71_46DF_A7A5_AFCCF9C6D2F1__INCLUDED_)
#define AFX_USEDISPMATH_H__FF8B24CA_5B71_46DF_A7A5_AFCCF9C6D2F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUseDispMathApp:
// See UseDispMath.cpp for the implementation of this class
//

class CUseDispMathApp : public CWinApp
{
public:
	CUseDispMathApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseDispMathApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUseDispMathApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEDISPMATH_H__FF8B24CA_5B71_46DF_A7A5_AFCCF9C6D2F1__INCLUDED_)
