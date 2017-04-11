// MFCDrawView.h : interface of the CMFCDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDRAWVIEW_H__90EE0F3F_8D4B_4E1F_83A7_61DF299C06B4__INCLUDED_)
#define AFX_MFCDRAWVIEW_H__90EE0F3F_8D4B_4E1F_83A7_61DF299C06B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCDrawView : public CView
{
protected: // create from serialization only
	CMFCDrawView();
	DECLARE_DYNCREATE(CMFCDrawView)

// Attributes
public:
	CMFCDrawDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDrawView)
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
	virtual ~CMFCDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCDrawView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEll();
	afx_msg void OnLine();
	afx_msg void OnPen();
	afx_msg void OnRec();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCDrawView.cpp
inline CMFCDrawDoc* CMFCDrawView::GetDocument()
   { return (CMFCDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDRAWVIEW_H__90EE0F3F_8D4B_4E1F_83A7_61DF299C06B4__INCLUDED_)
