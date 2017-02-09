#if !defined(AFX_ECKEYVALUEDLG_H__0809BFFD_E404_410F_9EDF_BDA521A7291C__INCLUDED_)
#define AFX_ECKEYVALUEDLG_H__0809BFFD_E404_410F_9EDF_BDA521A7291C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ECKeyValueDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CECKeyValueDlg dialog

class CECKeyValueDlg : public CDialog
{
// Construction
public:
	CECKeyValueDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CECKeyValueDlg)
	enum { IDD = IDD_ECC_KEY };
	CString	m_strPublic;
	CString	m_strPrivate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECKeyValueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CECKeyValueDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BYTE m_pub[67];
	BYTE m_prv[32];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECKEYVALUEDLG_H__0809BFFD_E404_410F_9EDF_BDA521A7291C__INCLUDED_)
