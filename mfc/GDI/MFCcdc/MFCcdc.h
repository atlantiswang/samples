// MFCcdc.h : main header file for the MFCCDC application
//

#if !defined(AFX_MFCCDC_H__252828D3_F177_42D4_A580_D35095DAB3F2__INCLUDED_)
#define AFX_MFCCDC_H__252828D3_F177_42D4_A580_D35095DAB3F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcApp:
// See MFCcdc.cpp for the implementation of this class
//

class CMFCcdcApp : public CWinApp
{
public:
	CMFCcdcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCcdcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCcdcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCDC_H__252828D3_F177_42D4_A580_D35095DAB3F2__INCLUDED_)
