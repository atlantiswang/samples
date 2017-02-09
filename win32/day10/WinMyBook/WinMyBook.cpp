#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
HINSTANCE g_hInstance=0;
void OnSave(HWND hWnd)
{
	HWND hEdit = GetDlgItem(hWnd,1001);
	LRESULT nLen=SendMessage(hEdit,WM_GETTEXTLENGTH,0,0);
	FILE* fp;
	char* pszText=(char*)malloc(nLen+1);
	memset(pszText,0,nLen+1);
	SendMessage(hEdit,WM_GETTEXT,nLen+1,(LPARAM)pszText);
	fp=fopen("F:/my.txt","w");
	fwrite(pszText,1,nLen,fp);
	fclose(fp);
	free(pszText);
	SetWindowText(hWnd,"window ");
}
void OnOpen(HWND hWnd)
{
	FILE *pFile=fopen("f:/my.txt","r");
	fseek(pFile,0,SEEK_END);
	long nLen = ftell(pFile);
	char* pszText=(char*)malloc(nLen+1);
	memset(pszText,0,nLen+1);
	fseek(pFile,0,SEEK_SET);
	fread(pszText,1,nLen,pFile);
	fclose(pFile);
	HWND hEdit = GetDlgItem(hWnd,1001);
	SendMessage(hEdit,WM_SETTEXT,0,(LPARAM)pszText);
	free(pszText);
}
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1001:
		if(HIWORD(wParam)==EN_CHANGE)
		{
			SetWindowText(hWnd,"window *");
		}
		break;
	case ID_SAVE:
		OnSave(hWnd);
		break;
	case ID_OPEN:
		OnOpen(hWnd);
		break;
	}
}
void OnCreate(HWND hWnd)
{
	HWND hEdit = CreateWindowEx(0,"EDIT","hello",
		WS_CHILD|WS_VISIBLE|ES_MULTILINE|
		ES_AUTOHSCROLL|ES_AUTOVSCROLL|
		WS_HSCROLL|WS_VSCROLL
		,0,0,100,100,hWnd,(HMENU)1001,
		g_hInstance,NULL);
	HFONT hFont = CreateFont(30,0,0,0,900,0,0,0,
		GB2312_CHARSET,0,0,0,0,"黑体");
	SendMessage(hEdit,WM_SETFONT,(WPARAM)hFont,1);
}
void OnSize(HWND hWnd,LPARAM lParam)
{
	int nWidth = LOWORD(lParam);
	int nHight = HIWORD(lParam);
	HWND hEdit = GetDlgItem(hWnd,1001);
	MoveWindow(hEdit,0,0,nWidth,nHight,true);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CTLCOLOREDIT:
		{
		HDC hdcEdit = (HDC)wParam;
		SetTextColor(hdcEdit,RGB(0,255,0));
		SetBkColor(hdcEdit,RGB(255,0,0));
		return (LRESULT)CreateSolidBrush(RGB(255,0,0));
		}
		break;
	case WM_SIZE:
		OnSize(hWnd,lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
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



