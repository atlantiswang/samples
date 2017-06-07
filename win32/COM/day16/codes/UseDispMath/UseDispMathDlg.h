// UseDispMathDlg.h : header file
//

#if !defined(AFX_USEDISPMATHDLG_H__E873922E_8A39_4793_B577_B39A975956DA__INCLUDED_)
#define AFX_USEDISPMATHDLG_H__E873922E_8A39_4793_B577_B39A975956DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUseDispMathDlg dialog

class CUseDispMathDlg : public CDialog
{
// Construction
public:
	CUseDispMathDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUseDispMathDlg)
	enum { IDD = IDD_USEDISPMATH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseDispMathDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUseDispMathDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEDISPMATHDLG_H__E873922E_8A39_4793_B577_B39A975956DA__INCLUDED_)
