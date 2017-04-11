// MFCDrawView.cpp : implementation of the CMFCDrawView class
//

#include "stdafx.h"
#include "MFCDraw.h"

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	//{{AFX_MSG_MAP(CMFCDrawView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ELL, OnEll)
	ON_COMMAND(ID_LINE, OnLine)
	ON_COMMAND(ID_PEN, OnPen)
	ON_COMMAND(ID_REC, OnRec)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawView construction/destruction

CMFCDrawView::CMFCDrawView()
{
	// TODO: add construction code here

}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawView drawing

void CMFCDrawView::OnDraw(CDC* pDC)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawView printing

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawView diagnostics

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCDrawView message handlers
CPoint ptStart;
CPoint ptCur;
int g_kind = 0;
void CMFCDrawView::OnEll() 
{
	// TODO: Add your command handler code here
	g_kind = 4;
}

void CMFCDrawView::OnLine() 
{
	// TODO: Add your command handler code here
	g_kind = 2;
}

void CMFCDrawView::OnPen() 
{
	// TODO: Add your command handler code here
	g_kind = 1;
}

void CMFCDrawView::OnRec() 
{
	// TODO: Add your command handler code here
	g_kind = 3;
}

void CMFCDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCapture(this->m_hWnd);
	CView::OnLButtonDown(nFlags, point);
	ptStart=point;
	ptCur=point;
}

void CMFCDrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void CMFCDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	if(nFlags & MK_LBUTTON)
	{
		if(g_kind==1)//铅笔
		{
			dc.MoveTo(ptStart);
			dc.LineTo(point);
			ptStart=point;
		}else if(g_kind==2)//直线
		{
			dc.SetROP2(R2_NOT);
			dc.MoveTo(ptStart);
			dc.LineTo(ptCur);
			dc.MoveTo(ptStart);
			dc.LineTo(point);
			ptCur = point;
		}else if(g_kind==3)//矩形
		{//矩形本身里面还有一个画刷，取反色导致画刷颜色也变了
			dc.SetROP2(R2_NOT);
			//向操作系统借的刷子不用销毁
			HBRUSH hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
			HBRUSH oldbrush =(HBRUSH)::SelectObject(dc.m_hDC,hBrush);
			dc.Rectangle(ptStart.x,ptStart.y,
				ptCur.x,ptCur.y);
			dc.Rectangle(ptStart.x,ptStart.y,
				point.x,point.y);
			ptCur=point;
			::SelectObject(dc.m_hDC,oldbrush);
		}else if(g_kind==4)//圆形
		{
			dc.SetROP2(R2_NOT);
			//向操作系统借的刷子不用销毁
			HBRUSH hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
			HBRUSH oldbrush =(HBRUSH)::SelectObject(dc.m_hDC,hBrush);
			dc.Ellipse(ptStart.x,ptStart.y,
				ptCur.x,ptCur.y);
			dc.Ellipse(ptStart.x,ptStart.y,
				point.x,point.y);
			ptCur=point;
			::SelectObject(dc.m_hDC,oldbrush);
		}
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CMFCDrawView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(g_kind == 1)
	{
		HCURSOR hPen = ::LoadCursor(AfxGetInstanceHandle(),
			MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(hPen);
	}else if(g_kind>1)
	{
		HCURSOR hTen = ::LoadCursor(AfxGetInstanceHandle(),
			MAKEINTRESOURCE(IDC_CURSOR2));
		::SetCursor(hTen); 
	}
	return 0;//CView::OnSetCursor(pWnd, nHitTest, message);
}
