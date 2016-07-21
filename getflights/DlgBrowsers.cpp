// DlgBrowsers.cpp : 实现文件
//

#include "stdafx.h"
#include "GetFlights.h"
#include "DlgBrowsers.h"
#include "afxdialogex.h"
#include "GetFlightsDlg.h"
#include "C9CHtmlParse.h"
#include "DbCenter.h"


// CDlgBrowsers 对话框

IMPLEMENT_DYNAMIC(CDlgBrowsers, CDialogEx)

CDlgBrowsers::CDlgBrowsers(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBrowsers::IDD, pParent)
{
	m_nlOldProgress1 = 0;
	m_nlOldProgress2 = 0;
	m_nlOldProgress3 = 0;
	m_nlOldProgress4 = 0;
	m_nlOldProgress5 = 0;
	m_nlOldProgress6 = 0;
}

CDlgBrowsers::~CDlgBrowsers()
{
}

void CDlgBrowsers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_browser1);
	DDX_Control(pDX, IDC_EXPLORER2, m_browser2);
	DDX_Control(pDX, IDC_EXPLORER3, m_browser3);
	DDX_Control(pDX, IDC_EXPLORER4, m_browser4);
	DDX_Control(pDX, IDC_EXPLORER5, m_browser5);
	DDX_Control(pDX, IDC_EXPLORER6, m_browser6);
}


BEGIN_MESSAGE_MAP(CDlgBrowsers, CDialogEx)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CDlgBrowsers, CDialogEx)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER1, 259, CDlgBrowsers::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER2, 259, CDlgBrowsers::DocumentCompleteExplorer2, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER3, 259, CDlgBrowsers::DocumentCompleteExplorer3, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER4, 259, CDlgBrowsers::DocumentCompleteExplorer4, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER5, 259, CDlgBrowsers::DocumentCompleteExplorer5, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER6, 259, CDlgBrowsers::DocumentCompleteExplorer6, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER1, 108, CDlgBrowsers::ProgressChangeExplorer1, VTS_I4 VTS_I4)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER2, 108, CDlgBrowsers::ProgressChangeExplorer2, VTS_I4 VTS_I4)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER3, 108, CDlgBrowsers::ProgressChangeExplorer3, VTS_I4 VTS_I4)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER4, 108, CDlgBrowsers::ProgressChangeExplorer4, VTS_I4 VTS_I4)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER5, 108, CDlgBrowsers::ProgressChangeExplorer5, VTS_I4 VTS_I4)
	ON_EVENT(CDlgBrowsers, IDC_EXPLORER6, 108, CDlgBrowsers::ProgressChangeExplorer6, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CDlgBrowsers 消息处理程序


BOOL CDlgBrowsers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_browser1.m_bInuse = false;
	m_browser2.m_bInuse = false;
	m_browser3.m_bInuse = false;
	m_browser4.m_bInuse = false;
	m_browser5.m_bInuse = false;
	m_browser6.m_bInuse = false;

	m_bStoped = true;

	SetTimer(2100,500,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgBrowsers::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::DestroyWindow();
}



void CDlgBrowsers::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	LayoutCtrls();
}


void CDlgBrowsers::LayoutCtrls(void)
{
	CRect rc;
	GetClientRect(&rc);
	int cx = rc.Width();
	int cy = rc.Height();

	int nSep = 10;

	int nCellwidth = (cx - nSep*4)/3;
	int nCellheight = (cy - nSep*3)/2;

	if (m_browser1.GetSafeHwnd())
	{
		m_browser1.SetWindowPos(&wndTop,nSep,nSep,nCellwidth,nCellheight,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
	if (m_browser2.GetSafeHwnd())
	{
		m_browser2.SetWindowPos(&wndTop,nSep*2 + nCellwidth,nSep,nCellwidth,nCellheight,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
	if (m_browser3.GetSafeHwnd())
	{
		m_browser3.SetWindowPos(&wndTop,nSep*3 + nCellwidth*2,nSep,nCellwidth,nCellheight,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
	if (m_browser4.GetSafeHwnd())
	{
		m_browser4.SetWindowPos(&wndTop,nSep,nSep*2 + nCellheight,nCellwidth,nCellheight,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
	if (m_browser5.GetSafeHwnd())
	{
		m_browser5.SetWindowPos(&wndTop,nSep*2 + nCellwidth,nSep*2 + nCellheight,nCellwidth,nCellheight,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
	if (m_browser6.GetSafeHwnd())
	{
		m_browser6.SetWindowPos(&wndTop,nSep*3 + nCellwidth*2,nSep*2 + nCellheight,nCellwidth,nCellheight,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
}

void CDlgBrowsers::ParseDocument(CExplorer1& browser)
{
	IHTMLDocument2 *lpHtmlDocument = browser.GetDocument();

	if (NULL == lpHtmlDocument)
	{
		return;
	}

	IHTMLElement *lpBodyElm;
	IHTMLElement *lpParentElm;

	lpHtmlDocument->get_body(&lpBodyElm);
	ASSERT(lpBodyElm);
	lpHtmlDocument->Release();

//	lpBodyElm->get_parentElement(&lpParentElm);
//	ASSERT(lpParentElm);
	BSTR    bstr;
	lpBodyElm->get_outerHTML(&bstr);
	//lpParentElm->get_innerHTML(&bstr);
	CString str = bstr;

	if (str.GetLength() > 0x30)
	{
		std::string html(CStrT2CStrA(str).GetBuffer(0));
		list<PT9CFlightInfo> flightsList;
		C9CHtmlParse parse;
		parse.ParseHtmlFlights(html,flightsList);

		list<PT9CFlightInfo>::iterator it;
		for (it = flightsList.begin(); it != flightsList.end(); it++)
		{
			PT9CFlightInfo pInfo = *it;
			if (CDbCenter::GetInstance()->IsHaveFlights(pInfo->straCompany,pInfo->straFromCityCode,pInfo->straToCityCode,pInfo->straFromDate,pInfo->straFlightNo))
			{
				CDbCenter::GetInstance()->UpdateFlightInfo(pInfo);
			}
			else
			{
				CDbCenter::GetInstance()->InsertFligthInfo(pInfo);
			}
			CStringA straLog;
			straLog.Format("%s-%s(%s:%s):%d|%d|%d",
				pInfo->straFromCityCode,pInfo->straToCityCode,
				pInfo->straFromDate,pInfo->straFlightNo,
				pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			((CGetFlightsDlg*)AfxGetMainWnd())->AddLog(CStrA2CStrT(straLog));

			delete pInfo;
		}
		flightsList.clear();
	}


//	lpParentElm->Release();
	lpBodyElm->Release();

	
}

void CDlgBrowsers::ParseDocument(LPDISPATCH pDisp)
{
	IHTMLDocument2 *lpHtmlDocument = NULL;
	
	if (pDisp != NULL) {

		// get the actual document interface
	//	IDispatch *document_dispatch = NULL;
	//	HRESULT hr = pDisp->get_Document(&document_dispatch);

	//	if (SUCCEEDED(hr) && (document_dispatch != NULL)) 
		{

			// get the actual document interface

			/*hr = */pDisp->QueryInterface(IID_IHTMLDocument2,
				(void **)&lpHtmlDocument);

			// release dispatch interface

	//		document_dispatch->Release();

		}

	//	pDisp->QueryInterface(IID_IHTMLDocument2,
	//		(void **)&lpHtmlDocument);
	}

	if (NULL == lpHtmlDocument)
	{
		return;
	}

	IHTMLElement *lpBodyElm;
	IHTMLElement *lpParentElm;

	lpHtmlDocument->get_body(&lpBodyElm);
	ASSERT(lpBodyElm);
	lpHtmlDocument->Release();

	//	lpBodyElm->get_parentElement(&lpParentElm);
	//	ASSERT(lpParentElm);
	BSTR    bstr;
	lpBodyElm->get_outerHTML(&bstr);
	//lpParentElm->get_innerHTML(&bstr);
	CString str = bstr;

	if (str.GetLength() > 0x30)
	{
		std::string html(CStrT2CStrA(str).GetBuffer(0));
		list<PT9CFlightInfo> flightsList;
		C9CHtmlParse parse;
		parse.ParseHtmlFlights(html,flightsList);

		list<PT9CFlightInfo>::iterator it;
		for (it = flightsList.begin(); it != flightsList.end(); it++)
		{
			PT9CFlightInfo pInfo = *it;
			if (CDbCenter::GetInstance()->IsHaveFlights(pInfo->straCompany,pInfo->straFromCityCode,pInfo->straToCityCode,pInfo->straFromDate,pInfo->straFlightNo))
			{
				CDbCenter::GetInstance()->UpdateFlightInfo(pInfo);
			}
			else
			{
				CDbCenter::GetInstance()->InsertFligthInfo(pInfo);
			}
			CStringA straLog;
			straLog.Format("%s-%s(%s:%s):%d|%d|%d",
				pInfo->straFromCityCode,pInfo->straToCityCode,
				pInfo->straFromDate,pInfo->straFlightNo,
				pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			((CGetFlightsDlg*)AfxGetMainWnd())->AddLog(CStrA2CStrT(straLog));

			delete pInfo;
		}
		flightsList.clear();
	}


	//	lpParentElm->Release();
	lpBodyElm->Release();


}


bool CDlgBrowsers::GetNewFlight(PTAirLineDateSingle pInfo)
{
	if (NULL == pInfo)
	{
		return false;
	}
	m_bStoped = false;
	CString strUrl;
	strUrl.Format(_T("http://www.china-sss.com/AirFlights/SearchFlights?OriCityCode=%s&DestCityCode=%s&FlightDate=%d-%02d-%02d&FlightDateReturn=%d-%02d-%02d&IsReturn=False&MoneyType=0&AdultNum=1&ChildNum=0&InfantNum=0"),
		pInfo->_airInfo.strFromCityCode,
		pInfo->_airInfo.strToCityCode,
		pInfo->tDate.GetYear(),pInfo->tDate.GetMonth(),pInfo->tDate.GetDay(),
		pInfo->tDate.GetYear(),pInfo->tDate.GetMonth(),pInfo->tDate.GetDay());

	bool bRet = false;
	if (!m_browser1.m_bInuse)
	{
		m_browser1.m_bInuse = true;
		m_browser1.Navigate(strUrl);
		bRet = true;
	}
	else if (!m_browser2.m_bInuse)
	{
		m_browser2.m_bInuse = true;
		m_browser2.Navigate(strUrl);
		bRet = true;
	}
	else if (!m_browser3.m_bInuse)
	{
		m_browser3.m_bInuse = true;
		m_browser3.Navigate(strUrl);
		bRet = true;
	}
	else if (!m_browser4.m_bInuse)
	{
		m_browser4.m_bInuse = true;
		m_browser4.Navigate(strUrl);
		bRet = true;
	}
	else if (!m_browser5.m_bInuse)
	{
		m_browser5.m_bInuse = true;
		m_browser5.Navigate(strUrl);
		bRet = true;
	}
	else if (!m_browser6.m_bInuse)
	{
		m_browser6.m_bInuse = true;
		m_browser6.Navigate(strUrl);
		bRet = true;
	}

	if (bRet)
	{
		CString strLog;

		strLog.Format(_T("开始获取:%s-%s(%d%02d%02d)"),
			pInfo->_airInfo.strFromCityCode,pInfo->_airInfo.strToCityCode,
			pInfo->tDate.GetYear(),pInfo->tDate.GetMonth(),pInfo->tDate.GetDay());
		((CGetFlightsDlg*)AfxGetMainWnd())->AddLog(strLog);
	}

	return bRet;
}


// 取消正在获取的网页
void CDlgBrowsers::CancelAll(void)
{
	m_bStoped = true;
	m_browser1.Stop();
	m_browser2.Stop();
	m_browser3.Stop();
	m_browser4.Stop();
	m_browser5.Stop();
	m_browser6.Stop();

	//m_browser1.Clear();
	//m_browser2.Clear();
	//m_browser3.Clear();
	//m_browser4.Clear();
	//m_browser5.Clear();
	//m_browser6.Clear();

	m_browser1.m_bInuse = false;
	m_browser2.m_bInuse = false;
	m_browser3.m_bInuse = false;
	m_browser4.m_bInuse = false;
	m_browser5.m_bInuse = false;
	m_browser6.m_bInuse = false;

	m_listBrowser.clear();
}


void CDlgBrowsers::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码
	CString str,strurl;
	if ((URL       != NULL) &&
		(V_VT(URL) == VT_BSTR)) {
			strurl = CString(V_BSTR(URL));
	}

	str.Format(_T("Browser1,DocumentComplete!\r\nURL:%s\r\n"),strurl);
	OutputDebugString(str);
//	ParseDocument(m_browser1);
	if (0 == strurl.CompareNoCase(m_browser1.m_strUrl) ||
		0 == strurl.CompareNoCase(_T("http://www.china-sss.com/Home/Error")))
	{
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser1;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
}


void CDlgBrowsers::DocumentCompleteExplorer2(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码

	CString str,strurl;
	if ((URL       != NULL) &&
		(V_VT(URL) == VT_BSTR)) {
			strurl = CString(V_BSTR(URL));
	}

	str.Format(_T("Browser2,DocumentComplete!\r\nURL:%s\r\n"),strurl);
	OutputDebugString(str);

	if (0 == strurl.CompareNoCase(m_browser2.m_strUrl) ||
		0 == strurl.CompareNoCase(_T("http://www.china-sss.com/Home/Error")))
	{
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser2;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
}


void CDlgBrowsers::DocumentCompleteExplorer3(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码

	CString str,strurl;
	if ((URL       != NULL) &&
		(V_VT(URL) == VT_BSTR)) {
			strurl = CString(V_BSTR(URL));
	}

	str.Format(_T("Browser3,DocumentComplete!\r\nURL:%s\r\n"),strurl);
	OutputDebugString(str);

	if (0 == strurl.CompareNoCase(m_browser3.m_strUrl) ||
		0 == strurl.CompareNoCase(_T("http://www.china-sss.com/Home/Error")))
	{
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser3;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
}


void CDlgBrowsers::DocumentCompleteExplorer4(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码

	CString str,strurl;
	if ((URL       != NULL) &&
		(V_VT(URL) == VT_BSTR)) {
			strurl = CString(V_BSTR(URL));
	}

	str.Format(_T("Browser4,DocumentComplete!\r\nURL:%s\r\n"),strurl);
	OutputDebugString(str);

	if (0 == strurl.CompareNoCase(m_browser4.m_strUrl) ||
		0 == strurl.CompareNoCase(_T("http://www.china-sss.com/Home/Error")))
	{
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser4;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
}


void CDlgBrowsers::DocumentCompleteExplorer5(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码

	CString str,strurl;
	if ((URL       != NULL) &&
		(V_VT(URL) == VT_BSTR)) {
			strurl = CString(V_BSTR(URL));
	}

	str.Format(_T("Browser5,DocumentComplete!\r\nURL:%s\r\n"),strurl);
	OutputDebugString(str);

	if (0 == strurl.CompareNoCase(m_browser5.m_strUrl) ||
		0 == strurl.CompareNoCase(_T("http://www.china-sss.com/Home/Error")))
	{
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser5;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
}


void CDlgBrowsers::DocumentCompleteExplorer6(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码

	CString str,strurl;
	if ((URL       != NULL) &&
		(V_VT(URL) == VT_BSTR)) {
			strurl = CString(V_BSTR(URL));
	}

	str.Format(_T("Browser6,DocumentComplete!\r\nURL:%s\r\n"),strurl);
	OutputDebugString(str);

	if (0 == strurl.CompareNoCase(m_browser6.m_strUrl) ||
		0 == strurl.CompareNoCase(_T("http://www.china-sss.com/Home/Error")))
	{
		
	}
}


void CDlgBrowsers::ProgressChangeExplorer1(long Progress, long ProgressMax)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format(_T("\r\nBrowser1---Progress:%d,ProgressMax:%d\r\n"),Progress,ProgressMax);
	OutputDebugString(str);

	if (Progress == 0 && ProgressMax == 0 && m_nlOldProgress1 == -1)
	{
		ParseDocument(m_browser1);
		m_browser1.m_bInuse = false;
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser1;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
	m_nlOldProgress1 = Progress;
}

void CDlgBrowsers::ProgressChangeExplorer2(long Progress, long ProgressMax)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format(_T("\r\nBrowser2---Progress:%d,ProgressMax:%d\r\n"),Progress,ProgressMax);
	OutputDebugString(str);

	if (Progress == 0 && ProgressMax == 0 && m_nlOldProgress2 == -1)
	{
		ParseDocument(m_browser2);
		m_browser2.m_bInuse = false;
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser2;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
	m_nlOldProgress2 = Progress;
}

void CDlgBrowsers::ProgressChangeExplorer3(long Progress, long ProgressMax)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format(_T("\r\nBrowser3---Progress:%d,ProgressMax:%d\r\n"),Progress,ProgressMax);
	OutputDebugString(str);

	if (Progress == 0 && ProgressMax == 0 && m_nlOldProgress3 == -1)
	{
		ParseDocument(m_browser3);
		m_browser3.m_bInuse = false;
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser3;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
	m_nlOldProgress3 = Progress;
}

void CDlgBrowsers::ProgressChangeExplorer4(long Progress, long ProgressMax)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format(_T("\r\nBrowser4---Progress:%d,ProgressMax:%d\r\n"),Progress,ProgressMax);
	OutputDebugString(str);

	if (Progress == 0 && ProgressMax == 0 && m_nlOldProgress4 == -1)
	{
		ParseDocument(m_browser4);
		m_browser4.m_bInuse = false;
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser4;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
	m_nlOldProgress4 = Progress;
}

void CDlgBrowsers::ProgressChangeExplorer5(long Progress, long ProgressMax)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format(_T("\r\nBrowser5---Progress:%d,ProgressMax:%d\r\n"),Progress,ProgressMax);
	OutputDebugString(str);

	if (Progress == 0 && ProgressMax == 0 && m_nlOldProgress5 == -1)
	{
		ParseDocument(m_browser5);
		m_browser5.m_bInuse = false;
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser5;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
	m_nlOldProgress5 = Progress;
}

void CDlgBrowsers::ProgressChangeExplorer6(long Progress, long ProgressMax)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format(_T("\r\nBrowser6---Progress:%d,ProgressMax:%d\r\n"),Progress,ProgressMax);
	OutputDebugString(str);

	if (Progress == 0 && ProgressMax == 0 && m_nlOldProgress6 == -1)
	{
		ParseDocument(m_browser6);
		m_browser6.m_bInuse = false;
		/*PTBrowserInfo pInfo = new TBrowserInfo;
		pInfo->browser = &m_browser6;
		pInfo->dwTickCount = GetTickCount();
		m_listBrowser.push_back(pInfo);*/
	}
	m_nlOldProgress6 = Progress;
}

void CDlgBrowsers::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_listBrowser.empty() && !m_bStoped)
	{
		PTBrowserInfo pInfo = m_listBrowser.front();
		if (pInfo != NULL)
		{
			if (GetTickCount() - pInfo->dwTickCount >= 2000)
			{
				ParseDocument(*(pInfo->browser));
				m_listBrowser.pop_front();
				pInfo->browser->m_bInuse = false;
				delete pInfo;
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
