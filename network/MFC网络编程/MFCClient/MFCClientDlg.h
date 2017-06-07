// MFCClientDlg.h : header file
//

#if !defined(AFX_MFCCLIENTDLG_H__2E3E43A2_E1D9_4787_ABB1_68BD71B73D6B__INCLUDED_)
#define AFX_MFCCLIENTDLG_H__2E3E43A2_E1D9_4787_ABB1_68BD71B73D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCClientDlg dialog

class CMFCClientDlg : public CDialog
{
// Construction
public:
	CMFCClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCClientDlg)
	enum { IDD = IDD_MFCCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSendFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCLIENTDLG_H__2E3E43A2_E1D9_4787_ABB1_68BD71B73D6B__INCLUDED_)
