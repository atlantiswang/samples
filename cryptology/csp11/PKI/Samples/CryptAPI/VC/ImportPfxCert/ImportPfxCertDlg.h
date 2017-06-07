// ImportPfxCertDlg.h : header file
//

#if !defined(AFX_IMPORTPFXCERTDLG_H__46328045_B082_4EAD_9AEF_1D88142C6368__INCLUDED_)
#define AFX_IMPORTPFXCERTDLG_H__46328045_B082_4EAD_9AEF_1D88142C6368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImportPfxCertDlg dialog

class CImportPfxCertDlg : public CDialog
{
	// Construction
public:
	CImportPfxCertDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CImportPfxCertDlg)
	enum { IDD = IDD_IMPORTPFXCERT_DIALOG };
	CString	m_strPfxName;
	CString	m_strPassword;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportPfxCertDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CImportPfxCertDlg)
	afx_msg void OnBtnSelectPfx();
	afx_msg void OnImportPfx();
	afx_msg void OnReset();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTPFXCERTDLG_H__46328045_B082_4EAD_9AEF_1D88142C6368__INCLUDED_)
