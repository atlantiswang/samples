// UseMcdDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mcd.h"
//}}AFX_INCLUDES

#if !defined(AFX_USEMCDDLG_H__18DFE1C4_42E6_46B1_ACCB_6B336DA4B571__INCLUDED_)
#define AFX_USEMCDDLG_H__18DFE1C4_42E6_46B1_ACCB_6B336DA4B571__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUseMcdDlg dialog

class CUseMcdDlg : public CDialog
{
// Construction
public:
	CUseMcdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUseMcdDlg)
	enum { IDD = IDD_USEMCD_DIALOG };
	CMcd	m_wndMcd;
	long	m_num1;
	long	m_num2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseMcdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUseMcdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnComputer();
	afx_msg void OnDirection();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEMCDDLG_H__18DFE1C4_42E6_46B1_ACCB_6B336DA4B571__INCLUDED_)
