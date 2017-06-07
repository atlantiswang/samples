// MFCThread2Dlg.h : header file
//

#if !defined(AFX_MFCTHREAD2DLG_H__CD22FF8C_C172_4192_A891_80BF1E0E2234__INCLUDED_)
#define AFX_MFCTHREAD2DLG_H__CD22FF8C_C172_4192_A891_80BF1E0E2234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCThread2Dlg dialog

class CMFCThread2Dlg : public CDialog
{
// Construction
public:
	CMFCThread2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCThread2Dlg)
	enum { IDD = IDD_MFCTHREAD2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCThread2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCThread2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTalk();
	afx_msg void OnCall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTHREAD2DLG_H__CD22FF8C_C172_4192_A891_80BF1E0E2234__INCLUDED_)
