// AutoMathDoc.h : interface of the CAutoMathDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOMATHDOC_H__FAC1D265_4CFC_4BF9_9A42_753FE0728A3E__INCLUDED_)
#define AFX_AUTOMATHDOC_H__FAC1D265_4CFC_4BF9_9A42_753FE0728A3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoMathDoc : public CDocument
{
protected: // create from serialization only
	CAutoMathDoc();
	DECLARE_DYNCREATE(CAutoMathDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoMathDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoMathDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoMathDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAutoMathDoc)
	afx_msg void Show();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOMATHDOC_H__FAC1D265_4CFC_4BF9_9A42_753FE0728A3E__INCLUDED_)
