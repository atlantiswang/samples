// MFCMdiWizardDoc.h : interface of the CMFCMdiWizardDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMDIWIZARDDOC_H__696E5FED_DB84_47CC_B3F5_C40CF4797CCA__INCLUDED_)
#define AFX_MFCMDIWIZARDDOC_H__696E5FED_DB84_47CC_B3F5_C40CF4797CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCMdiWizardDoc : public CDocument
{
protected: // create from serialization only
	CMFCMdiWizardDoc();
	DECLARE_DYNCREATE(CMFCMdiWizardDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMdiWizardDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCMdiWizardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMdiWizardDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDIWIZARDDOC_H__696E5FED_DB84_47CC_B3F5_C40CF4797CCA__INCLUDED_)
