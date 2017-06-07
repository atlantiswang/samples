// UseOcxDlg.h : header file
//
//{{AFX_INCLUDES()
#include "wmpplayer4.h"
//}}AFX_INCLUDES

#if !defined(AFX_USEOCXDLG_H__B262900D_B452_4823_8C34_B99A11D885DE__INCLUDED_)
#define AFX_USEOCXDLG_H__B262900D_B452_4823_8C34_B99A11D885DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUseOcxDlg dialog

class CUseOcxDlg : public CDialog
{
// Construction
public:
	CUseOcxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUseOcxDlg)
	enum { IDD = IDD_USEOCX_DIALOG };
	CWMPPlayer4	m_wndPlayer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseOcxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUseOcxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEOCXDLG_H__B262900D_B452_4823_8C34_B99A11D885DE__INCLUDED_)
