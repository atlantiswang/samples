#if !defined(AFX_LABELSHEET_H__5EE1D2DB_7D9E_4C86_8528_85E70FA6C04A__INCLUDED_)
#define AFX_LABELSHEET_H__5EE1D2DB_7D9E_4C86_8528_85E70FA6C04A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LabelSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLabelSheet
#include "Page1.h"
#include "Page2.h"
class CLabelSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CLabelSheet)

// Construction
public:
	CLabelSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CLabelSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPage1 m_page1;
	CPage2 m_page2;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLabelSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLabelSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELSHEET_H__5EE1D2DB_7D9E_4C86_8528_85E70FA6C04A__INCLUDED_)
