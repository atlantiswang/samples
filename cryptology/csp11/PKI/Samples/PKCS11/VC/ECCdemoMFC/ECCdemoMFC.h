// ECCdemoMFC.h : main header file for the ECCDEMOMFC application
//

#if !defined(AFX_ECCDEMOMFC_H__816680A0_6214_4F91_8E8A_E66D963DFCE2__INCLUDED_)
#define AFX_ECCDEMOMFC_H__816680A0_6214_4F91_8E8A_E66D963DFCE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CECCdemoMFCApp:
// See ECCdemoMFC.cpp for the implementation of this class
//

class CECCdemoMFCApp : public CWinApp
{
public:
	CECCdemoMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCdemoMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CECCdemoMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCDEMOMFC_H__816680A0_6214_4F91_8E8A_E66D963DFCE2__INCLUDED_)
