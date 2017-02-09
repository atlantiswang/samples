// MFCSdiWizardView.cpp : implementation of the CMFCSdiWizardView class
//

#include "stdafx.h"
#include "MFCSdiWizard.h"

#include "MFCSdiWizardDoc.h"
#include "MFCSdiWizardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardView

IMPLEMENT_DYNCREATE(CMFCSdiWizardView, CView)

BEGIN_MESSAGE_MAP(CMFCSdiWizardView, CView)
	//{{AFX_MSG_MAP(CMFCSdiWizardView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardView construction/destruction

CMFCSdiWizardView::CMFCSdiWizardView()
{
	// TODO: add construction code here

}

CMFCSdiWizardView::~CMFCSdiWizardView()
{
}

BOOL CMFCSdiWizardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardView drawing

void CMFCSdiWizardView::OnDraw(CDC* pDC)
{
	CMFCSdiWizardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardView printing

BOOL CMFCSdiWizardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCSdiWizardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCSdiWizardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardView diagnostics

#ifdef _DEBUG
void CMFCSdiWizardView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCSdiWizardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCSdiWizardDoc* CMFCSdiWizardView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSdiWizardDoc)));
	return (CMFCSdiWizardDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCSdiWizardView message handlers

void CMFCSdiWizardView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDown(nFlags, point);
}

void CMFCSdiWizardView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}

void CMFCSdiWizardView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMouseMove(nFlags, point);
}

BOOL CMFCSdiWizardView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	HCURSOR hBall = (HCURSOR)::LoadCursor(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hBall);
	return 0;//CView::OnSetCursor(pWnd, nHitTest, message);
}
