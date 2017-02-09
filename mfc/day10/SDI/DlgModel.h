#if !defined(AFX_DLGMODEL_H__B4E56B98_0080_469F_85AE_169CF71A440F__INCLUDED_)
#define AFX_DLGMODEL_H__B4E56B98_0080_469F_85AE_169CF71A440F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgModel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgModel dialog

class CDlgModel : public CDialog
{
// Construction
public:
	CDlgModel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgModel)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgModel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgModel)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODEL_H__B4E56B98_0080_469F_85AE_169CF71A440F__INCLUDED_)
