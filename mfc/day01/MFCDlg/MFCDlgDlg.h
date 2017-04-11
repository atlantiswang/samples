// MFCDlgDlg.h : header file
//

#if !defined(AFX_MFCDLGDLG_H__546A8E5B_FC2A_4114_B816_8307A67FE8E7__INCLUDED_)
#define AFX_MFCDLGDLG_H__546A8E5B_FC2A_4114_B816_8307A67FE8E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCDlgDlg dialog

class CMFCDlgDlg : public CDialog
{
// Construction
public:
	CMFCDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCDlgDlg)
	enum { IDD = IDD_MFCDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDLGDLG_H__546A8E5B_FC2A_4114_B816_8307A67FE8E7__INCLUDED_)
