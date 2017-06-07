// InitTokenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InitToken.h"
#include "InitTokenDlg.h"
#include "commonfunc.h"
#include <string>


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
// CInitTokenDlg dialog

CInitTokenDlg::CInitTokenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitTokenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitTokenDlg)
	m_strConfUserPIN = _T("");
	m_strSoPIN = _T("");
	m_strUserPIN = _T("");
	m_strTokenName = _T("");
	m_strCurrentTokenName = _T("");
	m_strOldUserPIn = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSlotList = NULL_PTR;
	m_pApplication = new char[255];
	ZeroMemory(m_pApplication, 255);
	lstrcpy((char*)m_pApplication, "InitToken Demo App");
	m_ulMinPin = 0;
	m_ulMaxPin = 0;
	m_ulSlotId = 0;
}

CInitTokenDlg::~CInitTokenDlg()
{
	delete[] m_pApplication;
	if(m_pSlotList)
	{
		delete[] m_pSlotList;
		m_pSlotList = NULL_PTR;
	}
}

void CInitTokenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitTokenDlg)
	DDX_Control(pDX, IDC_EDIT_OLD_USER_PIN, m_ctrlOleUserPin);
	DDX_Control(pDX, IDC_EDIT_USER_PIN, m_ctrlUserPin);
	DDX_Control(pDX, IDC_EDIT_SO_PIN, m_ctrlSoPin);
	DDX_Control(pDX, IDC_EDIT_CONF_USER_PIN, m_ctrlConfUserPin);
	DDX_Text(pDX, IDC_EDIT_CONF_USER_PIN, m_strConfUserPIN);
	DDX_Text(pDX, IDC_EDIT_SO_PIN, m_strSoPIN);
	DDX_Text(pDX, IDC_EDIT_USER_PIN, m_strUserPIN);
	DDX_Text(pDX, IDC_EDIT_TOKEN_NAME, m_strTokenName);
	DDX_Text(pDX, IDC_STATIC_TOKEN_NAME, m_strCurrentTokenName);
	DDX_Text(pDX, IDC_EDIT_OLD_USER_PIN, m_strOldUserPIn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInitTokenDlg, CDialog)
	//{{AFX_MSG_MAP(CInitTokenDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_SO_PIN, OnChangeEditSoPin)
	ON_EN_CHANGE(IDC_EDIT_TOKEN_NAME, OnChangeEditTokenName)
	ON_EN_CHANGE(IDC_EDIT_USER_PIN, OnChangeEditUserPin)
	ON_EN_CHANGE(IDC_EDIT_CONF_USER_PIN, OnChangeEditConfUserPin)
	ON_EN_CHANGE(IDC_EDIT_OLD_USER_PIN, OnChangeEditOldUserPin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitTokenDlg message handlers

BOOL CInitTokenDlg::OnInitDialog()
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

	if (!ConnectKey())
	{
		//CDialog::OnCancel();
		//return TRUE;
	}
	DisplayTokenInfo();
	
	m_ctrlSoPin.SetLimitText(m_ulMaxPin);
	m_ctrlUserPin.SetLimitText(m_ulMaxPin);
	m_ctrlConfUserPin.SetLimitText(m_ulMaxPin);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInitTokenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInitTokenDlg::OnPaint() 
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
HCURSOR CInitTokenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool CInitTokenDlg::ConnectKey()
{
	CK_RV rv;
	CK_ULONG ulCount = 0;
	rv = C_GetSlotList(TRUE, NULL_PTR, &ulCount);
	if(CKR_OK != rv )
	{
		AfxMessageBox("Can't Acquire information of Token.", MB_OK | MB_ICONERROR);
		return false;
	}
	if(0 >= ulCount)
	{
		AfxMessageBox("Can't connect to Token ,Make sure you have inserted Token.", MB_OK | MB_ICONERROR);
		return false;
	}
	
	m_pSlotList = (CK_SLOT_ID_PTR)new CK_SLOT_ID[ulCount];
	if (! m_pSlotList) 
	{
		AfxMessageBox("Can't allocate enough memory!", MB_OK | MB_ICONERROR);
		return false;
	}
	
	rv = C_GetSlotList(TRUE, m_pSlotList, &ulCount);
	if(CKR_OK != rv )
	{
		AfxMessageBox("Can't Acquire information of Token.", MB_OK | MB_ICONERROR);
		return false;
	}
	if(0 >= ulCount)
	{
		AfxMessageBox("Can't connect to Token,Make sure you have inserted Token.", MB_OK | MB_ICONERROR);
		return false;
	}
	m_ulSlotId = m_pSlotList[0];
	return true;
}

void CInitTokenDlg::OnChangeEditSoPin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeEditConfUserPin();
}

void CInitTokenDlg::OnChangeEditTokenName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeEditConfUserPin();
}

void CInitTokenDlg::OnChangeEditUserPin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeEditConfUserPin();
}

void CInitTokenDlg::OnChangeEditOldUserPin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here	
	OnChangeEditConfUserPin();
}

void CInitTokenDlg::OnChangeEditConfUserPin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	//get UTF8 length
	int iTokenName_utf8_length = 0;
	if(m_strTokenName.GetLength() > 0)
	{
		iTokenName_utf8_length = AppStringToUtf8String((LPCTSTR)m_strTokenName,m_strTokenName.GetLength(), NULL);
	}
	int iSoPIN_utf8_length = 0;
	if(m_strSoPIN.GetLength() > 0)
	{
		iSoPIN_utf8_length = AppStringToUtf8String((LPCTSTR)m_strSoPIN,m_strSoPIN.GetLength(), NULL);
	}
	int iOldUserPIN_utf8_length = 0;
	if(m_strOldUserPIn.GetLength() > 0)
	{
		iOldUserPIN_utf8_length = AppStringToUtf8String((LPCTSTR)m_strOldUserPIn,m_strOldUserPIn.GetLength(), NULL);
	}
	int iUserPIN_utf8_length = 0;
	if(m_strUserPIN.GetLength() > 0)
	{
		iUserPIN_utf8_length = AppStringToUtf8String((LPCTSTR)m_strUserPIN,m_strUserPIN.GetLength(), NULL);
	}
	
	if(iSoPIN_utf8_length >= (LONG)m_ulMinPin
		&& iTokenName_utf8_length > 0
		&& iTokenName_utf8_length < 33
		&& (0 != lstrcmp((m_strTokenName.Right(1)).GetBuffer(0)," "))
		&& iUserPIN_utf8_length >= (LONG)m_ulMinPin
		&& iOldUserPIN_utf8_length >= (LONG)m_ulMinPin
		&& (m_strUserPIN == m_strConfUserPIN)
		)
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	else
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	
	UpdateData(FALSE);	
}

void CInitTokenDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	CK_RV rv;
	CK_SESSION_HANDLE hSession = NULL_PTR;
	rv = C_OpenSession(m_ulSlotId, 
					   CKF_RW_SESSION | CKF_SERIAL_SESSION,
					   &m_pApplication, NULL_PTR, &hSession);
	if(CKR_OK != rv)
	{
		C_Logout(hSession);
		C_CloseSession(hSession);
		ViewErrorMsg(rv);
		return;
	}
	rv = RunC_Login(hSession, CKU_USER, (CK_BYTE_PTR)(LPCSTR)m_strOldUserPIn, m_strOldUserPIn.GetLength());
	if(CKR_OK != rv)
	{
		C_Logout(hSession);
		C_CloseSession(hSession);
		ViewErrorMsg(rv);
		return;
	}
	C_CloseAllSessions(m_ulSlotId);
	rv = RunC_InitToken(m_ulSlotId,
		(CK_BYTE_PTR)(LPCSTR)m_strSoPIN,
		m_strSoPIN.GetLength(),
		(CK_BYTE_PTR)(LPCSTR)m_strTokenName
		);
	if(CKR_OK != rv)
	{
		C_Logout(hSession);
		C_CloseSession(hSession);
		ViewErrorMsg(rv);
		return;
	}
	rv = C_OpenSession(m_ulSlotId, 
					   CKF_RW_SESSION | CKF_SERIAL_SESSION,
					   &m_pApplication, NULL_PTR, &hSession);
	if(CKR_OK != rv)
	{
		C_Logout(hSession);
		C_CloseSession(hSession);
		ViewErrorMsg(rv);
		return;
	}
	rv = RunC_Login(hSession, CKU_SO, (CK_BYTE_PTR)(LPCSTR)m_strSoPIN, m_strSoPIN.GetLength());
	if(CKR_OK != rv)
	{
		C_Logout(hSession);
		C_CloseSession(hSession);
		ViewErrorMsg(rv);
		return;
	}
	rv = RunC_InitPIN(hSession,(CK_BYTE_PTR)(LPCSTR)m_strUserPIN, m_strUserPIN.GetLength());
	if(CKR_OK != rv)
	{
		C_Logout(hSession);
		C_CloseSession(hSession);
		ViewErrorMsg(rv);
		return;
	}
	C_Logout(hSession);
	C_CloseSession(hSession);
	AfxMessageBox("Initialize token successfully.", MB_OK);
	DisplayTokenInfo();
	ChangeEditState();
	//CDialog::OnOK();
}

void CInitTokenDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CInitTokenDlg::ViewErrorMsg(CK_RV rv)
{
	std::string	strMsg = "Initialize token failed!";
	char szTmp[20] = {0};
	sprintf(szTmp, " [0x%08X]", rv);
	strMsg += szTmp;
	AfxMessageBox(strMsg.c_str(), MB_OK | MB_ICONERROR);
	ChangeEditState();
}

void CInitTokenDlg::ChangeEditState()
{
	UpdateData(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
	m_ctrlUserPin.SetWindowText("");
	m_ctrlSoPin.SetWindowText("");
	m_ctrlConfUserPin.SetWindowText("");
	m_ctrlOleUserPin.SetWindowText("");
	UpdateData(FALSE);
}

void CInitTokenDlg::ReadTokenInfo()
{
	CK_RV rv = CKR_OK;
	CK_TOKEN_INFO ti =
	{
		0
	};
	rv = C_GetTokenInfo(m_ulSlotId, &ti);
	if (CKR_OK == rv)
	{
		char szTokenName[33] =
		{
			0
		};
		memcpy(szTokenName, ti.label, 32);
		UTF8BytesToANSI(szTokenName, 32);
		m_strTokenName = szTokenName;
		m_strCurrentTokenName = szTokenName;
		m_ulMaxPin = ti.ulMaxPinLen;
		m_ulMinPin = ti.ulMinPinLen;
	}
	else
	{
		;
	}	
}

void CInitTokenDlg::DisplayTokenInfo()
{
	UpdateData(TRUE);
	ReadTokenInfo();
	UpdateData(FALSE);
	std::string	strInfo = "New User PIN(%d to %d characters):";
	CString	strMsg = "";
	strMsg.Format(strInfo.c_str(), m_ulMinPin, m_ulMaxPin);
	GetDlgItem(IDC_STATIC_INIT_TOKEN_USER_PIN)->SetWindowText((LPCSTR)strMsg);
}
