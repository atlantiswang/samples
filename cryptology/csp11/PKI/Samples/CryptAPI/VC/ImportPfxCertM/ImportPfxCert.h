// ImportPfxCert.h : main header file for the IMPORTPFXCERT application
//

#if !defined(AFX_IMPORTPFXCERT_H__A0F15EB0_A974_40FB_968E_6BBC9C57AF97__INCLUDED_)
#define AFX_IMPORTPFXCERT_H__A0F15EB0_A974_40FB_968E_6BBC9C57AF97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImportPfxCertApp:
// See ImportPfxCert.cpp for the implementation of this class
//

class CImportPfxCertApp : public CWinApp
{
public:
	CImportPfxCertApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportPfxCertApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImportPfxCertApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTPFXCERT_H__A0F15EB0_A974_40FB_968E_6BBC9C57AF97__INCLUDED_)
