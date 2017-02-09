// MFCGdiView.cpp : implementation of the CMFCGdiView class
//

#include "stdafx.h"
#include "MFCGdi.h"

#include "MFCGdiDoc.h"
#include "MFCGdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiView

IMPLEMENT_DYNCREATE(CMFCGdiView, CView)

BEGIN_MESSAGE_MAP(CMFCGdiView, CView)
	//{{AFX_MSG_MAP(CMFCGdiView)
	ON_COMMAND(ID_BMP, OnBmp)
	ON_COMMAND(ID_BRUSH, OnBrush)
	ON_COMMAND(ID_FONT, OnFont)
	ON_COMMAND(ID_PEN, OnPen)
	ON_COMMAND(ID_RGN, OnRgn)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiView construction/destruction

CMFCGdiView::CMFCGdiView()
{
	// TODO: add construction code here

}

CMFCGdiView::~CMFCGdiView()
{
}

BOOL CMFCGdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiView drawing

void CMFCGdiView::OnDraw(CDC* pDC)
{
	CMFCGdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiView printing

BOOL CMFCGdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCGdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCGdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiView diagnostics

#ifdef _DEBUG
void CMFCGdiView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGdiDoc* CMFCGdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGdiDoc)));
	return (CMFCGdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCGdiView message handlers

void CMFCGdiView::OnBmp() 
{
	// TODO: Add your command handler code here
	//比较难
	CClientDC dc(this);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap *oldbmp = memdc.SelectObject(&bmp);
	dc.BitBlt(100,100,48,48,&memdc,0,0,SRCCOPY);
	memdc.SelectObject(oldbmp);
	bmp.DeleteObject();
	memdc.DeleteDC();
}

void CMFCGdiView::OnBrush() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
//	CBrush brush(RGB(0,255,0));
	CBrush brush(HS_CROSS,RGB(0,0,255));
/*	CBrush *oldbrush = dc.SelectObject(&brush);
	dc.Rectangle(100,100,300,300);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();*/
	HBRUSH oldbrush =(HBRUSH)::SelectObject(dc.m_hDC,brush.m_hObject);
	::Rectangle(dc.m_hDC,100,100,300,300);
	::SelectObject(dc.m_hDC,oldbrush);
	::DeleteObject(brush.m_hObject);
}

void CMFCGdiView::OnFont() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(300,"黑体");
	CFont *oldfont = dc.SelectObject(&font);
	dc.TextOut(100,100,"CMFCGdiView::OnFont");
	dc.SelectObject(oldfont);
	font.DeleteObject();
}

void CMFCGdiView::OnPen() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	CPen pen(PS_SOLID,10,RGB(255,0,0));
/*	CPen *oldpen = dc.SelectObject(&pen);
	dc.Rectangle(100,100,300,300);
	dc.SelectObject(oldpen);
	pen.DeleteObject();*/
	HPEN oldpen=(HPEN)::SelectObject(dc.m_hDC,pen.m_hObject);
	::Rectangle(dc.m_hDC,100,200,300,400);
	::SelectObject(dc.m_hDC,oldpen);
	::DeleteObject(pen.m_hObject);
}

void CMFCGdiView::OnRgn() 
{
	// TODO: Add your command handler code here
	CRgn rgn1;
	rgn1.CreateRectRgn(100,100,300,300);
	CRgn rgn2;
	rgn2.CreateEllipticRgn(200,200,400,400);

	rgn1.CombineRgn(&rgn1,&rgn2,RGN_XOR);

	CBrush brush(RGB(255,0,0));
	CClientDC dc(this);
	dc.FillRgn(&rgn1,&brush);
}
