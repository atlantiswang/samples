// MFCThread2.h : main header file for the MFCTHREAD2 application
//

#if !defined(AFX_MFCTHREAD2_H__131204F7_2FB1_487C_894C_2BDCDE65CD74__INCLUDED_)
#define AFX_MFCTHREAD2_H__131204F7_2FB1_487C_894C_2BDCDE65CD74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCThread2App:
// See MFCThread2.cpp for the implementation of this class
//

class CMFCThread2App : public CWinApp
{
public:
	CMFCThread2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCThread2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCThread2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTHREAD2_H__131204F7_2FB1_487C_894C_2BDCDE65CD74__INCLUDED_)
