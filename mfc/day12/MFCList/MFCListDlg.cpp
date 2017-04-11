// MFCListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCList.h"
#include "MFCListDlg.h"

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
// CMFCListDlg dialog

CMFCListDlg::CMFCListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCListDlg)
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_STYLE, m_wndStyle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCListDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCListDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_STYLE, OnSelchangeStyle)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCListDlg message handlers

BOOL CMFCListDlg::OnInitDialog()
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
	m_wndStyle.SetCurSel(3);
	InitListCtrl();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCListDlg::OnPaint() 
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
HCURSOR CMFCListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCListDlg::InitListCtrl()
{
	//创建图标列表和小图标列表
	m_ilNormal.Create(IDB_NORMAL,32,1,RGB(0,0,0));
	m_ilSmall.Create(IDB_SMALL,18,1,RGB(0,0,0));
	//将图标列表设置到控件上
	m_wndList.SetImageList(&m_ilNormal,LVSIL_NORMAL);
	m_wndList.SetImageList(&m_ilSmall,LVSIL_SMALL);
	//插入控件的列
	m_wndList.InsertColumn(0,"名称",LVCFMT_LEFT,100);
	m_wndList.InsertColumn(1,"大小",LVCFMT_LEFT,100);
	m_wndList.InsertColumn(2,"类型",LVCFMT_LEFT,100);
	m_wndList.InsertColumn(3,"修改日期",LVCFMT_LEFT,150);
	//插入数据项
	m_wndList.InsertItem(0,"文件",1);
	m_wndList.InsertItem(1,"文件夹",0);
	//设置其它各列的文本
	m_wndList.SetItemText(0,1,"125k");
	m_wndList.SetItemText(0,3,"2015-10-19");
	m_wndList.SetItemText(1,2,"文件夹");
	m_wndList.SetItemText(1,3,"2015-10-19");
	//显示c:根目录下的文件和目录
	ShowData("c:");
	//设置控件的背景图片
	//初始化OLE库
	AfxOleInit();
	m_wndList.SetBkImage("g:/others/windows.bmp");
	//设置字体的背景色为透明
	m_wndList.SetTextBkColor(CLR_NONE);
}

void CMFCListDlg::ShowData(CString sPath)
{
	//在添加新的数据前，首先清空控件
	m_wndList.DeleteAllItems();
	m_lstPath.RemoveAll();
	//结合CFileFind类获取数据添加到控件
	CFileFind file;
	BOOL bRet=file.FindFile(sPath+"/*.*");
	int nItem=0;

	while(bRet)
	{
		bRet = file.FindNextFile();
		CString sName = file.GetFileName();
		if(file.IsDirectory())
		{
			m_wndList.InsertItem(nItem,sName,0);
			m_wndList.SetItemText(nItem,2,"文件夹");
		}else
		{
			m_wndList.InsertItem(nItem,sName,1);
			int nLen = file.GetLength();
			CString strLen;
			strLen.Format("%dB",nLen);
			m_wndList.SetItemText(nItem,1,strLen);
		}
		//设置日期列
		CTime t;
		file.GetLastWriteTime(t);
		CString sTime=t.Format("%Y年%m月%d日%H:%M");
		m_wndList.SetItemText(nItem,3,sTime);
		/*
		//通过数据项的附加数据保存路径
		CString *pPath=new CString;
		*pPath=file.GetFilePath();
		m_wndList.SetItemData(nItem,(DWORD)pPath);
		*/
		//向链表中添加文件路径
		m_lstPath.AddTail(file.GetFilePath());
		nItem++;
	}
}

void CMFCListDlg::OnSelchangeStyle() 
{
	//根据组合框控件的选项设置列表控件的显示风格
	int nSel=m_wndStyle.GetCurSel();
	switch(nSel)
	{
	case 0://图标
		m_wndList.ModifyStyle(
			LVS_SMALLICON|LVS_LIST|LVS_REPORT,LVS_ICON);
		break;
	case 1://小图标
		m_wndList.ModifyStyle(
			LVS_ICON|LVS_LIST|LVS_REPORT,LVS_SMALLICON);
		break;
	case 2://列表
		m_wndList.ModifyStyle(
			LVS_SMALLICON|LVS_REPORT|LVS_ICON,LVS_LIST);
		break;
	case 3://报表
		m_wndList.ModifyStyle(
			LVS_SMALLICON|LVS_LIST|LVS_ICON,LVS_REPORT);
		break;
	}
}

void CMFCListDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//获取双击时的选项
	LPNMITEMACTIVATE pItem=(LPNMITEMACTIVATE)pNMHDR;
	int nItem=pItem->iItem;
	if(nItem==-1)return;
	/*
	//根据索引获取附加数据（路径的指针）
	CString *pPath=(CString*)m_wndList.GetItemData(nItem);
	ShowData(*pPath);*/
	//从链表中获取文件路径
	CString sPath=
		m_lstPath.GetAt(m_lstPath.FindIndex(nItem));
	ShowData(sPath);
	*pResult = 0;
}
