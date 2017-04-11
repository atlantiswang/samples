// LoginView.h : interface of the CLoginView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINVIEW_H__67C0DCCC_28D2_487B_9661_CA4B5C79C91A__INCLUDED_)
#define AFX_LOGINVIEW_H__67C0DCCC_28D2_487B_9661_CA4B5C79C91A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLoginView : public CView
{
protected: // create from serialization only
	CLoginView();
	DECLARE_DYNCREATE(CLoginView)

// Attributes
public:
	CLoginDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginView)
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
	virtual ~CLoginView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLoginView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LoginView.cpp
inline CLoginDoc* CLoginView::GetDocument()
   { return (CLoginDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINVIEW_H__67C0DCCC_28D2_487B_9661_CA4B5C79C91A__INCLUDED_)
