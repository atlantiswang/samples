#include "stdafx.h"
#include "resource.h"

UINT g_hIndicator[]={
	0,
	IDS_TIME,
	IDS_POS
};
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	CToolBar toolbar;
	CMFCToolBar m_wndToolBar1;
	CStatusBar statusbar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNew();
	afx_msg void OnSet();
	afx_msg void OnTool();
    afx_msg void OnInitMenuPopup( CMenu *, UINT, BOOL );
	afx_msg void OnTimer(UINT nId);
	afx_msg void OnMouseMove( UINT, CPoint );
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_COMMAND(ID_SET,OnSet)
	ON_COMMAND(ID_NEW,OnNew)
	ON_COMMAND(ID_TOOL,OnTool)
	ON_WM_INITMENUPOPUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()
void CMyFrameWnd::OnMouseMove( UINT nFlags, CPoint point)
{
	CString strPos;
	strPos.Format("x=%d,y=%d",point.x,point.y);
	statusbar.SetPaneText(2,strPos);
}
void CMyFrameWnd::OnTimer(UINT nId)
{
	SYSTEMTIME st = {0};
	::GetLocalTime(&st);
	CString  strTime;
	strTime.Format("%d %d %d %d:%d:%d",
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	statusbar.SetPaneText(1,strTime);
}
void CMyFrameWnd::OnInitMenuPopup(
		CMenu *pPopup,UINT pos,BOOL i)
{
	if(toolbar.IsWindowVisible())
	{
		pPopup->CheckMenuItem(ID_TOOL,MF_CHECKED);
	}
	else pPopup->CheckMenuItem(ID_TOOL,MF_UNCHECKED);
}
void CMyFrameWnd::OnTool()
{
	if(toolbar.IsWindowVisible())
	{
		this->ShowControlBar(&toolbar,FALSE,FALSE);
	}else{
		this->ShowControlBar(&toolbar,TRUE,FALSE);
	}
}
void CMyFrameWnd::OnSet()
{
	AfxMessageBox("绿色按钮被点击");
}
void CMyFrameWnd::OnNew()
{
	AfxMessageBox("新建被点击");
}
int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	toolbar.CreateEx(this,TBSTYLE_FLAT,//按钮的风格
		WS_CHILD|WS_VISIBLE|CBRS_ALIGN_TOP|CBRS_GRIPPER|
		CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|CBRS_FLYBY);
	toolbar.LoadToolBar(IDR_TOOLBAR1);
	toolbar.EnableDocking(CBRS_ALIGN_ANY);
	this->EnableDocking(CBRS_ALIGN_ANY);
	this->DockControlBar(&toolbar,
		AFX_IDW_DOCKBAR_TOP);
	toolbar.SetWindowText("工具栏");
	statusbar.CreateEx(this);
	statusbar.SetIndicators(g_hIndicator,3);
	statusbar.SetPaneInfo( 1, IDS_TIME, SBPS_NORMAL, 200 );
	statusbar.SetPaneInfo( 2, IDS_POS, SBPS_NORMAL, 200);
	::SetTimer(this->m_hWnd, 1,1000,NULL);
	return CFrameWnd::OnCreate(lpCreateStruct);
}
class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd *pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCToolBar",
		WS_OVERLAPPEDWINDOW,CFrameWnd::rectDefault,
		NULL,MAKEINTRESOURCE(IDR_MENU1));
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}




