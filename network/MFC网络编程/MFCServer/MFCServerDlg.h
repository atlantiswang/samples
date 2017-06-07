// MFCServerDlg.h : header file
//

#if !defined(AFX_MFCSERVERDLG_H__1F92E3DA_9A35_4712_9588_5CE8D8A47632__INCLUDED_)
#define AFX_MFCSERVERDLG_H__1F92E3DA_9A35_4712_9588_5CE8D8A47632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCServerDlg dialog
#include "ServerSocket.h"
class CMFCServerDlg : public CDialog
{
// Construction
public:
	CMFCServerDlg(CWnd* pParent = NULL);	// standard constructor
	CServerSocket m_server;
// Dialog Data
	//{{AFX_DATA(CMFCServerDlg)
	enum { IDD = IDD_MFCSERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSERVERDLG_H__1F92E3DA_9A35_4712_9588_5CE8D8A47632__INCLUDED_)
