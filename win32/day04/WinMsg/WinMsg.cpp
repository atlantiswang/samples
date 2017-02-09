#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
HWND g_hEdit=0;
HANDLE g_hOutput=0;//标准输出句柄
#define WM_MYMESSAGE WM_USER+100
void OnCreate(HWND hWnd,LPARAM lParam)
{
	CREATESTRUCT *cs = (CREATESTRUCT*)lParam;
	char *pszText=(char *)cs->lpCreateParams;
	//MessageBox(hWnd,pszText,"infor",MB_OK);
	g_hEdit=CreateWindowEx(0,"EDIT","OK",WS_CHILD|WS_VISIBLE|
		WS_BORDER,0,0,200,200,
		hWnd,NULL,g_hInstance,NULL);
	PostMessage(hWnd,WM_MYMESSAGE,1,2);
}
void OnSize(HWND hWnd,LPARAM lParam)
{
	int nWidth = LOWORD(lParam);
	int nHight = HIWORD(lParam);
	char szText[256] = {0};
	sprintf(szText,"宽：%d,高：%d\n",nWidth,nHight);
	//MessageBox(hWnd,szText,"Infor",MB_OK);
	WriteConsole(g_hOutput,szText,strlen(szText),
		NULL,NULL);
	MoveWindow(g_hEdit,0,0,nWidth,nHight,true);
}
void OnMyMessage(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char szText[256]={0};
	sprintf(szText,"wParam=%d,lParam=%d",wParam,lParam);
	MessageBox(hWnd,szText,"Infor",MB_OK);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_MYMESSAGE:
		OnMyMessage(hWnd,wParam,lParam);
		break;
	case WM_SIZE:
		OnSize(hWnd,lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd,lParam);
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
							CW_USEDEFAULT,CW_USEDEFAULT,
							CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,
							g_hInstance,"hello create");
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
	MSG nMsg={0};/*
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}*/
	while(1)
	{
		if(PeekMessage(&nMsg,NULL,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&nMsg,NULL,0,0))
				return;
			else
			{
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
		}
		else{
			//WriteConsole(g_hOutput,"OnIdle",6,NULL,NULL);
		}
	}
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	AllocConsole();
	g_hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



