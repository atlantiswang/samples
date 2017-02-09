// LabelPropDoc.cpp : implementation of the CLabelPropDoc class
//

#include "stdafx.h"
#include "LabelProp.h"

#include "LabelPropDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabelPropDoc

IMPLEMENT_DYNCREATE(CLabelPropDoc, CDocument)

BEGIN_MESSAGE_MAP(CLabelPropDoc, CDocument)
	//{{AFX_MSG_MAP(CLabelPropDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabelPropDoc construction/destruction

CLabelPropDoc::CLabelPropDoc()
{
	// TODO: add one-time construction code here

}

CLabelPropDoc::~CLabelPropDoc()
{
}

BOOL CLabelPropDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLabelPropDoc serialization

void CLabelPropDoc::Serialize(CArchive& ar)
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
// CLabelPropDoc diagnostics

#ifdef _DEBUG
void CLabelPropDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLabelPropDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLabelPropDoc commands
