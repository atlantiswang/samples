#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
HINSTANCE g_hInstance=0;
void OnCreate(HWND hWnd)
{
	CreateWindowEx(0,"COMBOBOX","Simple",
		WS_CHILD|WS_VISIBLE|CBS_SIMPLE|WS_VSCROLL,
		50,50,200,200,hWnd,(HMENU)1001,
		g_hInstance,NULL);
	CreateWindowEx(0,"COMBOBOX","DropDown",
		WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|WS_VSCROLL,
		260,50,200,200,hWnd,(HMENU)1002,
		g_hInstance,NULL);
	CreateWindowEx(0,"COMBOBOX","DropList",
		WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,
		470,50,200,200,hWnd,(HMENU)1003,
		g_hInstance,NULL);
}
void OnAdd(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd,1001);
	HWND hDropDown = GetDlgItem(hWnd,1002);
	HWND hDropList = GetDlgItem(hWnd,1003);
	for(int i=0;i<100;i++)
	{
		char szItem[256]={0};
		sprintf(szItem,"Item%d",i);
		SendMessage(hSimple,CB_ADDSTRING,0,(LPARAM)szItem);
		SendMessage(hDropDown,CB_ADDSTRING,0,(LPARAM)szItem);
		SendMessage(hDropList,CB_ADDSTRING,0,(LPARAM)szItem);
		char* pszText = "hello data";
		SendMessage(hSimple,CB_SETITEMDATA,i,(LPARAM)pszText);
	}
	SendMessage(hSimple,CB_SETCURSEL,99,0);
	SendMessage(hDropDown,CB_SETCURSEL,99,0);
	SendMessage(hDropList,CB_SETCURSEL,99,0);
}
void OnClean(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd,1001);
	HWND hDropDown = GetDlgItem(hWnd,1002);
	HWND hDropList = GetDlgItem(hWnd,1003);
	SendMessage(hSimple,CB_RESETCONTENT,0,0);
	SendMessage(hDropDown,CB_RESETCONTENT,0,0);
	SendMessage(hDropList,CB_RESETCONTENT,0,0);
}
void OnDelete(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd,1001);
	HWND hDropDown = GetDlgItem(hWnd,1002);
	HWND hDropList = GetDlgItem(hWnd,1003);
	LRESULT nSel = SendMessage(hSimple,CB_GETCURSEL,0,0);
	SendMessage(hSimple,CB_DELETESTRING,nSel,0);
	nSel = SendMessage(hDropDown,CB_GETCURSEL,0,0);
	SendMessage(hDropDown,CB_DELETESTRING,nSel,0);
	nSel = SendMessage(hDropList,CB_GETCURSEL,0,0);
	SendMessage(hDropList,CB_DELETESTRING,nSel,0);
}
void OnFind(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd,1001);
	char szText[]="Item";
	LRESULT nFind = SendMessage(hSimple,
		CB_SELECTSTRING,-1,(LPARAM)szText);
	if(nFind!=CB_ERR)
	{
		char szFind[256] = {0};
		sprintf(szFind,"匹配到的选项为:%d",nFind);
		MessageBox(hWnd,szFind,"infor",MB_OK);
	}else{
		MessageBox(hWnd,"匹配失败","infor",MB_OK);
	}
}
void OnText(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd,1001);
	LRESULT nSel = SendMessage(hSimple,CB_GETCURSEL,0,0);
	char szText[256]={0};
	SendMessage(hSimple,CB_GETLBTEXT,nSel,(LPARAM)szText);
	MessageBox(hWnd,szText,"infor",MB_OK);
	char szText1[256]={0};
	SendMessage(hSimple,WM_GETTEXT,256,(LPARAM)szText1);
	MessageBox(hWnd,szText1,"infor",MB_OK);
}
void OnData(HWND hWnd)
{
	HWND hSimple = GetDlgItem(hWnd,1001);
	LRESULT nSel = SendMessage(hSimple,CB_GETCURSEL,0,0);
	LRESULT nData = SendMessage(hSimple,CB_GETITEMDATA,nSel,0);
	char szData[256] = {0};
	sprintf(szData,"附加数据:%s",nData);
	MessageBox(hWnd,szData,"infor",MB_OK);
}
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1001:
		if(HIWORD(wParam)==CBN_SELCHANGE)
		{
				HWND hSimple = GetDlgItem(hWnd,1001);
				HWND hDropDown = GetDlgItem(hWnd,1002);
				HWND hDropList = GetDlgItem(hWnd,1003);
				LRESULT nSel = SendMessage(hSimple,CB_GETCURSEL,0,0);
				SendMessage(hDropDown,CB_SETCURSEL,nSel,0);
				SendMessage(hDropList,CB_SETCURSEL,nSel,0);
		}else if(HIWORD(wParam)==CBN_EDITCHANGE)
		{
			MessageBox(hWnd,"内容有变化","infor",MB_OK);
		}
		break;
	case ID_DATA:
		OnData(hWnd);
		break;
	case ID_TEXT:
		OnText(hWnd);//获取选择项的文本内容
		break;
	case ID_FIND:
		OnFind(hWnd);
		break;
	case ID_DELETE:
		OnDelete(hWnd);
		break;
	case ID_CLEAN:
		OnClean(hWnd);
		break;
	case ID_ADD:
		OnAdd(hWnd);
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



