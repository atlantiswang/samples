#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
void OnCreate(HWND hWnd)
{
	HMENU hSys = GetSystemMenu(hWnd,FALSE);
	for(int i=0;i<6;i++)
		DeleteMenu(hSys,0,MF_BYPOSITION);
	AppendMenu(hSys,MF_SEPARATOR,0,"");
	AppendMenu(hSys,MF_STRING,1001,"我的菜单项");
}
void OnSysCommand(HWND hWnd,WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 1001:
		MessageBox(hWnd,"我的菜单项被点击","infor",MB_OK);
		break;
	}
}/*
void OnRButtonUp(HWND hWnd,LPARAM lParam)
{
	POINT pt={0};
	pt.x=LOWORD(lParam);
	pt.y=HIWORD(lParam);
	ClientToScreen(hWnd,(LPPOINT)&pt);
	HMENU hPopup = CreatePopupMenu();
	AppendMenu(hPopup,MF_STRING,1002,"新建");
	AppendMenu(hPopup,MF_SEPARATOR,0,"");
	AppendMenu(hPopup,MF_STRING,1003,"退出");
	BOOL nRet = TrackPopupMenu(hPopup,//阻塞函数
		TPM_CENTERALIGN|TPM_VCENTERALIGN|TPM_RETURNCMD,
		pt.x,pt.y,0,hWnd,NULL);//可坐标系不同
	switch(nRet)
	{
	case 1002:
		MessageBox(hWnd,"没有通过消息，处理了新建","infor",MB_OK);
		break;
	case 1003:
		MessageBox(hWnd,"没有通过消息，处理了\"退出\"","infor",MB_OK);
		break;
	}
}*/
void OnCommand(HWND hWnd,WPARAM wParam)
{
	char szText[256]={0};
	switch (LOWORD(wParam))
	{
	case 1002:
		sprintf(szText,"新建");
		break;
	case 1003:
		sprintf(szText,"退出");
		break;
	}
	
	MessageBox(hWnd,szText,"infor",MB_OK);
}
void OnContextMenu(HWND hWnd,LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();
	AppendMenu(hPopup,MF_STRING,1002,"新建");
	AppendMenu(hPopup,MF_SEPARATOR,0,"");
	AppendMenu(hPopup,MF_STRING,1003,"退出");
	TrackPopupMenu(hPopup,//阻塞函数
		TPM_CENTERALIGN|TPM_VCENTERALIGN,
		LOWORD(lParam),HIWORD(lParam),0,hWnd,NULL);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CONTEXTMENU://此消息用于影应右键被点击。由于WM_RBUTTONUP弹出菜单比较业余故使用此函数
		OnContextMenu(hWnd,lParam);
		//MessageBox(hWnd, "右键被点击", NULL, MB_OK);
		break;
	case WM_COMMAND:
		OnCommand(hWnd,wParam);
		break;
	case WM_RBUTTONUP:
		//OnRButtonUp(hWnd,lParam);
		break;
	case WM_SYSCOMMAND:
		OnSysCommand(hWnd,wParam);
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
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



