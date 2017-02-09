// MFCMdiWizardView.h : interface of the CMFCMdiWizardView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMDIWIZARDVIEW_H__DEA20736_57A7_4FD8_AC41_82F141508056__INCLUDED_)
#define AFX_MFCMDIWIZARDVIEW_H__DEA20736_57A7_4FD8_AC41_82F141508056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCMdiWizardView : public CView
{
protected: // create from serialization only
	CMFCMdiWizardView();
	DECLARE_DYNCREATE(CMFCMdiWizardView)

// Attributes
public:
	CMFCMdiWizardDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMdiWizardView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCMdiWizardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMdiWizardView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCMdiWizardView.cpp
inline CMFCMdiWizardDoc* CMFCMdiWizardView::GetDocument()
   { return (CMFCMdiWizardDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIWIZARDVIEW_H__DEA20736_57A7_4FD8_AC41_82F141508056__INCLUDED_)
