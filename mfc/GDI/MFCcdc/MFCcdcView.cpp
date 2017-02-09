// MFCcdcView.cpp : implementation of the CMFCcdcView class
//

#include "stdafx.h"
#include "MFCcdc.h"

#include "MFCcdcDoc.h"
#include "MFCcdcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcView

IMPLEMENT_DYNCREATE(CMFCcdcView, CView)

BEGIN_MESSAGE_MAP(CMFCcdcView, CView)
	//{{AFX_MSG_MAP(CMFCcdcView)
	ON_COMMAND(ID_CLIENT, OnClient)
	ON_COMMAND(ID_WINDOW, OnWindow)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcView construction/destruction

CMFCcdcView::CMFCcdcView()
{
	// TODO: add construction code here

}

CMFCcdcView::~CMFCcdcView()
{
}

BOOL CMFCcdcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcView drawing

void CMFCcdcView::OnDraw(CDC* pDC)
{
	CMFCcdcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcView printing

BOOL CMFCcdcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCcdcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCcdcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcView diagnostics

#ifdef _DEBUG
void CMFCcdcView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCcdcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCcdcDoc* CMFCcdcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCcdcDoc)));
	return (CMFCcdcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCcdcView message handlers

void CMFCcdcView::OnClient() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
//	dc.TextOut(0,0,"CMFCcdcView::OnClient");
	::TextOut(dc.m_hDC,0,0,"CMFCcdcView::OnClient",21);
}

void CMFCcdcView::OnWindow() 
{
	// TODO: Add your command handler code here
	CWindowDC dc(AfxGetApp()->m_pMainWnd);
//	dc.TextOut(0,0,"CMFCcdcView::OnWindow");
	::TextOut(dc.m_hDC,0,0,"CMFCcdcView::OnWindow",41);
}

void CMFCcdcView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.TextOut(0,0,"CMFCcdcView::OnPaint");
	// Do not call CView::OnPaint() for painting messages
}
