#if !defined(AFX_DLOG1_H__8B3E0FCE_E08D_4BCE_9039_8922865FAA90__INCLUDED_)
#define AFX_DLOG1_H__8B3E0FCE_E08D_4BCE_9039_8922865FAA90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlog1 dialog

class CDlog1 : public CDialog
{
// Construction
public:
	CDlog1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlog1)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlog1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlog1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLOG1_H__8B3E0FCE_E08D_4BCE_9039_8922865FAA90__INCLUDED_)
