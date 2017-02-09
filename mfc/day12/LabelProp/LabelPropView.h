// LabelPropView.h : interface of the CLabelPropView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABELPROPVIEW_H__F508D4C8_EC56_4AE9_86CB_E43F1FF80D44__INCLUDED_)
#define AFX_LABELPROPVIEW_H__F508D4C8_EC56_4AE9_86CB_E43F1FF80D44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LabelPropDoc.h"
class CLabelPropView : public CView
{
protected: // create from serialization only
	CLabelPropView();
	DECLARE_DYNCREATE(CLabelPropView)

// Attributes
public:
	CLabelPropDoc* GetDocument();

// Operations
public:
	int m_nWidth;//Ïß¿í
	COLORREF m_Color;//ÑÕÉ«
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelPropView)
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
	virtual ~CLabelPropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLabelPropView)
	afx_msg void OnProperty();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LabelPropView.cpp
inline CLabelPropDoc* CLabelPropView::GetDocument()
   { return (CLabelPropDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELPROPVIEW_H__F508D4C8_EC56_4AE9_86CB_E43F1FF80D44__INCLUDED_)
