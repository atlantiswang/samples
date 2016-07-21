#pragma once

#include <list>
#include <map>
#include "common/WinHttpClient.h"

#define	 MAX_PROXY_IP_OBJ		(2)
#define	 PROXY_IP_MAX_CHAR		(30)

#define SSS_1_CLIENT		(1)
#define SSS_MULTI_CLIENT		(2)

//近3天的航班：GET_FLIGHT_TYPE = 0
//从第4天开始7天内的航班 GET_FLIGHT_TYPE = 1;
//从第11天开始的航班 GET_FLIGHT_TYPE = 2;
//年前年后的航班 GET_FLIGHT_TYPE = 3;

#define GET_FLIGHT_TYPE	(1)

#if (0 == GET_FLIGHT_TYPE || 1 ==  GET_FLIGHT_TYPE)
	#define SSS_CLIENT_NUM	(1)
	#define MAX_CLIENT_NUM	(1)
#elif(2 ==  GET_FLIGHT_TYPE)
	#define SSS_CLIENT_NUM	(2)
	#define MAX_CLIENT_NUM	(5)
#else//(3 ==  GET_FLIGHT_TYPE)
	#define SSS_CLIENT_NUM	(1)
	#define MAX_CLIENT_NUM	(2)
#endif

//#define  GET_CA_FLIGHT

//#define CEAIR_MOBILE_E

//#define GET_AQ_FLIGHT

//#define GET_KN_FLIGHT

#ifndef GET_KN_FLIGHT
	#ifndef GET_CA_FLIGHT
		#ifndef GET_AQ_FLIGHT
			#ifdef CEAIR_MOBILE_E
				#define	 PROXY_IP_BUF_MAX_COUNT		(5)
			#else
				#if (SSS_CLIENT_NUM == SSS_1_CLIENT)
					#define		GET_FLIGHT_FROM_NEW_SITE
					#define	 PROXY_IP_BUF_MAX_COUNT		(20)//10
				#else //(SSS_CLIENT_NUM == SSS_2_CLIENT)
					#define		GET_FLIGHT_FROM_NEW_SITE
					#define	 PROXY_IP_BUF_MAX_COUNT		(30)
				#endif
			#endif
		#else//#define GET_AQ_FLIGHT
			#define MAX_CLIENT_NUM (1)
			#define PROXY_IP_BUF_MAX_COUNT (20)
		#endif
	#else //#ifdef GET_CA_FLIGHT
		#define MAX_CLIENT_NUM	(1)
		#define	 PROXY_IP_BUF_MAX_COUNT		(20)
	#endif
#else
	#define MAX_CLIENT_NUM (1)
	#if (GET_FLIGHT_TYPE == 0)
		#define PROXY_IP_BUF_MAX_COUNT (20)
	#elif (GET_FLIGHT_TYPE == 1)
		#define PROXY_IP_BUF_MAX_COUNT (20)
	#else 
		#define PROXY_IP_BUF_MAX_COUNT (20)
	#endif
#endif

using namespace std;

//新建或修改政策成功后发送此消息，提示更新界面
#define WM_CTRIP_FLIGHT		(WM_USER + 110)

enum
{
	CA_TUAN_PRODUCT = 0,
	CA_TUAN_LOW_PRICE_APPLY_PRODUT
};
//城市代码信息
typedef struct CityCode
{
	CString strName;
	CString strCode;
}TCityCode,*PTCityCode;

//航线信息
typedef struct AirLineInfo
{
	CString strFromCity;
	CString strToCity;
	CString strFromCityCode;
	CString strToCityCode;
	UINT	uMinHangPrice;

	AirLineInfo& operator=(AirLineInfo& value)
	{
		strFromCity = value.strFromCity;
		strFromCityCode = value.strFromCityCode;
		strToCity = value.strToCity;
		strToCityCode = value.strToCityCode;
		uMinHangPrice = value.uMinHangPrice;

		return *this;
	}
}TAirLineInfo,*PTAirLineInfo;

//航线日期信息（日期段）
typedef struct AirLineDateInfo
{
	TAirLineInfo	_airInfo;
	CTime			tStart;
	CTime			tEnd;
}TAirLineDateInfo,*PTAirLineDateInfo;

//航线日期信息
typedef struct AirLineDetailInfo
{
	TAirLineInfo	_airInfo;
	CTime			tStart;
}TAirLineDetailInfo,*PAirLineDetailInfo;

//航线日期信息（单天）
typedef struct AirLineDateSingle
{
	TAirLineInfo	_airInfo;
	CTime			tDate;
}TAirLineDateSingle,*PTAirLineDateSingle;

typedef struct FlightInfo
{

}TFlightInfo,*PTFlightInfo;



//航班信息
typedef struct t9CFlightInfo 
{
	CStringA	straCompany;		//航空公司
	CStringA	straFromCityCode;	//出发城市代码
	CStringA	straToCityCode;		//到达城市代码
	CStringA	straFlightNo;		//航班号
	CStringA	straFromDate;		//出发日期
	CStringA	straToDate;			//到达日期
	CStringA	straFromTime;		//出发时间
	CStringA	straToTime;			//到达时间
	int			nMinHangPrice;		//民航价
	int			nPrice1;			//价格1
	int			nPrice2;			//价格2
	int			nPrice3;			//价格3
	int			nMinPrice;			//最低价
	bool		bHavePolicy;		//是否有对应的特殊政策

	CStringA	straPrice1Json;
	CStringA	straPrice2Json;
	CStringA	straPrice3Json;

	t9CFlightInfo()
	{
		straCompany = "9C";
		nMinHangPrice = 0;
		nMinPrice = 0;
		nPrice1 = 0;
		nPrice2 = 0;
		nPrice3 = 0;
		bHavePolicy = false;

		straPrice1Json = "";
		straPrice2Json = "";
		straPrice3Json = "";
	}

	t9CFlightInfo & operator=(const t9CFlightInfo & flight)
	{
		this->straCompany = flight.straCompany;	
		this->straFromCityCode = flight.straFromCityCode;
		this->straToCityCode = flight.straToCityCode;	
		this->straFlightNo = flight.straFlightNo;	
		this->straFromDate = flight.straFromDate;	
		this->straToDate = flight.straToDate;		
		this->straFromTime = flight.straFromTime;		
		this->straToTime = flight.straToTime;	
		this->straCompany = flight.straCompany;
		this->nMinHangPrice = flight.nMinHangPrice;
		this->nMinPrice = flight.nMinPrice;
		this->nPrice1 = flight.nPrice1;
		this->nPrice2 = flight.nPrice2;
		this->nPrice3 = flight.nPrice3;
		this->bHavePolicy = flight.bHavePolicy;
		this->straPrice1Json = flight.straPrice1Json;
		this->straPrice2Json = flight.straPrice2Json;
		this->straPrice3Json = flight.straPrice3Json;

		return *this;
	}

}T9CFlightInfo,*PT9CFlightInfo;

typedef struct _tagTimePara
{
	BYTE u8Hour:8;	//0：7
	BYTE u8Minute:8;//8：15
	BYTE u8Sec:8;	//16：23
	BYTE uReserved:8;//24：31
}STimePara;
typedef union _tagUTimePara
{
	STimePara	sTime;
	UINT		u32;
}UTimePara;

typedef struct _tagDatePara
{
	WORD wYear:16;	//0：15
	BYTE u8Month:5;//16：20
	BYTE u8Day:6;	//21：26
	BYTE uReserved:5;//27：31
}SDatePara;
typedef union _tagUDatePara
{
	SDatePara	sDate;
	UINT		u32;
}UDatePara;

//设置信息
typedef struct ConfigInfo
{
	CStringA strDbHost;
	CStringA strDbUser;
	CStringA strDbPwd;
	CStringA strDbName;
	UINT	nDbPort;
	UINT	uClientId;

	CTime	tNoChangeFlightPoll;
	CTime	tLessChangeFlightPoll;
	BOOL	bAutoModDate;
	BOOL	bSelP4Ticket;	//是否上4折及以下的票
	BOOL	bSelP5Ticket;	//是否上4折以上的票
	BOOL	bSelSpecialPriceTicket;	//是否上4折以下的特价票，9，99，199，299元……
	int		nP4SpecialPrice;	//不上4折 nP4SpecialPrice价格以下且数字末尾带9的票……
	UTimePara uSel9Start;
	UTimePara uSel9End;

	ConfigInfo()
	{
		strDbHost	= _T("127.0.0.1");
		strDbUser	= _T("root");
		strDbPwd	= _T("hifb@2014");
		strDbName	= _T("hifb");
		nDbPort		= 3306;
		bSelP4Ticket = TRUE;
		bSelP5Ticket = TRUE;
		bSelSpecialPriceTicket = TRUE;
		nP4SpecialPrice = 800;
		uSel9Start.u32 = 0;
		uSel9End.u32 = 0;
	}
}TConfigInfo,*PTConfigInfo;

typedef struct _tagGetIp
{
	char	szIpBuf[PROXY_IP_MAX_CHAR+1];
	int		iRowId;
	_tagGetIp()
	{
		SecureZeroMemory(szIpBuf, sizeof(szIpBuf));
		szIpBuf[0] = '\0';
		iRowId = 1;
	}
}SGetIp;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//国航
typedef struct _tagSCaLowPriceFlightInfo
{
	int iProductId;
	int	iProductType;	//普通团购，低价申请团购	CA_TUAN_PRODUCT = 0, CA_TUAN_LOW_PRICE_APPLY_PRODUT
	int iMinHangPrice;	//民航价
	CStringA straDCityCode;
	CStringA straACityCode;
	int	 iCityCode;
	CStringA straCity;

	_tagSCaLowPriceFlightInfo & operator=(_tagSCaLowPriceFlightInfo & info)
	{
		this->iProductId = info.iProductId;
		this->iProductType = info.iProductType;
		this->straDCityCode = info.straDCityCode;
		this->straACityCode = info.straACityCode;
		this->iCityCode = info.iCityCode;
		this->straCity = info.straCity;

		return *this;
	}
}SCaLowPriceFlightInfo;

typedef struct _tagSCaAirLineDetailProcess
{
	CDialogEx*			pDlg;
	std::list<SCaLowPriceFlightInfo*> lowPriceFlightList;
}SCaAirLineDetailProcess,*PSCaAirLineDetailProcess;


//航班信息
typedef struct _tagCaLowPriceFlightDetail 
{
	CStringA	straCompany;		//航空公司
	CStringA	straFromCityCode;	//出发城市代码
	CStringA	straToCityCode;		//到达城市代码
	CStringA	straFlightNo;		//航班号
	CStringA	straFromDate;		//出发日期
	CStringA	straSaleEndDate;	//销售结束日期
	CStringA	straSaleEndTime;	//销售结束时间
	int			nPrice;				//价格
	int			nProductId;			//所属产品编号
	int			nRemainSeat;		//余票
	int			nProductType;		//所属产品类型,CA_TUAN_PRODUCT;	CA_TUAN_LOW_PRICE_APPLY_PRODUT

	_tagCaLowPriceFlightDetail()
	{
		straCompany = "CA";		//航空公司
		straFromCityCode = "";	//出发城市代码
		straToCityCode = "";	//到达城市代码
		straFlightNo = "";		//航班号
		straFromDate = "";		//出发日期
		straSaleEndDate = "";	//销售结束日期
		straSaleEndTime = "";	//销售结束时间
		nPrice = 0;				//价格
		nProductId = 0;			//所属产品编号
		nRemainSeat = 0;		//余票
		nProductType = CA_TUAN_PRODUCT;
	}

	_tagCaLowPriceFlightDetail & operator=(const _tagCaLowPriceFlightDetail & det)
	{
		this->straCompany = det.straCompany;	
		this->straFromCityCode = det.straFromCityCode;	
		this->straToCityCode = det.straToCityCode;	
		this->straFlightNo = det.straFlightNo;		
		this->straFromDate = det.straFromDate;	
		this->straSaleEndDate = det.straSaleEndDate;	
		this->straSaleEndTime = det.straSaleEndTime;	
		this->nPrice = det.nPrice;				
		this->nProductId = det.nProductId;			
		this->nRemainSeat = det.nRemainSeat;	
		this->nProductType = det.nProductType;

		return *this;
	}
}SCaLowPriceFlightDetail ,*PCaLowPriceFlightDetail;

//end国航
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class CDataProcess
{
public:
	CDataProcess(void);
	~CDataProcess(void);

	bool	m_bStarting;	//用于控制线程的关闭

	static CString	m_strXmlFile;

	map<CString,CString>	m_mapCityCodes;
	TConfigInfo				m_configInfo;
	UDatePara				m_uCaTuanGetFlightEndDate;//抓取国航团购的航班最大日期
	bool					m_bGetAllCaTuanFlight;//是否抓取所有的团购航线

	int						m_iExtraAddPrice;
	BOOL					m_bOutCeairLog;	//输出东航移动E日志到文件,二进制格式，文件名为ceairlog.log

	//加载配置信息
	bool	LoadConfigFromXml();
	//保存配置信息
	bool	SaveConfigToini();
	//加载民航价格
	BOOL	LoadMinHangPrice();
	//得到航线的民航价格，不分始发，两个城市间的航线民航价格是固定的
	UINT	GetMinHangPrice(std::map<CString, UINT> & priceMap, CString & strCity1Code, CString & strCity2Code);

	//保存不同轮询时间间隔的执行情况
	void	SaveNoChangeFlightPollTime();
	void	LoadNoChangeFlightPollTime();
	BOOL	NeedNoChangeFlightPoll();//是否需要轮询几乎不变的航线

	void	SaveLessChangeFlightPollTime();
	void	LoadLessChangeFlightPollTime();
	BOOL	NeedLessChangeFlightPoll();//是否需要轮询很少变的航线

	static void DateStrToCTime(CString strDate, CTime& t);
	static CTime	GetQueryStartTime(){return m_queryStartTime;};
	

	// 通过城市名称得到城市代码
	CString GetCityCodeByName(CString& strCityName);

	// 通过城市代码得到城市名称
	CString GetCityNameByCode(CString& strCityCode);
	// 保存航线信息到xml文件
	BOOL SaveAirlinesToXml(list<PTAirLineInfo>& listAirline);
	// 得到当前exe文件所在路径
	CString GetExePath(void);
	// 从xml文件中加载航线信息
	BOOL LoadAirlinesFromXml(list<PTAirLineInfo>& listAirline);
	// 保存日期等航线信息到xml文件中
	BOOL SaveAirlineDateToXml(list<PTAirLineDateInfo>& listAirDate, CString strFullPath = _T(""));
	// 从xml文件中加载航线日期信息
	BOOL LoadAirlineDateFromXml(list<PTAirLineDateInfo>& listAirDate, CString strFullPath = _T(""));
	// 判断城市是否存在
	BOOL IsCityExist(CString& strCity);
	// 得到数据处理的唯一实例
	static CDataProcess* GetInstance(void);

	static std::string Unicode2Ansi(const wchar_t* wstr);
	//取得汉字首字母
	static CString GetFirstLetter(LPCTSTR strName);
	
	// 得到新的政策代码
	static CString GetNewPolicyCode(void);
	// 加载城市代码
	bool LoadCityCodes(void);

	int ChangeProxy(WinHttpClient& httpClient);

	void GenAirLine(list<PTAirLineDateInfo>& listAirDate);
	BOOL __FindKeyInMap(std::map<CString, int> & mp, CString & strKey);

	CStringA ConvertCtripTo9C(CStringA & straCode);

private:
	static CString m_strIniFileName;

	static CTime	m_queryStartTime;
	static BOOL		m_bqueryStartTimeOk;

	std::map<CString, UINT>	m_minHangPriceMap;
	void			__GenMinHangPriceXml();
};

#define _DataProcess CDataProcess::GetInstance();
