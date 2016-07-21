
// UserChangePassword_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserChangePassword_MFC.h"
#include "UserChangePassword_MFCDlg.h"

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


// CUserChangePassword_MFCDlg 对话框




CUserChangePassword_MFCDlg::CUserChangePassword_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserChangePassword_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUserChangePassword_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserChangePassword_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CUserChangePassword_MFCDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserChangePassword_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserChangePassword_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserChangePassword_MFCDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CUserChangePassword_MFCDlg 消息处理程序

BOOL CUserChangePassword_MFCDlg::OnInitDialog()
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
	pSysMenu->AppendMenu(MF_STRING, ID_NEW, _T("测试"));
	
	GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	SetDlgItemText(IDC_EDIT1, _T("test"));
	SetDlgItemText(IDC_EDIT1, _T("tefeiw"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUserChangePassword_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == ID_NEW)
	{
		OnNew();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUserChangePassword_MFCDlg::OnPaint()
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
HCURSOR CUserChangePassword_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUserChangePassword_MFCDlg::OnNew()
{
	AfxMessageBox(_T("测试成功"));
}

void CUserChangePassword_MFCDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("测试"));
	return;
	OnOK();
}

void CUserChangePassword_MFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	AfxMessageBox(str);
}

#include "TestDlg.h"
void CUserChangePassword_MFCDlg::OnBnClickedButton2()
{
	CTestDlg dlg;
	dlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

void CUserChangePassword_MFCDlg::OnBnClickedButton3()
{
	::MessageBox(this->m_hWnd, _T("测试是否模态"), _T("MessageBox"), MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}
