#include "stdafx.h"
//窗口处理函数(处理消息)
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,
						WPARAM wParam,LPARAM lParam)
{
	return DefWindowProc(hWnd,nMsg,wParam,lParam);
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//注册窗口类（往操作系统里写数据）
	WNDCLASS wc = {0};
	wc.cbClsExtra=0;//开几个字节的缓冲区
	wc.cbWndExtra=0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor=NULL;
	wc.hIcon =NULL;
	wc.hInstance=hInstance;
	wc.lpfnWndProc =(WNDPROC)WndProc;
	wc.lpszClassName="Main";
	wc.lpszMenuName =NULL;
	wc.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND hWnd=CreateWindow("Main","window",
		WS_OVERLAPPEDWINDOW,
		100,100,500,500,NULL,NULL,
		hInstance,NULL);
	ShowWindow(hWnd,SW_SHOW);
	//UpdateWindow(hWnd);
	MSG umsg={0};
	while(GetMessage(&umsg,NULL,0,0))
	{
		TranslateMessage(&umsg);
		DispatchMessage(&umsg);
	}
	return 0;
}



