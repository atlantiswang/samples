#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
INT CALLBACK DlgProc(HWND hwndlg,UINT msg,
						WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		MessageBox(hwndlg,"WM_INITDIALOG","infor",MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndlg,"WM_CREATE","infor",MB_OK);
		break;
	case WM_SYSCOMMAND:
		if(wParam == SC_CLOSE)
		{
			//销毁模式对话框,只能用EndDialog,不能用DestroyWindow等函数
			//虽然能销毁对话框，但不能使DIALOGBOX函数解除阻塞
			EndDialog(hwndlg,1001);
			return true;
		}
		break;
	}
	//将消息交给真正对话框处理函数做默认处理
	return FALSE;
}
void OnModel(HWND hWnd)
{
	//阻塞函数
	int nRet = DialogBox(g_hInstance,
		MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DlgProc);
	if(nRet == 1001)
		MessageBox(hWnd,"successful","infor",MB_OK);
}
void OnCommand(HWND hWnd,WPARAM wParam)
{
	switch(LOWORD(wParam))
	{
	case ID_MODEL:
		OnModel(hWnd);//创建模式对话框
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



