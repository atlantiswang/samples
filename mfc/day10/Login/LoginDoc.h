// LoginDoc.h : interface of the CLoginDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINDOC_H__6C450BCA_ADEA_4A52_AC37_F88B1FA66625__INCLUDED_)
#define AFX_LOGINDOC_H__6C450BCA_ADEA_4A52_AC37_F88B1FA66625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLoginDoc : public CDocument
{
protected: // create from serialization only
	CLoginDoc();
	DECLARE_DYNCREATE(CLoginDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLoginDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLoginDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDOC_H__6C450BCA_ADEA_4A52_AC37_F88B1FA66625__INCLUDED_)
