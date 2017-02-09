// MFCSdiWizardView.h : interface of the CMFCSdiWizardView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCSDIWIZARDVIEW_H__A3538706_A2C8_4DE8_ADF5_FF7AF20C00CE__INCLUDED_)
#define AFX_MFCSDIWIZARDVIEW_H__A3538706_A2C8_4DE8_ADF5_FF7AF20C00CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCSdiWizardView : public CView
{
protected: // create from serialization only
	CMFCSdiWizardView();
	DECLARE_DYNCREATE(CMFCSdiWizardView)

// Attributes
public:
	CMFCSdiWizardDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSdiWizardView)
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
	virtual ~CMFCSdiWizardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCSdiWizardView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCSdiWizardView.cpp
inline CMFCSdiWizardDoc* CMFCSdiWizardView::GetDocument()
   { return (CMFCSdiWizardDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDIWIZARDVIEW_H__A3538706_A2C8_4DE8_ADF5_FF7AF20C00CE__INCLUDED_)
