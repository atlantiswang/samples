// InitTokenDlg.h : header file
//

#if !defined(AFX_INITTOKENDLG_H__EE6FF5B1_7DAF_46DA_8769_06B7F4CE3C80__INCLUDED_)
#define AFX_INITTOKENDLG_H__EE6FF5B1_7DAF_46DA_8769_06B7F4CE3C80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInitTokenDlg dialog

class CInitTokenDlg : public CDialog
{
// Construction
public:
	CInitTokenDlg(CWnd* pParent = NULL);	// standard constructor
	bool ConnectKey();
	void ViewErrorMsg(CK_RV rv);
	void ChangeEditState();
	void ReadTokenInfo();
	void DisplayTokenInfo();
	~CInitTokenDlg();

// Dialog Data
	//{{AFX_DATA(CInitTokenDlg)
	enum { IDD = IDD_INITTOKEN_DIALOG };
	CEdit	m_ctrlOleUserPin;
	CEdit	m_ctrlUserPin;
	CEdit	m_ctrlSoPin;
	CEdit	m_ctrlConfUserPin;
	CString	m_strConfUserPIN;
	CString	m_strSoPIN;
	CString	m_strUserPIN;
	CString	m_strTokenName;
	CString	m_strCurrentTokenName;
	CString	m_strOldUserPIn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitTokenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CK_SLOT_ID_PTR m_pSlotList;
	CK_VOID_PTR m_pApplication;
	CK_ULONG m_ulSlotId;

	// Generated message map functions
	//{{AFX_MSG(CInitTokenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditSoPin();
	afx_msg void OnChangeEditTokenName();
	afx_msg void OnChangeEditUserPin();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEditConfUserPin();
	afx_msg void OnChangeEditOldUserPin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ULONG m_ulMinPin;
	ULONG m_ulMaxPin;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITTOKENDLG_H__EE6FF5B1_7DAF_46DA_8769_06B7F4CE3C80__INCLUDED_)
