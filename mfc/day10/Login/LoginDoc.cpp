// LoginDoc.cpp : implementation of the CLoginDoc class
//

#include "stdafx.h"
#include "Login.h"

#include "LoginDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDoc

IMPLEMENT_DYNCREATE(CLoginDoc, CDocument)

BEGIN_MESSAGE_MAP(CLoginDoc, CDocument)
	//{{AFX_MSG_MAP(CLoginDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDoc construction/destruction

CLoginDoc::CLoginDoc()
{
	// TODO: add one-time construction code here

}

CLoginDoc::~CLoginDoc()
{
}

BOOL CLoginDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLoginDoc serialization

void CLoginDoc::Serialize(CArchive& ar)
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
// CLoginDoc diagnostics

#ifdef _DEBUG
void CLoginDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLoginDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoginDoc commands
