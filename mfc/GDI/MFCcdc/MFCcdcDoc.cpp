// MFCcdcDoc.cpp : implementation of the CMFCcdcDoc class
//

#include "stdafx.h"
#include "MFCcdc.h"

#include "MFCcdcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcDoc

IMPLEMENT_DYNCREATE(CMFCcdcDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCcdcDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCcdcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcDoc construction/destruction

CMFCcdcDoc::CMFCcdcDoc()
{
	// TODO: add one-time construction code here

}

CMFCcdcDoc::~CMFCcdcDoc()
{
}

BOOL CMFCcdcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCcdcDoc serialization

void CMFCcdcDoc::Serialize(CArchive& ar)
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
// CMFCcdcDoc diagnostics

#ifdef _DEBUG
void CMFCcdcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCcdcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcDoc commands
