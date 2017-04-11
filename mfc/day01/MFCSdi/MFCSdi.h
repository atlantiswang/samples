// MFCSdi.h : main header file for the MFCSDI application
//

#if !defined(AFX_MFCSDI_H__9C9967B1_B3F6_4087_A9EA_4A7EAF8FDE5D__INCLUDED_)
#define AFX_MFCSDI_H__9C9967B1_B3F6_4087_A9EA_4A7EAF8FDE5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiApp:
// See MFCSdi.cpp for the implementation of this class
//

class CMFCSdiApp : public CWinApp
{
public:
	CMFCSdiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSdiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCSdiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDI_H__9C9967B1_B3F6_4087_A9EA_4A7EAF8FDE5D__INCLUDED_)
