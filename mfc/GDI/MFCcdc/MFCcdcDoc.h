// MFCcdcDoc.h : interface of the CMFCcdcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCCDCDOC_H__3C51DF96_17BF_43C1_932B_A9AB3351EE69__INCLUDED_)
#define AFX_MFCCDCDOC_H__3C51DF96_17BF_43C1_932B_A9AB3351EE69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCcdcDoc : public CDocument
{
protected: // create from serialization only
	CMFCcdcDoc();
	DECLARE_DYNCREATE(CMFCcdcDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCcdcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCcdcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCcdcDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCDCDOC_H__3C51DF96_17BF_43C1_932B_A9AB3351EE69__INCLUDED_)
