// MFCCtrlDlg.h : header file
//

#if !defined(AFX_MFCCTRLDLG_H__0AFA5727_DEBF_4377_BD01_2D9ECE193C79__INCLUDED_)
#define AFX_MFCCTRLDLG_H__0AFA5727_DEBF_4377_BD01_2D9ECE193C79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCCtrlDlg dialog

class CMFCCtrlDlg : public CDialog
{
// Construction
public:
	CMFCCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCCtrlDlg)
	enum { IDD = IDD_MFCCTRL_DIALOG };
	CListBox	m_wndList5;
	CListBox	m_wndList1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCTRLDLG_H__0AFA5727_DEBF_4377_BD01_2D9ECE193C79__INCLUDED_)
