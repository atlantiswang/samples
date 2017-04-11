#include "stdafx.h"
#include "resource.h"
class CMyView : public CView
{
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDraw(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnNew();
};
BEGIN_MESSAGE_MAP(CMyView,CView)
//	ON_WM_PAINT() 建议让OnDraw处理
	ON_COMMAND(ID_NEW,OnNew)
END_MESSAGE_MAP()
void CMyView::OnNew()
{
	AfxMessageBox("视图类处理了新建被点击");
}
void CMyView::OnPaint()
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(this->m_hWnd,&ps);
	::TextOut(hdc,200,200,"CMyView::OnPaint",
		strlen("CMyView::OnPaint"));
	::EndPaint(this->m_hWnd,&ps);
}
void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100,100,"CMYVIEW::ONDRAW");
}
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()
int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CMyView *pView = new CMyView;
	pView ->Create(NULL,"",WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(0,0,100,100),this,AFX_IDW_PANE_FIRST);
	this->m_pViewActive = pView;
	return CFrameWnd::OnCreate(lpCreateStruct);
}
void CMyFrameWnd::OnPaint()
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(this->m_hWnd,&ps);
	::TextOut(hdc, 100,100,"我是框架窗口客户区",18);
	::EndPaint(this->m_hWnd,&ps);
}
class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd * pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCView",WS_OVERLAPPEDWINDOW,
		CFrameWnd::rectDefault,NULL,
		MAKEINTRESOURCE(IDR_MENU1));
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}