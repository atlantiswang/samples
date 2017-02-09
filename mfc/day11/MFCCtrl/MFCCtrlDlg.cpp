// MFCCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCCtrl.h"
#include "MFCCtrlDlg.h"

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
// CMFCCtrlDlg dialog

CMFCCtrlDlg::CMFCCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCCtrlDlg)
	DDX_Control(pDX, IDC_LIST5, m_wndList5);
	DDX_Control(pDX, IDC_LIST1, m_wndList1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCCtrlDlg message handlers

BOOL CMFCCtrlDlg::OnInitDialog()
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
	//为第一个列表框控件添加数据项
	m_wndList1.AddString("北京");
	m_wndList1.AddString("上海");
	m_wndList1.AddString("天津");
	m_wndList1.AddString("重庆");
	m_wndList1.SetCurSel(3);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCCtrlDlg::OnPaint() 
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
HCURSOR CMFCCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCCtrlDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString szText;
	int nIndex = m_wndList1.GetCurSel();
	if(nIndex==-1) return;
	m_wndList1.GetText(nIndex,szText);
	m_wndList5.AddString(szText);
	m_wndList1.DeleteString(nIndex);
}

void CMFCCtrlDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	int nCount = m_wndList1.GetCount();
	CString szText;
	for(int i=0;i<nCount;i++)
	{
		m_wndList1.GetText(0,szText);
		m_wndList5.AddString(szText);
		m_wndList1.DeleteString(0);
	}
//	m_wndList1.ResetContent();
}

void CMFCCtrlDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CString szText;
	int nIndex = m_wndList5.GetCurSel();
	if(nIndex==-1)return;
	m_wndList5.GetText(nIndex,szText);
	m_wndList1.AddString(szText);
	m_wndList5.DeleteString(nIndex);
}

void CMFCCtrlDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	int nCount = m_wndList5.GetCount();
	for(int i=0;i<nCount;i++)
	{
		CString szText;
		m_wndList5.GetText(i,szText);
		m_wndList1.AddString(szText);
	}
	m_wndList5.ResetContent();
}
