#if !defined(AFX_PAGE2_H__25D195AB_2B02_46F9_93BD_AA7577D1ECD5__INCLUDED_)
#define AFX_PAGE2_H__25D195AB_2B02_46F9_93BD_AA7577D1ECD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage2)

// Construction
public:
	CPage2();
	~CPage2();
	COLORREF m_Color;
// Dialog Data
	//{{AFX_DATA(CPage2)
	enum { IDD = IDD_PAGE2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage2)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage2)
	afx_msg void OnSetColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE2_H__25D195AB_2B02_46F9_93BD_AA7577D1ECD5__INCLUDED_)
