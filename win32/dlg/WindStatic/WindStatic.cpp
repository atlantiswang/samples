#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
void OnCreate(HWND hWnd)
{
	//静态框
	CreateWindowEx(0,"STATIC","hello txt",
					WS_CHILD|WS_VISIBLE|SS_NOTIFY,
					100,100,200,30,hWnd,(HMENU)1001,
					g_hInstance,NULL);
	//图标静态框
	CreateWindowEx(0,"STATIC","#101",
					WS_CHILD|WS_VISIBLE|SS_ICON|SS_NOTIFY,
					350,100,0,0,hWnd,(HMENU)1002,
					g_hInstance,NULL);
}
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1001:
		if(HIWORD(wParam) == STN_CLICKED)
		{
			MessageBox(hWnd,"点了文字","infor",MB_OK);
		}
	case 1002:
		if(HIWORD(wParam) == STN_DBLCLK)
		{
			MessageBox(hWnd,"双击了图标","infor",MB_OK);
		}
		break;
	case ID_BLACK:
		{
			HICON hBlack = LoadIcon(g_hInstance,
				MAKEINTRESOURCE(IDI_ICON1));
			//通过控件ID获取控件句柄函数
			HWND hStatic = GetDlgItem(hWnd,1002);
			SendMessage(hStatic,STM_SETICON,
				(WPARAM)hBlack,0);
			//发送窗口消息
		}
		break;
	case ID_BLUE:
		{
			HICON hBlue = LoadIcon(g_hInstance,
				MAKEINTRESOURCE(IDI_ICON2));
			HWND hStatic = GetDlgItem(hWnd,1002);
			SendMessage(hStatic,STM_SETICON,
				(WPARAM)hBlue,0);
		}
		break;
	}
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
		break;//此消息常用的就是创建子窗口
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
	wce.hCursor=NULL;
	wce.hIcon=NULL;
	wce.hIconSm=NULL;
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=WndProc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);//注意这里
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,CW_USEDEFAULT,
							CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,
							g_hInstance,NULL);
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



