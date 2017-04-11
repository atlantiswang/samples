#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
HANDLE g_hOutput=0;
void OnLButtonDown(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char szText[256] = {0};
	sprintf(szText,"WM_LBUTTONDOWN:按键状态:%08X,x=%d,y=%d",
		wParam,LOWORD(lParam),HIWORD(lParam));
	WriteConsole(g_hOutput,szText,strlen(szText),NULL,NULL);
}
void OnLButtonUp(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	char szText[256] = {0};
	sprintf(szText,"WM_LBUTTONUP:按键状态:%08X,x=%d,y=%d",
		wParam,LOWORD(lParam),HIWORD(lParam));
	WriteConsole(g_hOutput,szText,strlen(szText),NULL,NULL);
}
void OnMouseWheel(HWND hWnd,WPARAM wParam)
{
	short nDelta = HIWORD(wParam);
	char szText[256]={0};
	sprintf(szText,"偏移量:%d\n",nDelta);
	WriteConsole(g_hOutput,szText,strlen(szText),
			NULL,NULL);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_MOUSEWHEEL:
		OnMouseWheel(hWnd,wParam);
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(hWnd,wParam,lParam);
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(hWnd,wParam,lParam);
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



