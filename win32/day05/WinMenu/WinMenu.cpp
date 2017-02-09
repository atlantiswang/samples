#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
HANDLE g_hOutput = 0;
HMENU hFile = 0;
void OnCreate(HWND hWnd)
{
	HMENU hMain = CreateMenu();//顶层菜单
	hFile = CreatePopupMenu();//弹出式菜单
	AppendMenu(hFile,MF_STRING|MF_CHECKED,1003,"新建(&C)");
	AppendMenu(hFile,MF_SEPARATOR,0,"");
	AppendMenu(hFile,MF_STRING,1004,"退出(&X)");

	HMENU hHelp = CreatePopupMenu();
	AppendMenu(hHelp,MF_STRING|MF_GRAYED,1005,"关于");


	AppendMenu(hMain,MF_POPUP,(UINT)hFile,"文件(&F)");
	AppendMenu(hMain,MF_POPUP,(UINT)hHelp,"帮助");
	//只有POPUP风格的菜单才可以弹出菜单
	SetMenu(hWnd,hMain);
}
int g_state = 0;//标志量（标识新建菜单项当前状态）
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1003:
		if(g_state == 0)
		{
			CheckMenuItem(hFile,1003,MF_BYCOMMAND|MF_UNCHECKED);
		}
		else{
			CheckMenuItem(hFile,0,MF_BYPOSITION|MF_CHECKED);
		}
		g_state=!g_state;
		break;
	case 1004:
		MessageBox(hWnd,"退出被点击","infor",MB_OK);
		PostQuitMessage(0);
		break;
	case 1005:
		MessageBox(hWnd,"关于被点击","infor",MB_OK);
		break;
	}
}
void OnInitMenuPopup(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char szText[256] = {0};
	sprintf(szText,
		"即将显示的菜单的句柄:%d,被点击菜单项位置:%d,"
		"是否为窗口菜单:%d\n",wParam,LOWORD(lParam),HIWORD(lParam));
	WriteConsole(g_hOutput,szText,strlen(szText),NULL,NULL);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITMENUPOPUP:
		OnInitMenuPopup(hWnd,wParam,lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
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
	wce.hCursor=NULL;
	wce.hIcon=NULL;
	wce.hIconSm=NULL;
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=WndProc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName=NULL;
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
							100,100,500,500,NULL,NULL,
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
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



