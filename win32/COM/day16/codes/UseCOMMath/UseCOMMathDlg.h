// UseCOMMathDlg.h : header file
//

#if !defined(AFX_USECOMMATHDLG_H__D361D938_4005_4D8D_92AB_3496D280C749__INCLUDED_)
#define AFX_USECOMMATHDLG_H__D361D938_4005_4D8D_92AB_3496D280C749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUseCOMMathDlg dialog

class CUseCOMMathDlg : public CDialog
{
// Construction
public:
	CUseCOMMathDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUseCOMMathDlg)
	enum { IDD = IDD_USECOMMATH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseCOMMathDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUseCOMMathDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnCcomptr();
	afx_msg void OnCcomqiptr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USECOMMATHDLG_H__D361D938_4005_4D8D_92AB_3496D280C749__INCLUDED_)
