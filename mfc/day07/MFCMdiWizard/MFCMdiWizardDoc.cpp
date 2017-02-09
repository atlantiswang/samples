// MFCMdiWizardDoc.cpp : implementation of the CMFCMdiWizardDoc class
//

#include "stdafx.h"
#include "MFCMdiWizard.h"

#include "MFCMdiWizardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardDoc

IMPLEMENT_DYNCREATE(CMFCMdiWizardDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCMdiWizardDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCMdiWizardDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardDoc construction/destruction

CMFCMdiWizardDoc::CMFCMdiWizardDoc()
{
	// TODO: add one-time construction code here

}

CMFCMdiWizardDoc::~CMFCMdiWizardDoc()
{
}

BOOL CMFCMdiWizardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardDoc serialization

void CMFCMdiWizardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardDoc diagnostics

#ifdef _DEBUG
void CMFCMdiWizardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCMdiWizardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardDoc commands
