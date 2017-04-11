// AnimateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Animate.h"
#include "AnimateDlg.h"

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
// CAnimateDlg dialog

CAnimateDlg::CAnimateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimateDlg)
	m_sPath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimateDlg)
	DDX_Control(pDX, IDC_REPLAY, m_wndReplay);
	DDX_Control(pDX, IDC_PLAY_COUNT, m_wndPlayCount);
	DDX_Control(pDX, IDC_VIDEO, m_wndVideo);
	DDX_Control(pDX, IDC_LIST_NAME, m_wndListName);
	DDX_Text(pDX, IDC_FILE_PATH, m_sPath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimateDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_FILE, OnOpenFile)
	ON_LBN_DBLCLK(IDC_LIST_NAME, OnDblclkListName)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_REPLAY, OnReplay)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg message handlers

BOOL CAnimateDlg::OnInitDialog()
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
	m_wndPlayCount.EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAnimateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAnimateDlg::OnPaint() 
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
HCURSOR CAnimateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAnimateDlg::OnOpenFile() 
{
	// 1弹出打开文件对话框
	char szFilter[]=
		"视频文件(*.avi)|*.avi|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,NULL);
	if(dlg.DoModal()==IDCANCEL)return;
	// 2在文本框中显示文件路径
	m_sPath=dlg.GetPathName();
	UpdateData(FALSE);
	// 3在列表框中添加文件名称
	CString sName=dlg.GetFileName();
	//通过判断防止重复添加
	if(m_wndListName.FindString(-1,sName)==-1)
	{
		int nIndex = m_wndListName.AddString(sName);
		//通过附加数据添加文件路径
		CString *pPath = new CString;
		*pPath = m_sPath;
		m_wndListName.SetItemData(nIndex,(DWORD)pPath);
	}
	// 4在动画控件中播放视频文件
	Play();
}

void CAnimateDlg::OnDblclkListName() 
{
	// 获取双击选择的文件
	int nSel=m_wndListName.GetCurSel();
	if(nSel==-1)return;
	// 在文本框中显示当前的文件路径
	CString *pPath =(CString*)m_wndListName.GetItemData(nSel);
	m_sPath=*pPath;
	UpdateData(FALSE);
	// 播放文件
	Play();
}

void CAnimateDlg::Play()
{
	int nCount = 0;
	if(m_wndReplay.GetCheck())
	{
		//根据组合框控件的选项设置播放次数
		int nSel = m_wndPlayCount.GetCurSel();
		switch(nSel)
		{
		case 0:
			nCount=2;
			break;
		case 1:
			nCount=3;
			break;
		case 2:
			nCount=-1;
			break;
		}
	}
	else
	{
		nCount = 1;
	}
	m_wndVideo.Open(m_sPath);
	m_wndVideo.Play(0,-1,nCount);
}

void CAnimateDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	int nCount=m_wndListName.GetCount();
	for(int i=0;i<nCount;i++)
	{
		CString *pPath=
			(CString*)m_wndListName.GetItemData(i);
		delete pPath;
	}
	CDialog::OnClose();
}

void CAnimateDlg::OnReplay() 
{
	m_wndPlayCount.EnableWindow(m_wndReplay.GetCheck());
}

void CAnimateDlg::OnPlay() 
{
	Play();
}

void CAnimateDlg::OnStop() 
{
	m_wndVideo.Stop();	
}
