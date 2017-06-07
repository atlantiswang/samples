// ImportPfxCertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImportPfxCert.h"
#include "ImportPfxCertDlg.h"
#include <WinCrypt.h>
#include <csp/csp_ext.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define CSP_NAME "EnterSafe ePass2003 CSP v1.0"

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
// CImportPfxCertDlg dialog

CImportPfxCertDlg::CImportPfxCertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportPfxCertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportPfxCertDlg)
	m_strPfxName = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CImportPfxCertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportPfxCertDlg)
	DDX_Text(pDX, IDC_EDIT_PFX_PATH, m_strPfxName);
	DDX_Text(pDX, IDC_EDIT_PFX_PWD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportPfxCertDlg, CDialog)
	//{{AFX_MSG_MAP(CImportPfxCertDlg)
	ON_BN_CLICKED(IDC_BTN_SELECT_PFX, OnBtnSelectPfx)
	ON_BN_CLICKED(IDOK, OnImportPfx)
	ON_BN_CLICKED(ID_RESET, OnReset)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportPfxCertDlg message handlers

void CImportPfxCertDlg::OnBtnSelectPfx() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_EXPLORER, "pfx/p12 Files(*.pfx;*.p12)|*.pfx;*.p12|All Files(*.*)|*.*||", this);
	if (IDOK == dlg.DoModal())
		m_strPfxName = dlg.GetPathName();
	else
		return;

	m_strPassword.Empty();
	UpdateData(FALSE);
}

void CImportPfxCertDlg::OnImportPfx() 
{
	if (!UpdateData(TRUE))
		return;

	if (m_strPfxName.IsEmpty())
	{
		MessageBox(_T("Invalid file path."), _T("ERROR"), MB_OK|MB_ICONERROR);
		return;
	}
	BYTE ucPrvBlob[2048] = {0};
	DWORD dwPrvKeyLen = 2048;
	CRYPT_DATA_BLOB pfxblob = {0};
	PCCERT_CONTEXT pCertContext = NULL;
	HCRYPTPROV hProv = NULL, hMyCSPProv = NULL;
	DWORD dwKeySpec = 0;
	HCRYPTKEY hKey = NULL, hImportKey = NULL;
	HCERTSTORE hCertSotre = NULL;
	WCHAR wpassword[MAX_PATH] = {0};
	BYTE* pbPfxBody = NULL;
	GUID guid = {0};
	_TUCHAR *pszCtnName = NULL;

	//check pfx
	HANDLE hPfxFile = CreateFile(m_strPfxName, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hPfxFile) 
	{
		MessageBox(_T("Invalid certificate file"), _T("ERROR"), MB_OK|MB_ICONERROR);
		return;
	}

	if (S_OK == CoCreateGuid(&guid))
		UuidToString(&guid, &pszCtnName);
	
	HANDLE hMap = CreateFileMapping(hPfxFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (NULL == hMap) 
	{
		MessageBox(_T("Invalid certificate file"), _T("ERROR"), MB_OK|MB_ICONERROR);
		goto CLEAN_UP;
	}
	
	pbPfxBody = (BYTE*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if (NULL == pbPfxBody) 
	{
		MessageBox(_T("Invalid certificate file"), _T("ERROR"), MB_OK|MB_ICONERROR);
		goto CLEAN_UP;
	}

	pfxblob.cbData = GetFileSize(hPfxFile, 0);
	pfxblob.pbData = pbPfxBody;

	if (!PFXIsPFXBlob(&pfxblob))
	{
		MessageBox(_T("Invalid certificate file"), _T("ERROR"), MB_OK|MB_ICONERROR);
		goto CLEAN_UP;
	}

	MultiByteToWideChar(CP_ACP, 0, LPCTSTR(m_strPassword), -1, wpassword, MAX_PATH);

	//if pfx's password is "", you must input NULL, not ""
	if (!PFXVerifyPassword(&pfxblob, (0 == m_strPassword.GetLength()) ? NULL : wpassword, 0))
	{
		MessageBox(_T("Invalid certificate's password"), _T("ERROR"), MB_OK|MB_ICONERROR);
		goto CLEAN_UP;
	}
	if (NULL == (hCertSotre = PFXImportCertStore(&pfxblob, (0 == m_strPassword.GetLength()) ? NULL : wpassword, CRYPT_EXPORTABLE | CRYPT_MACHINE_KEYSET)))
	{
		MessageBox(_T("Can Not open this certificate"), _T("ERROR"), MB_OK|MB_ICONERROR);
		goto CLEAN_UP;
	}

	// while certificates exist in the pfxStore store.... 
	while (NULL != (pCertContext = CertEnumCertificatesInStore(hCertSotre, pCertContext)))
	{
		if (!CryptAcquireCertificatePrivateKey(pCertContext, CRYPT_ACQUIRE_SILENT_FLAG|CRYPT_ACQUIRE_CACHE_FLAG,
			NULL, &hProv, &dwKeySpec, NULL)) // do not release this hProv
			continue;

		if (!CryptGetUserKey(hProv, dwKeySpec, &hKey))
		{
			MessageBox(_T("Can Not enum user key"), _T("ERROR"), MB_OK|MB_ICONERROR);
			goto CLEAN_UP;
		}

		if (!CryptExportKey(hKey, NULL, PRIVATEKEYBLOB, 0, ucPrvBlob, &dwPrvKeyLen))
		{
			MessageBox(_T("Can Not export user key"), _T("ERROR"), MB_OK|MB_ICONERROR);
			goto CLEAN_UP;
		}
		//////////////////////////////////////////////////////////////////////////
		if (!CryptAcquireContext(&hMyCSPProv, "12345678"/*(NULL==pszCtnName?_T("container"):(TCHAR*)pszCtnName)*/, CSP_NAME, PROV_RSA_FULL, CRYPT_NEWKEYSET))
		{
			MessageBox(_T("Can Not open csp handle"), _T("ERROR"), MB_OK|MB_ICONERROR);
			goto CLEAN_UP;
		}
		if (!CryptImportKey(hMyCSPProv, ucPrvBlob, dwPrvKeyLen, NULL, 0, &hKey))
		{
			MessageBox(_T("Can Not import rsa private key"), _T("ERROR"), MB_OK|MB_ICONERROR);
			goto CLEAN_UP;
		}

		if (!CryptSetKeyParam(hKey, KP_CERTIFICATE, pCertContext->pbCertEncoded, 0))
		{
			MessageBox(_T("Can Not import certificate"), _T("ERROR"), MB_OK|MB_ICONERROR);
			goto CLEAN_UP;
		}
		
		CryptReleaseContext(hMyCSPProv, NULL);
		//////////////////////////////////////////////////////////////////////////

		MessageBox(_T("The certificate has been imported to your USBKey."), _T("Congratulations"), MB_OK|MB_ICONINFORMATION);
		break;
	}

CLEAN_UP:
	if (NULL != pszCtnName)
		RpcStringFree(&pszCtnName);
	if (NULL != pbPfxBody)
		UnmapViewOfFile(pbPfxBody);
	if (NULL != hMap)
		CloseHandle(hMap);
	if (INVALID_HANDLE_VALUE != hPfxFile)
		CloseHandle(hPfxFile);
}

void CImportPfxCertDlg::OnReset() 
{
	m_strPassword.Empty();
	m_strPfxName.Empty();
	UpdateData(FALSE);
}

void CImportPfxCertDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	GetDlgItem(IDC_EDIT_PFX_PATH)->SetFocus();
	OnReset();
}

BOOL CImportPfxCertDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
