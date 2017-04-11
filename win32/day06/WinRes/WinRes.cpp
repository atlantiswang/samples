#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
	HCURSOR hRec=LoadCursorFromFile("c:/windows/Cursors/aero_working.ani");
	HCURSOR hBall=LoadCursorFromFile("C:/Windows/Cursors/aero_working_l.ani");
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case ID_NEW:
		MessageBox(hWnd,"新建被点击","infor",MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd,"退出被点击","infor",MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd,"关于被点击","infor",MB_OK);
		break;
	}
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hWnd,&ps);
	HICON hIcon = LoadIcon(g_hInstance,
			MAKEINTRESOURCE(IDI_ICON1));
	DrawIcon(hdc,100,100,hIcon);
	EndPaint(hWnd,&ps);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_SETCURSOR:
		if(LOWORD(lParam)==HTCLIENT){
//		HCURSOR hRec=LoadCursorFromFile("c:/windows/Cursors/aero_working.ani");
//		HCURSOR hBall=LoadCursorFromFile("C:/Windows/Cursors/aero_working_l.ani");
//		HCURSOR hRec=LoadCursor(g_hInstance,
//				MAKEINTRESOURCE(IDC_CURSOR1));
//		HCURSOR hBall = LoadCursor(g_hInstance,
//				MAKEINTRESOURCE(IDC_CURSOR2));
		POINT pt={0};
		GetCursorPos(&pt);//屏幕坐标系下鼠标光标的位置
		ScreenToClient(hWnd,&pt);
		RECT rc={0};
		GetClientRect (hWnd,&rc);//客户区窗口边界信息
		if(pt.x<=rc.right/2)
			SetCursor(hRec);
		else
			SetCursor(hBall);
		return 0;//当自定义处理与默认处理有冲突是要返回
		}//为什么要加大括号，不让下面的case语句得到hBall?
		else
		{
			//在非客户区默认处理defwindowproc
		}
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
BOOL Register(LPSTR lpClassName,WNDPROC WndProc)
{
	WNDCLASSEX wce={0};
	wce.cbSize=sizeof(wce);
	wce.cbClsExtra=0;
	wce.cbWndExtra=0;
	wce.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wce.hCursor=LoadCursor(g_hInstance,MAKEINTRESOURCE(IDC_CURSOR2));
	wce.hIcon=LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_ICON2));
	wce.hIconSm=NULL;//LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_ICON1));
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=WndProc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName=NULL;//MAKEINTRESOURCE(IDR_MENU1);//类型不匹配，需要函数转
	//MAKEINTRESOURCE -这个宏转换，任何资源都可以转。
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);//注意这里
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)//只是建某个窗口
{
	HMENU hMenu=LoadMenu(g_hInstance,MAKEINTRESOURCE(IDR_MENU1));
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,CW_USEDEFAULT,
							CW_USEDEFAULT,CW_USEDEFAULT,NULL,
							hMenu,//（菜单）这里又要句柄类型
							g_hInstance,NULL);
// 	HICON hIcon=LoadIcon(g_hInstance,
// 		MAKEINTRESOURCE(IDI_ICON1));
// 	SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	return hWnd;
}
//显示窗口
void Display(HWND hWnd)
{
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
}
//消息循环
void Message()
{
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



