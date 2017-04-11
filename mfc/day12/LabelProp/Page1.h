#if !defined(AFX_PAGE1_H__61C7222C_6C40_4CD2_9D03_D91D6AA5D879__INCLUDED_)
#define AFX_PAGE1_H__61C7222C_6C40_4CD2_9D03_D91D6AA5D879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

class CPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage1)

// Construction
public:
	CPage1();
	~CPage1();

// Dialog Data
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_PAGE1 };
	int		m_nLineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage1)
	afx_msg void OnChangeLineWidth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__61C7222C_6C40_4CD2_9D03_D91D6AA5D879__INCLUDED_)
