// MFCGdiDoc.cpp : implementation of the CMFCGdiDoc class
//

#include "stdafx.h"
#include "MFCGdi.h"

#include "MFCGdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiDoc

IMPLEMENT_DYNCREATE(CMFCGdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCGdiDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCGdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiDoc construction/destruction

CMFCGdiDoc::CMFCGdiDoc()
{
	// TODO: add one-time construction code here

}

CMFCGdiDoc::~CMFCGdiDoc()
{
}

BOOL CMFCGdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCGdiDoc serialization

void CMFCGdiDoc::Serialize(CArchive& ar)
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
// CMFCGdiDoc diagnostics

#ifdef _DEBUG
void CMFCGdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCGdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiDoc commands
