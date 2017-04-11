// MFCSdiDoc.cpp : implementation of the CMFCSdiDoc class
//

#include "stdafx.h"
#include "MFCSdi.h"

#include "MFCSdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiDoc

IMPLEMENT_DYNCREATE(CMFCSdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCSdiDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCSdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiDoc construction/destruction

CMFCSdiDoc::CMFCSdiDoc()
{
	// TODO: add one-time construction code here

}

CMFCSdiDoc::~CMFCSdiDoc()
{
}

BOOL CMFCSdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCSdiDoc serialization

void CMFCSdiDoc::Serialize(CArchive& ar)
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
// CMFCSdiDoc diagnostics

#ifdef _DEBUG
void CMFCSdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCSdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiDoc commands
