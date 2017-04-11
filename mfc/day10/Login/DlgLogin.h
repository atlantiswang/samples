#if !defined(AFX_DLGLOGIN_H__BEC06754_5D8C_4FD6_AF8F_569697FA17C9__INCLUDED_)
#define AFX_DLGLOGIN_H__BEC06754_5D8C_4FD6_AF8F_569697FA17C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

class CDlgLogin : public CDialog
{
// Construction
public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_DIALOG1 };
	CString	m_ssUserName;
	CString	m_sPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__BEC06754_5D8C_4FD6_AF8F_569697FA17C9__INCLUDED_)
