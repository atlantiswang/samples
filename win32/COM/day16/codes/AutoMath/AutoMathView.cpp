// AutoMathView.cpp : implementation of the CAutoMathView class
//

#include "stdafx.h"
#include "AutoMath.h"

#include "AutoMathDoc.h"
#include "AutoMathView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoMathView

IMPLEMENT_DYNCREATE(CAutoMathView, CView)

BEGIN_MESSAGE_MAP(CAutoMathView, CView)
	//{{AFX_MSG_MAP(CAutoMathView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoMathView construction/destruction

CAutoMathView::CAutoMathView()
{
	// TODO: add construction code here

}

CAutoMathView::~CAutoMathView()
{
}

BOOL CAutoMathView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoMathView drawing

void CAutoMathView::OnDraw(CDC* pDC)
{
	CAutoMathDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAutoMathView printing

BOOL CAutoMathView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAutoMathView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAutoMathView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAutoMathView diagnostics

#ifdef _DEBUG
void CAutoMathView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoMathView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoMathDoc* CAutoMathView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoMathDoc)));
	return (CAutoMathDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoMathView message handlers
