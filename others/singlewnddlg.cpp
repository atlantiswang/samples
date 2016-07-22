
// SingleWndDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SingleWnd.h"
#include "SingleWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSingleWndDlg 对话框




CSingleWndDlg::CSingleWndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSingleWndDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDlg = NULL;
}

void CSingleWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSingleWndDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSingleWndDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_USER_NOTIFY, OnNotifyMsg)
	ON_COMMAND(ID_POPUP_32773, &CSingleWndDlg::OnPopupExit)
	ON_COMMAND(ID_POPUP_32771, &CSingleWndDlg::OnPopupDlg1)
	ON_COMMAND(ID_POPUP_32772, &CSingleWndDlg::OnPopupDlg2)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_POPUP_32774, &CSingleWndDlg::OnPopupNoModal)
END_MESSAGE_MAP()


// CSingleWndDlg 消息处理程序

BOOL CSingleWndDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_NotifyIcon.cbSize = sizeof(m_NotifyIcon);
	m_NotifyIcon.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_NotifyIcon.hWnd = this->m_hWnd;
	m_NotifyIcon.uID = IDR_MAINFRAME;
	wcscpy(m_NotifyIcon.szTip, _T("the united states"));
	m_NotifyIcon.uCallbackMessage = WM_USER_NOTIFY;
	m_NotifyIcon.uFlags = NIF_ICON|NIF_TIP|NIF_MESSAGE;

	Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon);

	m_pDlgShowing = NULL;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSingleWndDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		if (HasShowingDlg())
			return ;
		CAboutDlg dlgAbout;
		m_pDlgShowing = &dlgAbout;
		dlgAbout.DoModal();
		m_pDlgShowing = NULL;
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSingleWndDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSingleWndDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "MyDlg1.h"
void CSingleWndDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

LRESULT CSingleWndDlg::OnNotifyMsg(WPARAM wparam,LPARAM lparam)
{
	if(wparam != IDR_MAINFRAME||
		(lparam !=WM_RBUTTONUP && lparam != WM_LBUTTONDBLCLK))
		return 0;
	
	CMenu menu;
	if (!menu.LoadMenu(IDR_MENU_NOTIFY))
		return 0;
	CMenu *pSubMenu = menu.GetSubMenu(0);
	if (!pSubMenu)
		return 0;
	
	if (lparam == WM_RBUTTONUP)
	{
		pSubMenu->SetDefaultItem(0, TRUE);

		CPoint mouse;
		GetCursorPos(&mouse);
		this->SetForegroundWindow();
		::TrackPopupMenu(pSubMenu->m_hMenu, TPM_BOTTOMALIGN, mouse.x, mouse.y, 0, m_NotifyIcon.hWnd, NULL);
	} else
	{
		ShowWindow(SW_SHOW);
	}

	return 1;
}
void CSingleWndDlg::OnPopupExit()
{
	// TODO: 在此添加命令处理程序代码
	this->EndDialog(IDCANCEL);
}

void CSingleWndDlg::OnPopupDlg1()
{
	// TODO: 在此添加命令处理程序代码
	if (HasShowingDlg())
		return ;

	CMyDlg1 dlg;
	m_pDlgShowing = &dlg;
	dlg.m_style = DOMAL;
	dlg.DoModal();
	m_pDlgShowing = NULL;
}

void CSingleWndDlg::OnPopupDlg2()
{
	// TODO: 在此添加命令处理程序代码
	if (HasShowingDlg())
		return ;

	CMyDlg1 dlg;
	m_pDlgShowing = &dlg;
	dlg.m_style = DOMAL;
	dlg.DoModal();
	m_pDlgShowing = NULL;
}

void CSingleWndDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//this->SetForegroundWindow();

	CDialog::OnLButtonDown(nFlags, point);
}

bool CSingleWndDlg::HasShowingDlg(void)
{
	if (m_pDlgShowing)
	{
		m_pDlgShowing->SetForegroundWindow();
		FLASHWINFO fi = {0};
		fi.cbSize = sizeof(fi);
		fi.hwnd = m_pDlgShowing->GetSafeHwnd();
		fi.dwFlags = FLASHW_CAPTION;
		fi.uCount = 3;
		fi.dwTimeout = 10;
		::FlashWindowEx(&fi);
		return true;
	}

	return false;
}

void CSingleWndDlg::OnPopupNoModal()
{
	// TODO: 在此添加命令处理程序代码
	if (HasShowingDlg())
		return ;

	CMyDlg1 *pdlg = new CMyDlg1();
	m_pDlgShowing = pdlg;
	pdlg->Create(IDD_DIALOG1);
	pdlg->ShowWindow(SW_NORMAL);
}
