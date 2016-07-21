#pragma once
#include "explorer1.h"
#include "DataProcess.h"

// CDlgBrowsers 对话框
typedef struct tBrowserInfo
{
	CExplorer1*	browser;
	DWORD	dwTickCount;
}TBrowserInfo,*PTBrowserInfo;

class CDlgBrowsers : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBrowsers)

public:
	CDlgBrowsers(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBrowsers();

// 对话框数据
	enum { IDD = IDD_DLG_BROWSERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_browser1;
	CExplorer1 m_browser2;
	CExplorer1 m_browser3;
	CExplorer1 m_browser4;
	CExplorer1 m_browser5;
	CExplorer1 m_browser6;

	long	m_nlOldProgress1;
	long	m_nlOldProgress2;
	long	m_nlOldProgress3;
	long	m_nlOldProgress4;
	long	m_nlOldProgress5;
	long	m_nlOldProgress6;

	list<PTBrowserInfo> m_listBrowser;
	bool	m_bStoped;

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);


	void LayoutCtrls(void);
	void ParseDocument(CExplorer1& browser);
	void ParseDocument(LPDISPATCH pDisp);

	bool GetNewFlight(PTAirLineDateSingle pInfo);
	// 取消正在获取的网页
	void CancelAll(void);
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
	void DocumentCompleteExplorer2(LPDISPATCH pDisp, VARIANT* URL);
	void DocumentCompleteExplorer3(LPDISPATCH pDisp, VARIANT* URL);
	void DocumentCompleteExplorer4(LPDISPATCH pDisp, VARIANT* URL);
	void DocumentCompleteExplorer5(LPDISPATCH pDisp, VARIANT* URL);
	void DocumentCompleteExplorer6(LPDISPATCH pDisp, VARIANT* URL);
	void ProgressChangeExplorer1(long Progress, long ProgressMax);
	void ProgressChangeExplorer2(long Progress, long ProgressMax);
	void ProgressChangeExplorer3(long Progress, long ProgressMax);
	void ProgressChangeExplorer4(long Progress, long ProgressMax);
	void ProgressChangeExplorer5(long Progress, long ProgressMax);
	void ProgressChangeExplorer6(long Progress, long ProgressMax);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};
