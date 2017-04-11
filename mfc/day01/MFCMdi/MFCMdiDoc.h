// MFCMdiDoc.h : interface of the CMFCMdiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMDIDOC_H__5D8E2076_0229_40DD_8AD3_151DED193299__INCLUDED_)
#define AFX_MFCMDIDOC_H__5D8E2076_0229_40DD_8AD3_151DED193299__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCMdiDoc : public CDocument
{
protected: // create from serialization only
	CMFCMdiDoc();
	DECLARE_DYNCREATE(CMFCMdiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMdiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCMdiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMdiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIDOC_H__5D8E2076_0229_40DD_8AD3_151DED193299__INCLUDED_)
