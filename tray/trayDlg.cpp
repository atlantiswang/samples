
// trayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tray.h"
#include "trayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CtrayDlg dialog




CtrayDlg::CtrayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtrayDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtrayDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON1, &CtrayDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_USER_NOTIFYICON, &CtrayDlg::OnNotifyIcon)
	ON_WM_WINDOWPOSCHANGING()
	ON_COMMAND(ID_POPUP_EXIT, &CtrayDlg::OnPopupExit)
END_MESSAGE_MAP()


LRESULT CtrayDlg::OnNotifyIcon(WPARAM wparam, LPARAM lparam)
{
	if(wparam!=IDR_MAINFRAME || 
		(lparam != WM_RBUTTONUP /*&& lparam != WM_LBUTTONDBLCLK*/))
		return    1;    

	CMenu menu;
	if(!menu.LoadMenu(IDR_MENU_TRAY))
		return 1;

	CMenu *pMenu = menu.GetSubMenu(0);
	if (!pMenu)
		return 1;
	if (lparam == WM_RBUTTONUP)
	{

		CPoint pt;
		GetCursorPos(&pt);
		this->SetForegroundWindow();
		//::TrackPopupMenu(pMenu->m_hMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, m_tnid.hWnd, NULL);
		pMenu->TrackPopupMenu(TPM_BOTTOMALIGN, pt.x, pt.y, (CWnd*)this);
	}

	return 0;  
}
// CtrayDlg message handlers

BOOL CtrayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_tray.init();

	//m_tray.test();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtrayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtrayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtrayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtrayDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_tray.modifytray(L"wh2396", L"wh2396@foxmail.com");
}

void CtrayDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	static UINT nShow = 3;
	if(nShow && !IsWindowVisible())
	{
		nShow--;
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}
	CDialog::OnWindowPosChanging(lpwndpos);

	// TODO: Add your message handler code here
}

void CtrayDlg::OnPopupExit()
{
	// TODO: Add your command handler code here
	PostQuitMessage(0);
}
