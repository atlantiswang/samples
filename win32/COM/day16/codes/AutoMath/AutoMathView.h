// AutoMathView.h : interface of the CAutoMathView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOMATHVIEW_H__3B5473F2_A0A3_4E35_B3B9_4104A961E5E1__INCLUDED_)
#define AFX_AUTOMATHVIEW_H__3B5473F2_A0A3_4E35_B3B9_4104A961E5E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoMathView : public CView
{
protected: // create from serialization only
	CAutoMathView();
	DECLARE_DYNCREATE(CAutoMathView)

// Attributes
public:
	CAutoMathDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoMathView)
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
	virtual ~CAutoMathView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoMathView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoMathView.cpp
inline CAutoMathDoc* CAutoMathView::GetDocument()
   { return (CAutoMathDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOMATHVIEW_H__3B5473F2_A0A3_4E35_B3B9_4104A961E5E1__INCLUDED_)
