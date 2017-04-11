// MFCTab.h : main header file for the MFCTAB application
//

#if !defined(AFX_MFCTAB_H__434E2F27_8897_44ED_9452_764C8C89DBE7__INCLUDED_)
#define AFX_MFCTAB_H__434E2F27_8897_44ED_9452_764C8C89DBE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCTabApp:
// See MFCTab.cpp for the implementation of this class
//

class CMFCTabApp : public CWinApp
{
public:
	CMFCTabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCTabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCTabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTAB_H__434E2F27_8897_44ED_9452_764C8C89DBE7__INCLUDED_)
