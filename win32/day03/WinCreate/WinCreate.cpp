#include "stdafx.h"
#include "stdio.h"
//#include "stdlib.h"
HINSTANCE g_hInstance=0;
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY://窗口被销毁时的消息，
		PostQuitMessage(0);//产生WM_QUIT消息
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
BOOL Register(LPSTR lpClassName,WNDPROC WndProc)
{
	WNDCLASSEX wce={0};
	wce.cbSize=sizeof(wce);
	wce.cbClsExtra=200;//窗口类的附加数据BUFF大小
	wce.cbWndExtra=200;//窗口的附加数据BUFF大小
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
HWND CreateChild(LPSTR lpClassName,LPSTR lpWndName,
				 HWND hParent)
{
	HWND hChild=CreateWindowEx(0,lpClassName,lpWndName,
			WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW,
			100,100,200,200,hParent,NULL,
			g_hInstance,NULL);
	return hChild;
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
	while(GetMessage(&nMsg,NULL,0,0))//NUll说明所有窗口的消息
	{//0,0最大ID，最小ID获取ID

	//GetMessage获得WM_QUIT时返回0
		TranslateMessage(&nMsg);
		//只翻译键盘的消息（可见字符部分）
		DispatchMessage(&nMsg);
	}
}
//写入数据
void SetExtra(HWND hWnd)
{
	char *pszText ="hello data";
	SetClassLong(hWnd,0,(LONG)pszText);
	SetWindowLong(hWnd,0,100);
}
//读取数据
void GetExtra(HWND hWnd)
{
	long nClass=GetClassLong(hWnd,0);
	long nWnd=GetWindowLong(hWnd,0);
	char szText[256]={0};
	sprintf(szText,"窗口类:%s,窗口:%d",nClass,nWnd);
	MessageBox(NULL,szText,"infor",MB_OK);
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
	Register("Child",DefWindowProc);
	HWND hChild1=CreateChild("Child","c1",hWnd);
	HWND hChild2=CreateChild("Child","c2",hWnd);
	MoveWindow(hChild2,200,200,500,500,true);
	SetExtra(hChild1);
	GetExtra(hChild2);
	Message();
	return 0;
}



