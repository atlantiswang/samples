#if !defined(AFX_PINDLG_H__D3238581_98C0_40E6_93DF_6E50E2CCB9CE__INCLUDED_)
#define AFX_PINDLG_H__D3238581_98C0_40E6_93DF_6E50E2CCB9CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PINDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPINDlg dialog

class CPINDlg : public CDialog
{
// Construction
public:
	CPINDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPINDlg)
	enum { IDD = IDD_PIN };
	CString	m_PIN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPINDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPINDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINDLG_H__D3238581_98C0_40E6_93DF_6E50E2CCB9CE__INCLUDED_)
