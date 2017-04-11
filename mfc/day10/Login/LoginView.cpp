// LoginView.cpp : implementation of the CLoginView class
//

#include "stdafx.h"
#include "Login.h"

#include "LoginDoc.h"
#include "LoginView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginView

IMPLEMENT_DYNCREATE(CLoginView, CView)

BEGIN_MESSAGE_MAP(CLoginView, CView)
	//{{AFX_MSG_MAP(CLoginView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginView construction/destruction

CLoginView::CLoginView()
{
	// TODO: add construction code here

}

CLoginView::~CLoginView()
{
}

BOOL CLoginView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLoginView drawing

void CLoginView::OnDraw(CDC* pDC)
{
	CLoginDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLoginView printing

BOOL CLoginView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLoginView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLoginView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLoginView diagnostics

#ifdef _DEBUG
void CLoginView::AssertValid() const
{
	CView::AssertValid();
}

void CLoginView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLoginDoc* CLoginView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLoginDoc)));
	return (CLoginDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoginView message handlers
