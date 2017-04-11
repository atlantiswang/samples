// MFCcdcView.h : interface of the CMFCcdcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCCDCVIEW_H__100871EC_F201_4771_9872_0CD7ABC90702__INCLUDED_)
#define AFX_MFCCDCVIEW_H__100871EC_F201_4771_9872_0CD7ABC90702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCcdcView : public CView
{
protected: // create from serialization only
	CMFCcdcView();
	DECLARE_DYNCREATE(CMFCcdcView)

// Attributes
public:
	CMFCcdcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCcdcView)
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
	virtual ~CMFCcdcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCcdcView)
	afx_msg void OnClient();
	afx_msg void OnWindow();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCcdcView.cpp
inline CMFCcdcDoc* CMFCcdcView::GetDocument()
   { return (CMFCcdcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCDCVIEW_H__100871EC_F201_4771_9872_0CD7ABC90702__INCLUDED_)
