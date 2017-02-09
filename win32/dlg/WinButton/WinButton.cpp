#include "stdafx.h"
HINSTANCE g_hInstance=0;
void OnCreate(HWND hWnd)
{
	CreateWindowEx(0,"BUTTON","OK",
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		50,50,100,40,hWnd,(HMENU)1001,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","GroupBox",
		WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
		30,30,300,400,hWnd,(HMENU)1002,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","CheckBox",
		WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
		50,100,200,30,hWnd,(HMENU)1003,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","AutoCheckBox",
		WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,
		50,140,200,30,hWnd,(HMENU)1004,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","3State",
		WS_CHILD|WS_VISIBLE|BS_3STATE,
		50,180,200,30,hWnd,(HMENU)1005,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","Auto3State",
		WS_CHILD|WS_VISIBLE|BS_AUTO3STATE,
		50,220,200,30,hWnd,(HMENU)1006,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","A霸天虎",
		WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|
		WS_GROUP,
		50,260,200,20,hWnd,(HMENU)1007,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","B汽车人",
		WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
		50,290,200,20,hWnd,(HMENU)1008,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","C喜羊羊",
		WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|
		WS_GROUP,
		50,320,200,20,hWnd,(HMENU)1009,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","D灰太狼",
		WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
		50,350,200,20,hWnd,(HMENU)1010,
		g_hInstance,NULL);
	CreateWindowEx(0,"BUTTON","多态按钮",
		WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|
		BS_PUSHLIKE,
		50,380,100,40,hWnd,(HMENU)1011,
		g_hInstance,NULL);
} 
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case 1005:
		if(HIWORD(wParam)==BN_CLICKED)
		{
			HWND h3State=GetDlgItem(hWnd,1005);
			LRESULT nRet = SendMessage(h3State,
				BM_GETCHECK,0,0);
			if(nRet == BST_CHECKED)
			{
				SendMessage(h3State,BM_SETCHECK,
					BST_INDETERMINATE,0);
			}else if(nRet==BST_INDETERMINATE)
			{
				SendMessage(h3State,BM_SETCHECK,
					BST_UNCHECKED,0);
			}else
			{
				SendMessage(h3State,BM_SETCHECK,
					BST_CHECKED,0);
			}
		}
		break;
	case 1003:
		if(HIWORD(wParam)==BN_CLICKED)
		{
			HWND hCheck = GetDlgItem(hWnd,1003);
			LRESULT nRet = SendMessage(hCheck,
				BM_GETCHECK,0,0);
			if(nRet == BST_CHECKED)
			{
				SendMessage(hCheck,BM_SETCHECK,
					BST_UNCHECKED,0);
			}else{
				SendMessage(hCheck,BM_SETCHECK,
					BST_CHECKED,0);
			}
		}
		break;
	case 1001:
		if(HIWORD(wParam)==BN_CLICKED)
		{
			MessageBox(hWnd,"点了OK","infor",MB_OK);
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



