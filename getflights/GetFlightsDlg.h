
// GetFlightsDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgConfig.h"
//#include "DlgGetFlights.h"
//#include "DlgBrowsers.h"
#include "DlgShowFlights.h"
#include "CeairMobileEConst.h"
#include <map>

#ifndef GET_KN_FLIGHT
	#ifndef GET_CA_FLIGHT
		#ifndef GET_AQ_FLIGHT
			#ifdef CEAIR_MOBILE_E
				#define ThreadCount	(1)//15
			#else
				#if (SSS_CLIENT_NUM == SSS_1_CLIENT)
					#define ThreadCount	(1)//10
				#else
					#define ThreadCount	(15)
				#endif
			#endif
		#else//#define GET_AQ_FLIGHT
			#define ThreadCount (20) //20
		#endif
	#else //#ifdef GET_CA_FLIGHT
		#define ThreadCount	(10)
	#endif
#else
	#if ( GET_FLIGHT_TYPE == 0 )
		#define ThreadCount (5)
	#elif( GET_FLIGHT_TYPE == 1 )
		#define ThreadCount (10)
	#else
		#define ThreadCount (1)//10
	#endif
#endif
//要处理的数据(一天的数据保存在一起)
typedef struct AirLineDateProcess
{
	CTime				tDate;		//日期
	CDialogEx*			pDlg;
	list<PTAirLineInfo>	listAirLine;
}TAirLineDateProcess,*PTAirLineDateProcess;

typedef struct AirLineDetailProcess
{
	CDialogEx*			pDlg;
	list<PAirLineDetailInfo>	listAirLine;
}TAirLineDetailProcess,*PTAirLineDetailProcess;

// CGetFlightsDlg 对话框
class CGetFlightsDlg : public CDialogEx
{
// 构造
public:
	CGetFlightsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETFLIGHTS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	static HWND GetDlgConfigHwnd() { return m_hDlgConfigHwnd;};

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;

	bool	m_bCloseClicked;
	bool	m_bStart;

	CDlgConfig* m_pDlgConfig;
	CDlgShowFlights*	m_pDlgShowFlights;

	std::list<PAirLineDetailInfo>	m_allLineList;

	map<UINT, PTAirLineDetailProcess> m_client1MapProcess;
	map<CString, PTAirLineDateProcess> m_mapProcess;


	virtual BOOL DestroyWindow();
	void LayoutCtrls(void);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	int Start(bool bLoop);
	int Client1Start(bool bLoop);//所有航线用1个客户端来跑
	int CaClientStart(bool bLoop);//国航客户端
	int ClientMobileEStart(bool bLoop);//东航移动E
	int KnClientStart(bool bLoop);//联航客户端

	void AddLog(CString strLog);

	void ClearAllLineList();
	// 清理map
	int ClearProcessMap(map<CString,PTAirLineDateProcess>& mapProcess);
	//线程处理函数,一个日期一个线程
	static void ThreadProcessKn( LPVOID pParam );
	static void ThreadProcess( LPVOID pParam );
	static void ThreadProcessClient1( LPVOID pParam );
	static void __ThreadAqFlightProcess( LPVOID pParam );
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Stop(void);

	//消息响应函数，处理线程已经结束
	LRESULT OnProcessThreadEnd(WPARAM wParam, LPARAM lParam);

	LRESULT OnUpdateFlight(WPARAM wParam, LPARAM lParam);
	LRESULT OnQueryLessChangeFlightOk(WPARAM wParam, LPARAM lParam);

	UINT	m_nThreadEndCount;
	MUINT	m_uThreadCount;
	afx_msg void OnClose();

	//联航6秒事件
	static HANDLE   m_h6Second;
	static HANDLE   m_h6Second2;
	//退出软件事件
	static HANDLE	m_hExitEvt;
	//继续执行事件
	static HANDLE	m_hContinueDoEvt;
	static CGetFlightsDlg*	m_pThis;
	static HWND		m_hDlgConfigHwnd;

	//添加任务到线程池
	static UINT __ThreadInsertKnJobToThreadPool(void* pParam);
	static UINT __ThreadInsertJobToThreadPool( void* pParam );
	static UINT __ThreadInsertJobToThreadPoolClient1(void * pParam );
	//等待线程池中的所有任务完成（线程池中的任务执行具有无序性，防止有些任务执行次数多而有些任务执行的次数少）
	static void __WailAllJobFinished(bool bWaitAll=true);

	void	__Reset9CFlightInfoList(list<PT9CFlightInfo> &flightList);
	PT9CFlightInfo	__Find9CFlight(list<PT9CFlightInfo> &flightList, PT9CFlightInfo pKey, BOOL *pbFind);
	void	__Merge9CFlightInfoList(list<PT9CFlightInfo> & fromFlightList, list<PT9CFlightInfo> & toFlightList);
	void	__Free9CFlightInfoList(list<PT9CFlightInfo> &flightList);
	void	__SetCurThreadCount(UINT u);
	UINT	__GetCurThreadCount(void);
	static BOOL	__IsJsonFlightDataOk(list<PT9CFlightInfo>& listFlight);
	//从春秋抓取一条航班信息
	static BOOL __GetSssFlight(BOOL bChangeProxy, CString strFromCityCode,CString strToCityCode, 
		CStringA straStartDate, CStringA straEndDate, wstring& httpResponseContent);
	//从九元抓取一条航班信息
	static BOOL __GetAqFlightFromSite(BOOL bChangeProxy, CString & strFromCityCode,CString & strToCityCode, 
		CStringA & straStartDate, wstring& httpResponseContent);
	//从春秋抓取一条航班信息
	static BOOL	__GetKnFlight(BOOL bChangeProxy, CString & strFromCityCode,CString & strToCityCode, 
		CStringA & straStartDate, wstring& httpResponseContent);
	static BOOL __GetSssFlightFromNewSite(BOOL bChangeProxy, CString & strFromCityCode,CString & strToCityCode, 
		CStringA & straStartDate, wstring& httpResponseContent);
	static std::string	__GetCityNameUrlCode(CString & strCityCode);

	static BOOL		m_bNoChangeFlightPoll;//几乎不变的航线是否已经轮询完成


private:
	map<UINT, SCaAirLineDetailProcess*> m_caMapProcess;//每个线程处理要处理的航班列表，map中的key仅为序号
	//map<int, std::list<UINT>> m_caProductFlightMap;//每个产品的包含的航班列表。一个页面上的一个航线图片为一个产品
	std::list<SCaLowPriceFlightInfo*>	m_caLowPriceAirLineList;
	void	__ReleaseCaLowPriceFlightList();
	void	__LoadCaLowPriceAirLineList();
	static BOOL	__GetCaLowPriceFlight(BOOL bChangeProxy, int iCityCode, const CString & strCity, wstring& httpResponseContent);
	//添加任务到线程池
	static UINT __ThreadInsertCaJobToThreadPool( void* pParam );
	static UINT __ThreadInsertAqJobToThreadPool( void* pParam );
	//线程处理函数,一个线程处理几条线
	static void __ThreadCaLowPriceFlightProcess( LPVOID pParam );

	
	static UINT __ThreadInsertMobileEJobToThreadPool( LPVOID pParam );
	static void __CeairMobileEThreadProcess( LPVOID pParam );

	template <class T>
	void	__FreeFlightList(list<T*> &flightList)
	{
		list<T*>::iterator it;
		T* pFlight = NULL;

		if (flightList.empty())
			return;
		for (it = flightList.begin(); it != flightList.end(); it++)
		{
			pFlight = *it;
			delete pFlight;
			pFlight = NULL;
		}
		flightList.clear();
	}
	void	__ResetCaTuanFlightInfoList(list<SCaLowPriceFlightDetail*> &flightList);
	void	__MergeCaTuanFlightInfoList(list<SCaLowPriceFlightDetail*> & fromFlightList, list<SCaLowPriceFlightDetail*> & toFlightList);
	SCaLowPriceFlightDetail*	__FindCaTuanFlight(list<SCaLowPriceFlightDetail*>  &flightList, SCaLowPriceFlightDetail* pKey, BOOL *pbFind);

	//东航移动E
	void	__ResetCeairMEFlightInfoList(list<SCeairFlightInfo*> &flightList);
	void	__MergeCeairMEFlightInfoList(list<SCeairFlightInfo*> & fromFlightList, list<SCeairFlightInfo*> & toFlightList);
	SCeairFlightInfo*	__FindCeairMEFlight(list<SCeairFlightInfo*>  &flightList, SCeairFlightInfo* pKey, BOOL *pbFind);

public:

	static CStringA CityCode2CityNameCode(CStringA straCityCode)
	{
		CStringA CityNameCode;
		if(straCityCode == "NAY")
			CityNameCode = "BJS";
		else if(straCityCode == "PVG")
			CityNameCode = "SHA";
		else if(straCityCode == "PEK")
			CityNameCode = "BJS";
		else 
			CityNameCode = straCityCode;
		return CityNameCode;
	}
};
