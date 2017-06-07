// AutoMathDoc.cpp : implementation of the CAutoMathDoc class
//

#include "stdafx.h"
#include "AutoMath.h"

#include "AutoMathDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoMathDoc

IMPLEMENT_DYNCREATE(CAutoMathDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoMathDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoMathDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoMathDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CAutoMathDoc)
	DISP_FUNCTION(CAutoMathDoc, "Show", Show, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoMath to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {2CC4D650-1632-45CF-ABC6-BEB94F58DAC1}
static const IID IID_IAutoMath =
{ 0x2cc4d650, 0x1632, 0x45cf, { 0xab, 0xc6, 0xbe, 0xb9, 0x4f, 0x58, 0xda, 0xc1 } };

BEGIN_INTERFACE_MAP(CAutoMathDoc, CDocument)
	INTERFACE_PART(CAutoMathDoc, IID_IAutoMath, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoMathDoc construction/destruction

CAutoMathDoc::CAutoMathDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CAutoMathDoc::~CAutoMathDoc()
{
	AfxOleUnlockApp();
}

BOOL CAutoMathDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAutoMathDoc serialization

void CAutoMathDoc::Serialize(CArchive& ar)
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
// CAutoMathDoc diagnostics

#ifdef _DEBUG
void CAutoMathDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoMathDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoMathDoc commands

void CAutoMathDoc::Show() 
{
	// TODO: Add your dispatch handler code here
    AfxGetMainWnd()->ShowWindow(SW_SHOW);
}
