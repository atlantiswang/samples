// ECCdemoMFCDlg.h : header file
//

#if !defined(AFX_ECCDEMOMFCDLG_H__53295BE9_72D6_4E71_BFA7_578D2ABBC15B__INCLUDED_)
#define AFX_ECCDEMOMFCDLG_H__53295BE9_72D6_4E71_BFA7_578D2ABBC15B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pkcs11/cryptoki_ext.h>

/////////////////////////////////////////////////////////////////////////////
// CECCdemoMFCDlg dialog

class CECCdemoMFCDlg : public CDialog
{
// Construction
public:
	CECCdemoMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CECCdemoMFCDlg)
	enum { IDD = IDD_ECCDEMOMFC_DIALOG };
	CString	m_log;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCdemoMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CECCdemoMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonClear();
	virtual void OnCancel();
	afx_msg void OnButtonSign();
	afx_msg void OnButtonVerify();
	afx_msg void OnButtonCreate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AppendLog(CString const & log);
	void AppendInfo(CString const & log);
	void AppendError(CString const & desc,CK_RV error);
private:
	CK_SESSION_HANDLE m_session;
	CK_OBJECT_HANDLE m_pubKey;
	CK_OBJECT_HANDLE m_prvKey;

	CK_BYTE m_signature[100];
	CK_ULONG m_signature_len;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCDEMOMFCDLG_H__53295BE9_72D6_4E71_BFA7_578D2ABBC15B__INCLUDED_)
