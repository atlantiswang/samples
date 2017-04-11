// MFCSdiWizardDoc.h : interface of the CMFCSdiWizardDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCSDIWIZARDDOC_H__723AF994_1D60_46DA_A112_45B6D45AA177__INCLUDED_)
#define AFX_MFCSDIWIZARDDOC_H__723AF994_1D60_46DA_A112_45B6D45AA177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCSdiWizardDoc : public CDocument
{
protected: // create from serialization only
	CMFCSdiWizardDoc();
	DECLARE_DYNCREATE(CMFCSdiWizardDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSdiWizardDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCSdiWizardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCSdiWizardDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDIWIZARDDOC_H__723AF994_1D60_46DA_A112_45B6D45AA177__INCLUDED_)
