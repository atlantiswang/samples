// MFCSdiWizardDoc.cpp : implementation of the CMFCSdiWizardDoc class
//

#include "stdafx.h"
#include "MFCSdiWizard.h"

#include "MFCSdiWizardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardDoc

IMPLEMENT_DYNCREATE(CMFCSdiWizardDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCSdiWizardDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCSdiWizardDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardDoc construction/destruction

CMFCSdiWizardDoc::CMFCSdiWizardDoc()
{
	// TODO: add one-time construction code here

}

CMFCSdiWizardDoc::~CMFCSdiWizardDoc()
{
}

BOOL CMFCSdiWizardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardDoc serialization

void CMFCSdiWizardDoc::Serialize(CArchive& ar)
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
// CMFCSdiWizardDoc diagnostics

#ifdef _DEBUG
void CMFCSdiWizardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCSdiWizardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardDoc commands
