// MFCMdiView.cpp : implementation of the CMFCMdiView class
//

#include "stdafx.h"
#include "MFCMdi.h"

#include "MFCMdiDoc.h"
#include "MFCMdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiView

IMPLEMENT_DYNCREATE(CMFCMdiView, CView)

BEGIN_MESSAGE_MAP(CMFCMdiView, CView)
	//{{AFX_MSG_MAP(CMFCMdiView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiView construction/destruction

CMFCMdiView::CMFCMdiView()
{
	// TODO: add construction code here

}

CMFCMdiView::~CMFCMdiView()
{
}

BOOL CMFCMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiView drawing

void CMFCMdiView::OnDraw(CDC* pDC)
{
	CMFCMdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiView printing

BOOL CMFCMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCMdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCMdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiView diagnostics

#ifdef _DEBUG
void CMFCMdiView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCMdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCMdiDoc* CMFCMdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMdiDoc)));
	return (CMFCMdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiView message handlers
