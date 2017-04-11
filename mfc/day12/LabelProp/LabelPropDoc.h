// LabelPropDoc.h : interface of the CLabelPropDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABELPROPDOC_H__4B08D127_49C4_4F54_8CCF_28B599A1B557__INCLUDED_)
#define AFX_LABELPROPDOC_H__4B08D127_49C4_4F54_8CCF_28B599A1B557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLabelPropDoc : public CDocument
{
protected: // create from serialization only
	CLabelPropDoc();
	DECLARE_DYNCREATE(CLabelPropDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelPropDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLabelPropDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLabelPropDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELPROPDOC_H__4B08D127_49C4_4F54_8CCF_28B599A1B557__INCLUDED_)
