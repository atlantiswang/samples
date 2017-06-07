// TestAutomationDlg.h : header file
//

#if !defined(AFX_TESTAUTOMATIONDLG_H__2CD241EE_D908_4FCE_BCB2_8834D8E7FBB1__INCLUDED_)
#define AFX_TESTAUTOMATIONDLG_H__2CD241EE_D908_4FCE_BCB2_8834D8E7FBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestAutomationDlg dialog

class CTestAutomationDlg : public CDialog
{
// Construction
public:
	CTestAutomationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestAutomationDlg)
	enum { IDD = IDD_TESTAUTOMATION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAutomationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestAutomationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAutoword();
	afx_msg void OnAutomath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAUTOMATIONDLG_H__2CD241EE_D908_4FCE_BCB2_8834D8E7FBB1__INCLUDED_)
