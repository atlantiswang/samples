#include "stdafx.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
HANDLE g_hOutput = 0;
int g_xPos=100;
int g_yPos=100;
int Left_Right=true;
int Right_Left=false;
int Up_Down=true;
int Down_Up=false;
void OnTimer(HWND hWnd,WPARAM wParam)
{
	char szText[256] = {0};
	sprintf(szText,"定时器:%d\n",wParam);
	WriteConsole(g_hOutput,szText,strlen(szText),NULL,NULL);
	RECT rc={0};
	GetClientRect(hWnd,&rc);
	if(g_xPos<=rc.left)
	{
		Left_Right=TRUE;
		Right_Left=FALSE;
	}else if(g_xPos+50>=rc.right)
	{
		Left_Right=FALSE;
		Right_Left=TRUE;
	}
	if(g_yPos<=rc.top)
	{
		Up_Down=TRUE;
		Down_Up=FALSE;
	}else if(g_yPos+50>=rc.bottom)
	{
		Up_Down=FALSE;
		Down_Up=TRUE;
	}
	if(Up_Down)
	{
		g_yPos++;
	}else if(Down_Up)
	{
		g_yPos--;
	}
	if(Left_Right)
	{
		g_xPos++;
	}else if(Right_Left)
	{
		g_xPos--;
	}
	InvalidateRect(hWnd,NULL,FALSE);
}
void CALLBACK TimerProc(HWND hWnd,UINT idEvent,
						UINT idTimer,DWORD dwCur)
{
	char szText[256] = {0};
	sprintf(szText,"定时器处理函数处理:%d\n",idTimer);
	WriteConsole(g_hOutput,szText,strlen(szText),
			NULL,NULL);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps={0};
	HDC hdc = BeginPaint(hWnd,&ps);
	Ellipse(hdc,g_xPos,g_yPos,g_xPos+50,g_yPos+50);
	EndPaint(hWnd,&ps);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		KillTimer(hWnd,1);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_TIMER:
		OnTimer(hWnd,wParam);
		break;
	case WM_CREATE:
		SetTimer(hWnd,1,10,NULL);
		//SetTimer(hWnd,2,2000,TimerProc);//建议使用窗口处理函数	
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
	g_hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	g_hInstance=hInstance;
	Register("Main",WndProc);
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;
}



