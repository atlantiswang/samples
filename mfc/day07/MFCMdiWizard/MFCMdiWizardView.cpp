// MFCMdiWizardView.cpp : implementation of the CMFCMdiWizardView class
//

#include "stdafx.h"
#include "MFCMdiWizard.h"

#include "MFCMdiWizardDoc.h"
#include "MFCMdiWizardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardView

IMPLEMENT_DYNCREATE(CMFCMdiWizardView, CView)

BEGIN_MESSAGE_MAP(CMFCMdiWizardView, CView)
	//{{AFX_MSG_MAP(CMFCMdiWizardView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardView construction/destruction

CMFCMdiWizardView::CMFCMdiWizardView()
{
	// TODO: add construction code here

}

CMFCMdiWizardView::~CMFCMdiWizardView()
{
}

BOOL CMFCMdiWizardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardView drawing

void CMFCMdiWizardView::OnDraw(CDC* pDC)
{
	CMFCMdiWizardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardView printing

BOOL CMFCMdiWizardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCMdiWizardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCMdiWizardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardView diagnostics

#ifdef _DEBUG
void CMFCMdiWizardView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCMdiWizardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCMdiWizardDoc* CMFCMdiWizardView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMdiWizardDoc)));
	return (CMFCMdiWizardDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCMdiWizardView message handlers
