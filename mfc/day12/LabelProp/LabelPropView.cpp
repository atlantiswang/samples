// LabelPropView.cpp : implementation of the CLabelPropView class
//

#include "stdafx.h"
#include "LabelProp.h"

#include "LabelPropDoc.h"
#include "LabelPropView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabelPropView

IMPLEMENT_DYNCREATE(CLabelPropView, CView)

BEGIN_MESSAGE_MAP(CLabelPropView, CView)
	//{{AFX_MSG_MAP(CLabelPropView)
	ON_COMMAND(ID_PROPERTY, OnProperty)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabelPropView construction/destruction

CLabelPropView::CLabelPropView()
{
	// TODO: add construction code here
	m_Color=RGB(0,0,0);
	m_nWidth=1;
}

CLabelPropView::~CLabelPropView()
{
}

BOOL CLabelPropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLabelPropView drawing

void CLabelPropView::OnDraw(CDC* pDC)
{
	CLabelPropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPen pen(PS_SOLID,m_nWidth,m_Color);
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(100,100,200,200);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CLabelPropView printing

BOOL CLabelPropView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLabelPropView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLabelPropView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLabelPropView diagnostics

#ifdef _DEBUG
void CLabelPropView::AssertValid() const
{
	CView::AssertValid();
}

void CLabelPropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLabelPropDoc* CLabelPropView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabelPropDoc)));
	return (CLabelPropDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLabelPropView message handlers
#include "LabelSheet.h"
void CLabelPropView::OnProperty() 
{
	//创建和显示属性页对话框
	CLabelSheet sheet("标签式");
	//设置为向导模式
	sheet.SetWizardMode();
	sheet.DoModal();
}
