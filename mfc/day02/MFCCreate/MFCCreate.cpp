#include "stdafx.h"
class CMyFrameWnd : public CFrameWnd
{
public:
	virtual LRESULT WindowProc(
		UINT message,WPARAM wParam,LPARAM lParam);
};
LRESULT CMyFrameWnd:: WindowProc(
		UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {0};
			HDC hdc=::BeginPaint(this->m_hWnd,&ps);
			::TextOut(hdc,0,0,"hello",5);
			::EndPaint(m_hWnd,&ps);
		}
		break;
	case WM_CREATE:
		AfxMessageBox("WM_CERATE");
		break;
	}
	return CFrameWnd::WindowProc(message,wParam,lParam);
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
	pFrame ->Create(NULL,"MFCCreate");
	m_pMainWnd = pFrame;
	pFrame ->ShowWindow(SW_SHOW);
	pFrame ->UpdateWindow();
	return TRUE;
}

