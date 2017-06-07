// UseDispMathDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UseDispMath.h"
#include "UseDispMathDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseDispMathDlg dialog

CUseDispMathDlg::CUseDispMathDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUseDispMathDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUseDispMathDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUseDispMathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUseDispMathDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUseDispMathDlg, CDialog)
	//{{AFX_MSG_MAP(CUseDispMathDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseDispMathDlg message handlers

BOOL CUseDispMathDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUseDispMathDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUseDispMathDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUseDispMathDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUseDispMathDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here

	//根据ProgID得到CLSID
	WCHAR* progID=L"DispMath.Math";
	CLSID clsid={0};
	CLSIDFromProgID(progID,&clsid);
	//创建对象，返回IDispatch接口
	IDispatch *piDispatch=NULL;
	CoCreateInstance(clsid,NULL,CLSCTX_ALL,
		IID_IDispatch,(LPVOID*)&piDispatch);
	//获取接口函数对应的接口函数的ID
	WCHAR *pszName=L"Add";//输入的接口函数的名称
	DISPID nID=0;//保存返回的接口函数的ID
    piDispatch->GetIDsOfNames(IID_NULL,&pszName,
		1,LOCALE_SYSTEM_DEFAULT,&nID);
	//根据接口函数的ID，调用该接口函数
	//调用接口函数前，构造函数的参数
	VARIANT varParam[3]={0};
	//把参数添加到数组中的顺序是从右至左
	long nAdd=0;//保存计算结果
    varParam[0].plVal=&nAdd;
	varParam[0].vt=VT_I4|VT_BYREF;
	varParam[1].lVal=100;
	varParam[1].vt=VT_I4;
	varParam[2].lVal=100;
	varParam[2].vt=VT_I4;
	//将数组赋值给表示参数的结构体变量
	DISPPARAMS  params={0};
	params.cArgs=3;
	params.rgvarg=varParam;
	VARIANT varResult={0};
	//调用接口函数
    piDispatch->Invoke(nID,IID_NULL,LOCALE_SYSTEM_DEFAULT,
		DISPATCH_METHOD,&params,&varResult,NULL,NULL);
    //输出计算结果
	CString strAdd;
	strAdd.Format("nAdd=%d",nAdd);
	MessageBox(strAdd);







}
