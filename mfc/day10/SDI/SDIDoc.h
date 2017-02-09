// SDIDoc.h : interface of the CSDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIDOC_H__C0ACA9EA_6D04_4614_ACCB_2E32321641F5__INCLUDED_)
#define AFX_SDIDOC_H__C0ACA9EA_6D04_4614_ACCB_2E32321641F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIDoc : public CDocument
{
protected: // create from serialization only
	CSDIDoc();
	DECLARE_DYNCREATE(CSDIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIDOC_H__C0ACA9EA_6D04_4614_ACCB_2E32321641F5__INCLUDED_)
