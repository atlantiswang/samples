// MFCSdiView.h : interface of the CMFCSdiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCSDIVIEW_H__BAF251A5_AD6D_454F_AFB8_8E77D444E2A0__INCLUDED_)
#define AFX_MFCSDIVIEW_H__BAF251A5_AD6D_454F_AFB8_8E77D444E2A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCSdiView : public CView
{
protected: // create from serialization only
	CMFCSdiView();
	DECLARE_DYNCREATE(CMFCSdiView)

// Attributes
public:
	CMFCSdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSdiView)
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
	virtual ~CMFCSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCSdiView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCSdiView.cpp
inline CMFCSdiDoc* CMFCSdiView::GetDocument()
   { return (CMFCSdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDIVIEW_H__BAF251A5_AD6D_454F_AFB8_8E77D444E2A0__INCLUDED_)
