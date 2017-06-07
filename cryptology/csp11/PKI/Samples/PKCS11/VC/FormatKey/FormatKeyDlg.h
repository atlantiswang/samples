// low_initDlg.h : header file
//

#if !defined(AFX_LOW_INITDLG_H__1D2A1DC6_2928_4EA2_A8AC_9E647EDC27F8__INCLUDED_)
#define AFX_LOW_INITDLG_H__1D2A1DC6_2928_4EA2_A8AC_9E647EDC27F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFormatKeyDlg dialog

class CFormatKeyDlg : public CDialog
{
// Construction
public:
	CFormatKeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFormatKeyDlg)
	enum { IDD = IDD_LOW_INIT_DIALOG };
	CButton	m_btnOk;
	CString	m_strSoPin;
	CString	m_strTokenName;
	CString	m_strUserPin;
	CString	m_strResult;
	CString	m_strTotalResult;
	int	m_ucSoPinEc;
	int	m_ucUserPinEc;
	//}}AFX_DATA

protected:

	DWORD m_dwSucceededCount;
	DWORD m_dwFailedCount;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFormatKeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOW_INITDLG_H__1D2A1DC6_2928_4EA2_A8AC_9E647EDC27F8__INCLUDED_)
