// MFCMdiDoc.cpp : implementation of the CMFCMdiDoc class
//

#include "stdafx.h"
#include "MFCMdi.h"

#include "MFCMdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiDoc

IMPLEMENT_DYNCREATE(CMFCMdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCMdiDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCMdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiDoc construction/destruction

CMFCMdiDoc::CMFCMdiDoc()
{
	// TODO: add one-time construction code here

}

CMFCMdiDoc::~CMFCMdiDoc()
{
}

BOOL CMFCMdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCMdiDoc serialization

void CMFCMdiDoc::Serialize(CArchive& ar)
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
// CMFCMdiDoc diagnostics

#ifdef _DEBUG
void CMFCMdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCMdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiDoc commands
