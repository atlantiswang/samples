// ECCdemoMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ECCdemoMFC.h"
#include "ECCdemoMFCDlg.h"
#include "PINDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CK_BBOOL bTrue = TRUE;

CK_OBJECT_CLASS pubClass = CKO_PUBLIC_KEY;
CK_OBJECT_CLASS priClass = CKO_PRIVATE_KEY;
CK_ULONG keyTypeECC = CKK_EC;

CK_BYTE subject[] = "Sample Key Pair";
CK_BYTE objID[]={0x01};
//DER encoded OID for name curve P-256 {1 2 840 10045 4 1 3 1 7}
CK_BYTE curve[] ={0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07};

CK_MECHANISM g_ckMechanism={CKM_ECDSA_SHA1,NULL_PTR,0};

CK_BYTE message[] = "We build security.";

#ifdef GEN_SOFT_EC
static bool GenKeySoft(std::vector<BYTE>& pub,std::vector<BYTE>&prv)
{
	EC_GROUP* group=0;
	EC_KEY *key=0;
	EC_POINT *pubkey =0;
	BN_CTX *ctx=0;					
	BIGNUM	*x=0,*y=0,*prikey =0;

	BIGNUM *kinv,*rp;
	
	bool ret = false;
	do
	{
		if((group = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1))==NULL)
			break;
		
		if((key = EC_KEY_new())==NULL)
			break;
		
		if(!EC_KEY_set_group(key,group))
			break;
		
		if(!EC_KEY_generate_key(key))
			break;
		
		if((pubkey = const_cast<EC_POINT *>(EC_KEY_get0_public_key(key)))==NULL)
			break;
		
		if((ctx=BN_CTX_new())==NULL)
			break;
		
		if((x = BN_new())==NULL || (y=BN_new())==NULL ||(prikey = BN_new())==NULL) 
			break;
		
		if(!EC_POINT_get_affine_coordinates_GFp(group,pubkey,x,y,ctx))
			break;
		
		if((prikey = const_cast<BIGNUM *>(EC_KEY_get0_private_key(key)))==NULL)
			break;
		
		pub.clear();
		pub.push_back(0x04);
		pub.push_back(0x41);
		pub.push_back(0x04);
		BYTE bin[32];
		DWORD size=BN_bn2bin(x,&bin[0]);
		if(size>32)
			break;
		pub.insert(pub.end(),32-size,0);
		pub.insert(pub.end(),&bin[0],&bin[size]);
		
		size=BN_bn2bin(y,&bin[0]);
		if(size>32)
			break;
		pub.insert(pub.end(),32-size,0);
		pub.insert(pub.end(),&bin[0],&bin[size]);
		
		prv.clear();
		size=BN_bn2bin(prikey,&bin[0]);
		if(size>32)
			break;
		prv.insert(prv.end(),32-size,0);
		prv.insert(prv.end(),&bin[0],&bin[size]);

		ret = true;
	}while(0);
	
	if(kinv) BN_free(kinv);
	if(rp) BN_free(rp);

	if(prikey) BN_free(prikey);
	if(y) BN_free(y);
	if(x) BN_free(x);
	if(pubkey) EC_POINT_free(pubkey);
	if(ctx) BN_CTX_free(ctx);
	if(group) EC_GROUP_free(group);
	
	return ret;
}

#endif

/////////////////////////////////////////////////////////////////////////////
// CECCdemoMFCDlg dialog

CECCdemoMFCDlg::CECCdemoMFCDlg(CWnd* pParent /*=NULL*/)
	:CDialog(CECCdemoMFCDlg::IDD, pParent)
	,m_session(0)
	,m_pubKey(0)
	,m_prvKey(0)
{
	//{{AFX_DATA_INIT(CECCdemoMFCDlg)
	m_log = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CECCdemoMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CECCdemoMFCDlg)
	DDX_Text(pDX, IDC_EDIT_LOG, m_log);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CECCdemoMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CECCdemoMFCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, OnButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, OnButtonVerify)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECCdemoMFCDlg message handlers

BOOL CECCdemoMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	GetDlgItem(IDC_BUTTON_GENERATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SIGN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_VERIFY)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CECCdemoMFCDlg::OnCancel() 
{
 	if(m_pubKey) C_DestroyObject(m_session, m_pubKey);
 	if(m_prvKey) C_DestroyObject(m_session, m_prvKey);
	if(m_session) C_CloseSession(m_session);
	
	CDialog::OnCancel();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CECCdemoMFCDlg::OnPaint() 
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


void CECCdemoMFCDlg::AppendLog(CString const & log)
{
	m_log+=log;
	UpdateData(FALSE);

	CEdit* ctrllog = (CEdit*)GetDlgItem(IDC_EDIT_LOG);
	if(!ctrllog)
		return;

	int nLastLine = ctrllog->GetLineCount();// GetFirstVisibleLine();

	if (nLastLine > 0)
	{
		ctrllog->LineScroll(nLastLine, 0);
	}
}

void CECCdemoMFCDlg::AppendInfo(CString const & log)
{
	AppendLog(log+_T("\r\n"));
}

void CECCdemoMFCDlg::AppendError(CString const & desc,CK_RV error)
{
	AppendLog(desc);
	CString tmp;
	tmp.Format(_T("[0x%08x]\r\n"),error);
	AppendLog(tmp);
}



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CECCdemoMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





void CECCdemoMFCDlg::OnButtonClear() 
{
	m_log=_T("");
	UpdateData(FALSE);
}


void CECCdemoMFCDlg::OnButtonConnect() 
{
	AppendInfo(_T(">>>>>>>>>>>>>>>>>OnConnect"));
	
	CK_RV rv;
	if(!m_session)
	{
		CK_SLOT_ID slots[100]={0};
		CK_ULONG ulCount = sizeof(slots)/sizeof(slots[0]);

		rv = C_GetSlotList(TRUE, slots, &ulCount);
		if(CKR_OK != rv || 0 >= ulCount)
		{
			AppendError(_T("C_GetSlotList failed."), rv);
			return;
		}
		
		rv = C_OpenSession(slots[0],CKF_RW_SESSION|CKF_SERIAL_SESSION,NULL_PTR,NULL_PTR,&m_session);
		if(CKR_OK != rv )
		{
			AppendError(_T("C_OpenSession failed."), rv);
		}
		else
		{
			AppendInfo(_T("Connect to token Successfully !"));
		}
	}

	CPINDlg dlg;
	if(dlg.DoModal()!=IDOK)
		return;

	rv = C_Login(m_session, CKU_USER, (CK_UTF8CHAR_PTR)(LPCTSTR)dlg.m_PIN, dlg.m_PIN.GetLength());
	if(CKR_OK != rv)
	{
		AppendError(_T("Login failed"),rv);
		return;
	}

	AppendInfo(_T("Login OK!"));

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GENERATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(TRUE);
}

void CECCdemoMFCDlg::OnButtonGenerate() 
{
	AppendInfo(_T(">>>>>>>>>>>>>>>>>OnGenerate"));
	CK_ATTRIBUTE pubTemplateECC[] = { 
		{CKA_CLASS,			&pubClass,		sizeof(pubClass)},
		{CKA_KEY_TYPE,		&keyTypeECC,	sizeof(keyTypeECC)},
		{CKA_ID,			objID,			sizeof(objID)},
		{CKA_SUBJECT,		subject,		sizeof(subject)},
		{CKA_TOKEN,			&bTrue,			sizeof(bTrue)},
		{CKA_EC_PARAMS,		curve,			sizeof(curve)}
	};


	CK_ATTRIBUTE prvTemplateECC[] = {
		{CKA_CLASS,			&priClass,	sizeof(priClass)},
		{CKA_KEY_TYPE,		&keyTypeECC,sizeof(keyTypeECC)},
		{CKA_ID,			objID,		sizeof(objID)},
		{CKA_SUBJECT,		subject,	sizeof(subject)},
		{CKA_PRIVATE,		&bTrue,		sizeof(bTrue)},
		{CKA_SENSITIVE,		&bTrue,		sizeof(bTrue)},
		{CKA_TOKEN,			&bTrue,		sizeof(bTrue)},
		{CKA_EC_PARAMS,		curve,		sizeof(curve)}
	};
	CK_MECHANISM keyGenMechanism = {CKM_EC_KEY_PAIR_GEN,NULL_PTR,0};

	CK_RV rv = C_GenerateKeyPair(	m_session, &keyGenMechanism,
									pubTemplateECC, sizeof(pubTemplateECC)/sizeof(pubTemplateECC[0]),
									prvTemplateECC, sizeof(prvTemplateECC)/sizeof(prvTemplateECC[0]),
									&m_pubKey, &m_prvKey);
	if(CKR_OK != rv)
	{
		AppendError(_T("Failed to generate ECC key pair"),rv);
	}
	else
	{
		AppendInfo(_T("GenerateKeyPair OK!"));
		
		GetDlgItem(IDC_BUTTON_GENERATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SIGN)->EnableWindow(TRUE);
	}
}

void CECCdemoMFCDlg::OnButtonCreate() 
{
	CK_RV rv = CKR_OK;

	BYTE pub_value[]=
	{
		0xEF,0x15,0x1E,0x77,0xA7,0x85,0x6F,0x83,
		0x74,0x1E,0x05,0x8C,0x9B,0xED,0x62,0xE9,
		0x68,0x3B,0xD7,0xC8,0xEF,0xD2,0x41,0xA1,
		0x76,0xBE,0xE7,0xC0,0xA9,0x67,0x13,0x45,
		0xBE,0xF9,0x8D,0x31,0xA7,0x2D,0x9D,0x39,
		0x63,0xEB,0x4B,0x40,0x42,0xC7,0x1E,0x1F,
		0xB2,0x21,0x61,0xCE,0x7A,0xFE,0x37,0xCF,
		0x58,0x01,0x66,0xD8,0xBA,0x45,0x52,0x61
	};
	
	BYTE prv_value[]=
	{
		0x6A,0x17,0xD1,0xF2,0xE1,0x2C,0x42,0x47,
		0xF8,0xBC,0x76,0xE5,0x63,0xA4,0x40,0xF2,
		0x77,0x03,0x7D,0x81,0x2D,0xEB,0x33,0xA0,
		0xF4,0xA1,0x39,0x45,0xD8,0x98,0xC2,0x96			
	};

	CK_ATTRIBUTE pubTemplateECC[] = 
	{ 
		{CKA_CLASS,			&pubClass,		sizeof(pubClass)},
		{CKA_KEY_TYPE,		&keyTypeECC,	sizeof(keyTypeECC)},
		{CKA_ID,			objID,			sizeof(objID)},
		{CKA_SUBJECT,		subject,		sizeof(subject)},
		{CKA_TOKEN,			&bTrue,			sizeof(bTrue)},
		{CKA_EC_PARAMS,		curve,			sizeof(curve)},
		{CKA_EC_POINT,		pub_value,		sizeof(pub_value)},
	};
	if((rv=C_CreateObject(m_session,pubTemplateECC,sizeof(pubTemplateECC)/sizeof(pubTemplateECC[0]),&m_pubKey))!=CKR_OK)
	{
		AppendError(_T("Failed to create public key."),rv);
		m_pubKey=0;
 		m_prvKey=0;
		return;
	}
	AppendInfo(_T("Create public key OK."));

	CK_ATTRIBUTE prvTemplateECC[] = 
	{
		{CKA_CLASS,			&priClass,	sizeof(priClass)},
		{CKA_KEY_TYPE,		&keyTypeECC,sizeof(keyTypeECC)},
		{CKA_ID,			objID,		sizeof(objID)},
		{CKA_SUBJECT,		subject,	sizeof(subject)},
		{CKA_PRIVATE,		&bTrue,		sizeof(bTrue)},
		{CKA_SENSITIVE,		&bTrue,		sizeof(bTrue)},
		{CKA_TOKEN,			&bTrue,		sizeof(bTrue)},
		{CKA_EC_PARAMS,		curve,		sizeof(curve)},
		{CKA_VALUE,			prv_value,	sizeof(prv_value)},	
	};
	
	if((rv=C_CreateObject(m_session,prvTemplateECC,sizeof(prvTemplateECC)/sizeof(prvTemplateECC[0]),&m_prvKey))!=CKR_OK)
	{
		AppendError(_T("Failed to create private key."),rv);
		
		if(m_pubKey)
			C_DestroyObject(m_session, m_pubKey);

		m_pubKey=0;
 		m_prvKey=0;
		return;
	}
	AppendInfo(_T("Create private key OK."));

	GetDlgItem(IDC_BUTTON_GENERATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SIGN)->EnableWindow(TRUE);
}

void CECCdemoMFCDlg::OnButtonSign() 
{
	AppendInfo(_T(">>>>>>>>>>>>>>>>>OnSign"));

	CK_RV rv = C_SignInit(m_session, &g_ckMechanism, m_prvKey);
	if(CKR_OK != rv)
	{
		AppendError(_T("Failed to sign."),rv);
		return;
	}

	m_signature_len = sizeof(m_signature);
	rv = C_Sign(m_session,message,sizeof(message),m_signature,&m_signature_len);
	if(CKR_OK != rv)
	{
		AppendError(_T("Failed to sign."),rv);
	}
	else
	{
		AppendError(_T("Data is signed successfully!"),rv);
		GetDlgItem(IDC_BUTTON_VERIFY)->EnableWindow(TRUE);
	}
}

void CECCdemoMFCDlg::OnButtonVerify() 
{
	AppendInfo(_T(">>>>>>>>>>>>>>>>>OnVerify"));

	CK_RV rv = C_VerifyInit(m_session, &g_ckMechanism, m_pubKey);
	if(CKR_OK != rv)
	{
		AppendError(_T("Failed to Verify."),rv);
		return;
	}

	rv = C_Verify(m_session,message,sizeof(message),m_signature,m_signature_len);
	if(CKR_OK != rv)
		AppendError(_T("Failed to Verify."),rv);
	else
		AppendInfo(_T("Verify OK!"));	
}
