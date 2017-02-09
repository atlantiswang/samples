#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;
int g_kind=0;//标志量
void OnCommand(HWND hWnd,WPARAM wParam)
{//绘图必须在paint消息里画
	g_kind = LOWORD(wParam);
	switch(LOWORD(wParam))
	{
	case ID_REC:
	case ID_PIT:
	case ID_CIR:
	case ID_LINE:
	case ID_BMP:
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	}
}
void DrawPit(HDC hdc)
{
	for(int i=0;i<256;i++)
		for(int j=0;j<256;j++)
		SetPixel(hdc,i,j,RGB(i,j,0));
}
void DrawCir(HDC hdc)
{
	//其实这个函数是画椭圆的
	Ellipse(hdc,200,200,300,300);
	Ellipse(hdc,240,240,500,54);
}
void DrawLine(HDC hdc)
{
	MoveToEx(hdc,50,50,NULL);
	LineTo(hdc,200,100);
//	Arc(hdc,200,300,400,500,230,230,450,450);
	//按逆时针方向取弧
	//下面的函数设置取弧方向
	SetArcDirection(hdc,AD_CLOCKWISE);
	Arc(hdc,200,300,400,500,230,230,450,450);
}
void DrawRec(HDC hdc)
{
	Rectangle(hdc,300,-300,400,-400);
	//绘制圆角矩形,后面两个参数表示弧的宽和高（两个弧）
	RoundRect(hdc,100,100,300,30,10,10);
}
void DrawBmp(HDC hdc)
{
	//添加资源
	//加载位图
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	BITMAP bmpInfo = {0};
	//动态获取位图的宽和高
	GetObject(hBmp,sizeof(bmpInfo),&bmpInfo);
	//创建一个与当前DC匹配的内存DC并构建一个虚拟区域
	HDC hMemdc = CreateCompatibleDC(hdc);
	HGDIOBJ nOldBmp = SelectObject(hMemdc,hBmp);
	//将图片送给内存DC后，内存DC立即将图片在虚拟区域中绘制出来
	BitBlt(hdc,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,hMemdc,10,10,SRCCOPY);
//	StretchBlt(hdc,100,100,240,240,hMemdc,
//				0,0,48,48,NOTSRCCOPY);
	//缩放成像
	SelectObject(hMemdc,nOldBmp);//这个函数是替换功能，所以能要回来
	DeleteObject(hBmp);
	DeleteObject(hMemdc);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps={0};
	HDC hdc = BeginPaint(hWnd,&ps);
	HPEN hPen = CreatePen(PS_DASH,1,RGB(255,0,0));
	HGDIOBJ nOldPen = SelectObject(hdc,hPen);
//	HBRUSH hBrush= CreateSolidBrush(RGB(0,255,0));
//	HBRUSH hBrush= CreateHatchBrush(HS_CROSS,
//									RGB(0,255,0));
//	HBRUSH hBrush= CreatePatternBrush();
	//透明刷子
//	HGDIOBJ hBrush= GetStockObject(NULL_BRUSH);
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	//位图画刷要创建位图资源
	HGDIOBJ nOldBrush = SelectObject(hdc,hBrush);
	int nOldMode = SetMapMode(hdc,MM_ANISOTROPIC);
	SetWindowExtEx(hdc,1,1,NULL);
	SetViewportExtEx(hdc,3,3,NULL);
	//想改变坐标的方向，改变数字的正负号
	switch(g_kind)
	{
	case ID_BMP:
		DrawBmp(hdc);
		break;
	case ID_REC:
		DrawRec(hdc);
		break;
	case ID_PIT:
		DrawPit(hdc);
		break;
	case ID_CIR:
		DrawCir(hdc);
		break;
	case ID_LINE:
		DrawLine(hdc);
		break;
	}
	SetMapMode(hdc,nOldMode);
	SelectObject(hdc,nOldBrush);
	SelectObject(hdc,nOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	EndPaint(hWnd,&ps);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
						 WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_PAINT:
		OnPaint(hWnd);
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
	wce.hbrBackground=CreateSolidBrush(RGB(0,0,255));
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
	//WM_PAINT消息：GetMessage函数会不定期地去看看需不需要
	//PAINT，需要的话就产生WM_PAINT消息
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



