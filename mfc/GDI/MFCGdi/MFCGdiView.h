// MFCGdiView.h : interface of the CMFCGdiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCGDIVIEW_H__02C97A29_5726_4E4F_87F5_0A524563536E__INCLUDED_)
#define AFX_MFCGDIVIEW_H__02C97A29_5726_4E4F_87F5_0A524563536E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCGdiView : public CView
{
protected: // create from serialization only
	CMFCGdiView();
	DECLARE_DYNCREATE(CMFCGdiView)

// Attributes
public:
	CMFCGdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCGdiView)
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
	virtual ~CMFCGdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCGdiView)
	afx_msg void OnBmp();
	afx_msg void OnBrush();
	afx_msg void OnFont();
	afx_msg void OnPen();
	afx_msg void OnRgn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCGdiView.cpp
inline CMFCGdiDoc* CMFCGdiView::GetDocument()
   { return (CMFCGdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCGDIVIEW_H__02C97A29_5726_4E4F_87F5_0A524563536E__INCLUDED_)
