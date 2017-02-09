// MFCMdiView.h : interface of the CMFCMdiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMDIVIEW_H__535E4524_5736_4AE3_B59B_4F24A96F8602__INCLUDED_)
#define AFX_MFCMDIVIEW_H__535E4524_5736_4AE3_B59B_4F24A96F8602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCMdiView : public CView
{
protected: // create from serialization only
	CMFCMdiView();
	DECLARE_DYNCREATE(CMFCMdiView)

// Attributes
public:
	CMFCMdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMdiView)
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
	virtual ~CMFCMdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMdiView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCMdiView.cpp
inline CMFCMdiDoc* CMFCMdiView::GetDocument()
   { return (CMFCMdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIVIEW_H__535E4524_5736_4AE3_B59B_4F24A96F8602__INCLUDED_)
