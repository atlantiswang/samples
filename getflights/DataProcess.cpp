#include "StdAfx.h"
#include "DataProcess.h"
#include "./common/Markup.h"
#include "DbCenter.h"
#include "./common/CStringToolEx.h"
#include "GetFlights.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define random(x) (rand()%x)

CString CDataProcess::m_strIniFileName = _T("sssConfig.ini");
CTime	CDataProcess::m_queryStartTime;
BOOL	CDataProcess::m_bqueryStartTimeOk = FALSE;

CDataProcess::CDataProcess(void)
{
	LoadConfigFromXml();
	//__GenMinHangPriceXml();
	LoadMinHangPrice();
}


CDataProcess::~CDataProcess(void)
{

}


// 通过城市名称得到城市代码
CString CDataProcess::GetCityCodeByName(CString& strCityName)
{
	CString strRet(_T(""));
	map<CString,CString>::iterator itmap;
	
	CString strQz(_T("泉州"));
	CString strJj(_T("晋江"));
	CString strSt(_T("汕头"));
	if (0 == strCityName.CompareNoCase(strSt))
		strRet = _T("SWA");
	else if (0 == strCityName.CompareNoCase(strQz) || 0 == strCityName.CompareNoCase(strJj))
		strRet = _T("JJN");
	else
	{
		for (itmap = m_mapCityCodes.begin(); itmap != m_mapCityCodes.end(); itmap++)
		{
			if (0 == strCityName.Compare(itmap->second))
			{			
				strRet = itmap->first;
			}
		}
	}

	return strRet;
}


// 通过城市代码得到城市名称
CString CDataProcess::GetCityNameByCode(CString& strCityCode)
{
	CString strRet(_T(""));

	map<CString,CString>::iterator itmap = m_mapCityCodes.find(strCityCode);
	if (itmap != m_mapCityCodes.end())
	{
		strRet = itmap->second;
	}
	return strRet;
}


// 保存航线信息到xml文件
BOOL CDataProcess::SaveAirlinesToXml(list<PTAirLineInfo>& listAirline)
{
	CString strXmlFile = GetExePath() + _T("\\Airlines.xml");
	CMarkup xml;
	if (!xml.Load(strXmlFile))
	{
		xml.Load(_T(""),0);
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n"));
	}
	if (xml.FindElem(_T("Airlines")))
	{
		xml.RemoveElem();
	}
	xml.AddElem(_T("Airlines"));

	if (xml.IntoElem())
	{
		list<PTAirLineInfo>::iterator it;  
		for (it = listAirline.begin(); it != listAirline.end();it++)  
		{  
			xml.AddElem(_T("AirLineInfo"));
			xml.AddChildElem(_T("From"),(*it)->strFromCity);
			xml.AddChildElem(_T("To"),(*it)->strToCity);		
		}
	}

	xml.Save(strXmlFile);

	return TRUE;
}

//加载配置信息
bool CDataProcess::LoadConfigFromXml()
{
	CString strIni = GetExePath() + m_strIniFileName;

	char szTemp[256];

	GetPrivateProfileStringA("DbInfo","dbhost","127.0.0.1",szTemp,256,CStrT2CStrA(strIni));
	m_configInfo.strDbHost.Format("%s",szTemp);
	GetPrivateProfileStringA("DbInfo","dbuser","root",szTemp,256,CStrT2CStrA(strIni));
	m_configInfo.strDbUser.Format("%s",szTemp);
	GetPrivateProfileStringA("DbInfo","dbpasswd","上海中联",szTemp,256,CStrT2CStrA(strIni));
	m_configInfo.strDbPwd.Format("%s",szTemp);
	GetPrivateProfileStringA("DbInfo","dbname","myhifb",szTemp,256,CStrT2CStrA(strIni));
	m_configInfo.strDbName.Format("%s",szTemp);
	m_configInfo.nDbPort = GetPrivateProfileIntA("DbInfo","dbport",3306,CStrT2CStrA(strIni));

	m_configInfo.uClientId = GetPrivateProfileIntA("DbInfo","uSssClientId", 0,CStrT2CStrA(strIni));
	if (m_configInfo.uClientId >= MAX_CLIENT_NUM)
	{
		m_configInfo.uClientId = 0;
	}
	m_configInfo.bAutoModDate = (BOOL)GetPrivateProfileIntA("airline","autoModDate", 0,CStrT2CStrA(strIni));
	m_configInfo.bSelP4Ticket = (BOOL)GetPrivateProfileInt(_T("airline"), _T("selP4Ticket"), TRUE, strIni);
	m_configInfo.bSelP5Ticket = (BOOL)GetPrivateProfileInt(_T("airline"), _T("selP5Ticket"), TRUE, strIni);
	m_configInfo.bSelSpecialPriceTicket = (BOOL)GetPrivateProfileInt(_T("airline"), _T("selSpecialPriceTicket"), TRUE, strIni);
	if ((FALSE == m_configInfo.bSelP4Ticket) && (FALSE == m_configInfo.bSelP5Ticket))
	{
		m_configInfo.bSelP4Ticket = TRUE;
		AfxMessageBox(_T("错误：4折以下和4折以上的票都没上，请至少选择一个，否则系统将默认上4折以下的票。"));
	}
	m_configInfo.nP4SpecialPrice = GetPrivateProfileInt(_T("airline"), _T("SpecialPrice"), 800, strIni);
	m_configInfo.uSel9Start.u32 = 0;
	m_configInfo.uSel9Start.sTime.u8Hour = (BYTE)GetPrivateProfileInt(_T("airline"), _T("Sel9StartHour"), 9, strIni);
	m_configInfo.uSel9Start.sTime.u8Minute = (BYTE)GetPrivateProfileInt(_T("airline"), _T("Sel9StartMin"), 30, strIni);
	m_configInfo.uSel9End.u32 = 0;
	m_configInfo.uSel9End.sTime.u8Hour = (BYTE)GetPrivateProfileInt(_T("airline"), _T("Sel9EndHour"), 17, strIni);
	m_configInfo.uSel9End.sTime.u8Minute = (BYTE)GetPrivateProfileInt(_T("airline"), _T("Sel9EndMin"), 30, strIni);

	//不同轮询时间间隔的执行情况
	LoadNoChangeFlightPollTime();
	LoadLessChangeFlightPollTime();
	//end 不同轮询时间间隔的执行情况

	m_uCaTuanGetFlightEndDate.u32 = 0;
	m_uCaTuanGetFlightEndDate.sDate.wYear = (WORD)GetPrivateProfileInt(_T("caTuan"), _T("endYear"), 2015, strIni);
	m_uCaTuanGetFlightEndDate.sDate.u8Month = (WORD)GetPrivateProfileInt(_T("caTuan"), _T("endMonth"), 1, strIni);
	m_uCaTuanGetFlightEndDate.sDate.u8Day = (WORD)GetPrivateProfileInt(_T("caTuan"), _T("endDay"), 31, strIni);
	m_bGetAllCaTuanFlight = (bool)GetPrivateProfileInt(_T("caTuan"), _T("getAll"), 1, strIni);

	m_iExtraAddPrice = GetPrivateProfileInt(_T("AddPrice_Extra"), _T("sssAdd"), 150, strIni);

	m_bOutCeairLog = (BOOL)GetPrivateProfileInt(_T("log"), _T("ceairlog"), 0, strIni);

	return true;
}

//保存配置信息
bool CDataProcess::SaveConfigToini()
{
	CString strIni = GetExePath() + m_strIniFileName;

	return true;
}
void CDataProcess::LoadNoChangeFlightPollTime()
{
	CString strIni = GetExePath() + m_strIniFileName;

	int iYear = GetPrivateProfileInt(_T("Poll"), _T("noChangeYear"), 1971, strIni);
	int iMonth = GetPrivateProfileInt(_T("Poll"), _T("noChangeMonth"), 1, strIni);
	int iDay = GetPrivateProfileInt(_T("Poll"), _T("noChangeDay"), 1, strIni);
	int iHour = GetPrivateProfileInt(_T("Poll"), _T("noChangeHour"), 0, strIni);
	int iMinute = GetPrivateProfileInt(_T("Poll"), _T("noChangeMinute"), 0, strIni);
	m_configInfo.tNoChangeFlightPoll = CTime(iYear, iMonth, iDay, iHour, iMinute, 0);
}
//保存不同轮询时间间隔的执行情况
void  CDataProcess::SaveNoChangeFlightPollTime()
{
	CString strIni = GetExePath() + m_strIniFileName;
	CTime t = CTime::GetCurrentTime();
	int iYear = t.GetYear();
	int iMonth = t.GetMonth();
	int iDay = t.GetDay();
	int iHour = t.GetHour();
	int iMinute = t.GetMinute();
	m_configInfo.tNoChangeFlightPoll = CTime(iYear, iMonth, iDay, iHour, iMinute, 0);
	CString strTemp;
	strTemp.Format(_T("%02d"), iYear);
	WritePrivateProfileString(_T("Poll"), _T("noChangeYear"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iMonth);
	WritePrivateProfileString(_T("Poll"), _T("noChangeMonth"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iDay);
	WritePrivateProfileString(_T("Poll"), _T("noChangeDay"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iHour);
	WritePrivateProfileString(_T("Poll"), _T("noChangeHour"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iMinute);
	WritePrivateProfileString(_T("Poll"), _T("noChangeMinute"), strTemp, strIni);
}
BOOL CDataProcess::NeedNoChangeFlightPoll()
{
	BOOL bNeed = FALSE;
	CString strCurDay;
	CTime tCurTime = CTime::GetCurrentTime();
	//几乎不变的航线一天轮询一遍
	CTime tPollTime = m_configInfo.tNoChangeFlightPoll + CTimeSpan(1, 0, 0, 0);
	if (tCurTime >= tPollTime)
		bNeed = TRUE;

	return bNeed;
}
void CDataProcess::SaveLessChangeFlightPollTime()
{
	CString strIni = GetExePath() + m_strIniFileName;
	CTime t = CTime::GetCurrentTime();
	int iYear = t.GetYear();
	int iMonth = t.GetMonth();
	int iDay = t.GetDay();
	int iHour = t.GetHour();
	int iMinute = t.GetMinute();
	m_configInfo.tLessChangeFlightPoll = CTime(iYear, iMonth, iDay, iHour, iMinute, 0);
	CString strTemp;
	strTemp.Format(_T("%02d"), iYear);
	WritePrivateProfileString(_T("Poll"), _T("lessChangeYear"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iMonth);
	WritePrivateProfileString(_T("Poll"), _T("lessChangeMonth"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iDay);
	WritePrivateProfileString(_T("Poll"), _T("lessChangeDay"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iHour);
	WritePrivateProfileString(_T("Poll"), _T("lessChangeHour"), strTemp, strIni);
	strTemp.Format(_T("%02d"), iMinute);
	WritePrivateProfileString(_T("Poll"), _T("lessChangeMinute"), strTemp, strIni);
}

void CDataProcess::LoadLessChangeFlightPollTime()
{
	CString strIni = GetExePath() + m_strIniFileName;

	int iYear = GetPrivateProfileInt(_T("Poll"), _T("lessChangeYear"), 1971, strIni);
	int iMonth = GetPrivateProfileInt(_T("Poll"), _T("lessChangeMonth"), 1, strIni);
	int iDay = GetPrivateProfileInt(_T("Poll"), _T("lessChangeDay"), 1, strIni);
	int iHour = GetPrivateProfileInt(_T("Poll"), _T("lessChangeHour"), 0, strIni);
	int iMinute = GetPrivateProfileInt(_T("Poll"), _T("lessChangeMinute"), 0, strIni);
	m_configInfo.tLessChangeFlightPoll = CTime(iYear, iMonth, iDay, iHour, iMinute, 0);
}

//是否需要轮询很少变的航线
BOOL CDataProcess::NeedLessChangeFlightPoll()
{
	BOOL bNeed = FALSE;
	CString strCurDay;
	CTime tCurTime = CTime::GetCurrentTime();
	//很少变的航线2小时轮询一遍
	CTime tPollTime = m_configInfo.tLessChangeFlightPoll + CTimeSpan(0, 2, 0, 0);
	if (tCurTime >= tPollTime)
		bNeed = TRUE;

	return bNeed;	
}

// 得到当前exe文件所在路径
CString CDataProcess::GetExePath(void)
{
	TCHAR path[1024];
	int len = GetModuleFileName(AfxGetInstanceHandle(),path,1024);
	path[len]=0;
	TCHAR* ret = _tcsrchr(path,'\\');
	if(!ret)
		return _T("");
	int idxlen = (int)(ret - path + 1);
	path[idxlen]=0;
	return CString(path);
}


// 从xml文件中加载航线信息
BOOL CDataProcess::LoadAirlinesFromXml(list<PTAirLineInfo>& listAirline)
{
	CMarkup xml;
	if (!xml.Load(GetExePath() + _T("\\Airlines.xml")))
	{
		return FALSE;
	}
	if (!xml.FindElem(_T("Airlines")))
	{
		return FALSE;
	}

	if (xml.IntoElem())
	{
		while (xml.FindElem(_T("AirLineInfo")))
		{
			xml.IntoElem();

			PTAirLineInfo pInfo = new TAirLineInfo;
			if (xml.FindElem(_T("From")))
			{
				pInfo->strFromCity = xml.GetData();
				pInfo->strFromCityCode = GetCityCodeByName(pInfo->strFromCity);
			}
			if (xml.FindElem(_T("To")))
			{
				pInfo->strToCity = xml.GetData();
				pInfo->strToCityCode = GetCityCodeByName(pInfo->strToCity);
			}
			pInfo->uMinHangPrice = GetMinHangPrice(m_minHangPriceMap, pInfo->strFromCityCode, pInfo->strToCityCode);
			//TRACE(_T("\n%s=%d"), pInfo->strFromCityCode+pInfo->strToCityCode, pInfo->uMinHangPrice);

			listAirline.push_back(pInfo);

			xml.OutOfElem();
		}

	}

	return TRUE;
}


// 保存日期等航线信息到xml文件中
BOOL CDataProcess::SaveAirlineDateToXml(list<PTAirLineDateInfo>& listAirDate, CString strFullPath)
{
	CMarkup xml;
#ifdef CEAIR_MOBILE_E
	CString strXmlFile = GetExePath() + _T("\\ceairMeAirlineDates.xml");
#else
	CString strXmlFile = GetExePath() + _T("\\sssAirlineDates.xml");
#endif
	if (!strFullPath.IsEmpty())
		strXmlFile = strFullPath;

	if (!xml.Load(strXmlFile))
	{
		xml.Load(_T(""),0);
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n"));
	}
	if (xml.FindElem(_T("AirlineDates")))
	{
		xml.RemoveElem();
	}
	xml.AddElem(_T("AirlineDates"));

	if (xml.IntoElem())
	{
		CString strTemp;
		list<PTAirLineDateInfo>::iterator it;  
		PTAirLineDateInfo pInfo = NULL;
		for (it = listAirDate.begin(); it != listAirDate.end();it++)  
		{  
			pInfo = *it;
			xml.AddElem(_T("AirLineDateInfo"));
			xml.AddChildElem(_T("From"),pInfo->_airInfo.strFromCity);
			xml.AddChildElem(_T("To"),pInfo->_airInfo.strToCity);		
			strTemp.Format(_T("%d-%02d-%02d"),pInfo->tStart.GetYear(),pInfo->tStart.GetMonth(),pInfo->tStart.GetDay());
			xml.AddChildElem(_T("StartDate"),strTemp);
			strTemp.Format(_T("%d-%02d-%02d"),pInfo->tEnd.GetYear(),pInfo->tEnd.GetMonth(),pInfo->tEnd.GetDay());
			xml.AddChildElem(_T("EndDate"),strTemp);
		}
	}

	xml.Save(strXmlFile);

	return TRUE;
}


// 从xml文件中加载航线日期信息
BOOL CDataProcess::LoadAirlineDateFromXml(list<PTAirLineDateInfo>& listAirDate, CString strFullPath)
{
	CMarkup xml;
#ifdef CEAIR_MOBILE_E
	CString strXmlFile = GetExePath() + _T("\\ceairMeAirlineDates.xml");
#else
	CString strXmlFile = GetExePath() + _T("\\sssAirlineDates.xml");
#endif
	if (!strFullPath.IsEmpty())
		strXmlFile = strFullPath;
	if (!xml.Load(strXmlFile))
	{
		return FALSE;
	}
	if (!xml.FindElem(_T("AirlineDates")))
	{
		return TRUE;
	}

	CTime curTime = CTime::GetCurrentTime();
	CTime tToday = CTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 0, 0, 0);
	CTime tStart = tToday + CTimeSpan(1, 0, 0, 0);
	CTime tEnd = curTime + CTimeSpan(60, 0, 0, 0);

	if (xml.IntoElem())
	{
		while (xml.FindElem(_T("AirLineDateInfo")))
		{
			xml.IntoElem();

			PTAirLineDateInfo pInfo = new TAirLineDateInfo;
			if (xml.FindElem(_T("From")))
			{
				pInfo->_airInfo.strFromCity = xml.GetData();
				pInfo->_airInfo.strFromCityCode = GetCityCodeByName(pInfo->_airInfo.strFromCity);
				ASSERT(!pInfo->_airInfo.strFromCityCode.IsEmpty());
			}
			if (xml.FindElem(_T("To")))
			{
				pInfo->_airInfo.strToCity = xml.GetData();
				pInfo->_airInfo.strToCityCode = GetCityCodeByName(pInfo->_airInfo.strToCity);
				ASSERT(!pInfo->_airInfo.strToCityCode.IsEmpty());
			}
			if (xml.FindElem(_T("StartDate")))
			{
				int nYear,nMonth,nDay;
				sscanf(Unicode2Ansi(xml.GetData()).c_str(),"%d-%d-%d",&nYear,&nMonth,&nDay);  
				CTime t(nYear,nMonth,nDay,0,0,0);
				
				if (m_configInfo.bAutoModDate)
				{
					pInfo->tStart = tStart;
				}
				else
				{
					pInfo->tStart = t;
				}

				if (!m_bqueryStartTimeOk)
				{
					m_bqueryStartTimeOk = TRUE;
					m_queryStartTime = pInfo->tStart;
				}
			}
			if (xml.FindElem(_T("EndDate")))
			{
				int nYear,nMonth,nDay;
				sscanf(Unicode2Ansi(xml.GetData()).c_str(),"%d-%d-%d",&nYear,&nMonth,&nDay);  
				CTime t(nYear,nMonth,nDay,0,0,0);
				
				if (m_configInfo.bAutoModDate)
				{
					pInfo->tEnd = tEnd;
				}
				else
				{
					pInfo->tEnd = t;
				}
			}
			pInfo->_airInfo.uMinHangPrice = GetMinHangPrice(m_minHangPriceMap, pInfo->_airInfo.strFromCityCode, pInfo->_airInfo.strToCityCode);
			TRACE(_T("\n%s=%d"), pInfo->_airInfo.strFromCityCode+pInfo->_airInfo.strToCityCode, pInfo->_airInfo.uMinHangPrice);

			listAirDate.push_back(pInfo);

			xml.OutOfElem();
		}

	}

	TRACE(_T("\n listAirDate size= %d "), listAirDate.size());

	return TRUE;
}


// 判断城市是否存在
BOOL CDataProcess::IsCityExist(CString& strCity)
{
	return 0;
}


// 得到数据处理的唯一实例
CDataProcess* CDataProcess::GetInstance(void)
{
	static CDataProcess dp;
	return &dp;
}


std::string CDataProcess::Unicode2Ansi(const wchar_t* wstr) 
{
	int len = WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,wstr,-1,NULL,0,NULL,NULL);
	char* tmps = new char[len];
	WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,wstr,-1,tmps,len,NULL,NULL);
	std::string ss = tmps;
	delete [] tmps;
	return ss;
}

//取得汉字首字母
CString CDataProcess::GetFirstLetter(LPCTSTR strName)
{
		static TCHAR* wcsFiestLetterTable = 
			_T("ydkqsxnwzssxjbymgcczqpssqbycdscdqldylybssjgyqzjjfgcclzznwdwzjljpfyynnjjtmynzwzhflzppqhgccyynmjqyxxgdnnsnsjnjnsnnmlnrxyfsngnnnnqzggllyjlnyzssecykyyhqwjssggyxyqyjtwktjhychmnxjtlhjyqbyxdldwrrjnwysrldzjpcbzjjbrcfslnczstzfxxchtrqggddlyccssymmrjcyqzpwwjjyfcrwfdfzqpyddwyxkyjawjffxjbcftzyhhycyswccyxsclcxxwzcxnbgnnxbxlzsqsbsjpysazdhmdzbqbscwdzzyytzhbtsyyfzgntnxjywqnknphhlxgybfmjnbjhhgqtjcysxstkzglyckglysmzxyalmeldccxgzyrjxjzlnjzcqkcnnjwhjczccqljststbnhbtyxceqxkkwjyflzqlyhjxspsfxlmpbysxxxytccnylllsjxfhjxpjbtffyabyxbcczbzyclwlczggbtssmdtjcxpthyqtgjjxcjfzkjzjqnlzwlslhdzbwjncjzyzsqnycqynzcjjwybrtwpyftwexcskdzctbyhyzqyyjxzcfbzzmjyxxsdczottbzljwfckscsxfyrlrygmbdthjxsqjccsbxyytswfbjdztnbcnzlcyzzpsacyzzsqqcshzqydxlbpjllmqxqydzxsqjtzpxlcglqdcwzfhctdjjsfxjejjtlbgxsxjmyjjqpfzasyjnsydjxkjcdjsznbartcclnjqmwnqnclllkbdbzzsyhqcltwlccrshllzntylnewyzyxczxxgdkdmtcedejtsyyssdqdfmxdbjlkrwnqlybglxnlgtgxbqjdznyjsjyjcjmrnymgrcjczgjmzmgxmmryxkjnymsgmzzymknfxmbdtgfbhcjhkylpfmdxlxjjsmsqgzsjlqdldgjycalcmzcsdjllnxdjffffjcnfnnffpfkhkgdpqxktacjdhh")
			_T("zdddrrcfqyjkqccwjdxhwjlyllzgcfcqjsmlzpbjjblsbcjggdckkdezsqcckjgcgkdjtjllzycxklqccgjcltfpcqczgwbjdqyzjjbyjhsjddwgfsjgzkcjctllfspkjgqjhzzljplgjgjjthjjyjzccmlzlyqbgjwmljkxzdznjqsyzmljlljkywxmkjlhskjhbmclyymkxjqlbmllkmdxxkwyxwslmlpsjqqjqxyqfjtjdxmxxllcrqbsyjbgwynnggbcnxpjtgpapfgdjqbhbncfjyzjkjkhxqfgqckfhygkhdkllsdjqxpqyaybnqsxqnszswhbsxwhxwbzzxdmndjbsbkbbzklylxgwxjjwaqzmywsjqlsjxxjqwjeqxnchetlzalyyyszzpnkyzcptlshtzcfycyxyljsdcjqagyslcllyyysslqqqnldxzsccscadycjysfsgbfrsszqsbxjpsjysdrckgjlgtkzjzbdktcsyqpyhstcldjnhmymcgxyzhjdctmhltxzhylamoxyjcltyfbqqjpfbdfehthsqhzywwcncxcdwhowgyjlegmdqcwgfjhcsntmydolbygnqwesqpwnmlrydzszzlyqpzgcwxhnxpyxshmdqjgztdppbfbhzhhjyfdzwkgkzbldnzsxhqeegzxylzmmzyjzgszxkhkhtxexxgylyapsthxdwhzydpxagkydxbhnhnkdnjnmyhylpmgecslnzhkxxlbzzlbmlsfbhhgsgyyggbhscyajtxglxtzmcwzydqdqmngdnllszhngjzwfyhqswscelqajynytlsxthaznkzzsdhlaxxtwwcjhqqtddwzbcchyqzflxpslzqgpzsznglydqtbdlxntctajdkywnsyzljhhdzckryyzywmhychhhxhjkzwsxhdnxlyscqydpslyzwmypnkxyjlkchtyhaxqsyshxasmchkdscrsgjpwqsgzjlwwschsjhsqnhnsngndantbaalczmss")
			_T("tdqjcjktscjnxplggxhhgoxzcxpdmmhldgtybynjmxhmrzplxjzckzxshflqxxcdhxwzpckczcdytcjyxqhlxdhypjqxnlsyydzozjnhhqezysjyayxkypdgxddnsppyzndhthrhxydpcjjhtcnnctlhbynyhmhzllnnxmylllmdcppxhmxdkycyrdltxjchhznxclcclylnzsxnjzzlnnnnwhyqsnjhxynttdkyjpychhyegkcwtwlgjrlggtgtygyhpyhylqyqgcwyqkpyyettttlhyylltyttsylnyzwgywgpydqqzzdqnnkcqnmjjzzbxtqfjkdffbtkhzkbxdjjkdjjtlbwfzpptkqtztgpdwntpjyfalqmkgxbcclzfhzcllllanpnxtjklcclgyhdzfgyddgcyyfgydxkssendhykdndknnaxxhbpbyyhxccgapfqyjjdmlxcsjzllpcnbsxgjyndybwjspcwjlzkzddtacsbkzdyzypjzqsjnkktknjdjgyepgtlnyqnacdntcyhblgdzhbbydmjregkzyheyybjmcdtafzjzhgcjnlghldwxjjkytcyksssmtwcttqzlpbszdtwcxgzagyktywxlnlcpbclloqmmzsslcmbjcsdzkydczjgqjdsmcytzqqlnzqzxssbpkdfqmddzzsddtdmfhtdycnaqjqkypbdjyyxtljhdrqxlmhkydhrnlklytwhllrllrcxylbnsrnzzsymqzzhhkyhxksmzsyzgcxfbnbsqlfzxxnnxkxwymsddyqnggqmmyhcdzttfgyyhgsbttybykjdnkyjbelhdypjqnfxfdnkzhqksbyjtzbxhfdsbdaswpawajldyjsfhblcnndnqjtjnchxfjsrfwhzfmdrfjyxwzpdjkzyjympcyznynxfbytfyfwygdbnzzzdnytxzemmqbsqehxfznbmflzzsrsyqjgsxwzjsprytjsjgskjjgljjynzjjxhgjkymlpyyycxycg")
			_T("qzswhwlyrjlpxslcxmnsmwklcdnknynpsjszhdzeptxmwywxyysywlxjqcqxzdclaeelmcpjpclwbxsqhfwrtfnjtnqjhjqdxhwlbyccfjlylkyynldxnhycstyywncjtxywtrmdrqnwqcmfjdxzmhmayxnwmyzqtxtlmrspwwjhanbxtgzypxyyrrclmpamgkqjszycymyjsnxtplnbappypylxmyzkynldgyjzcchnlmzhhanqnbgwqtzmxxmllhgdzxnhxhrxycjmffxywcfsbssqlhnndycannmtcjcypnxnytycnnymnmsxndlylysljnlxyssqmllyzlzjjjkyzzcsfbzxxmstbjgnxnchlsnmcjscyznfzlxbrnnnylmnrtgzqysatswryhyjzmgdhzgzdwybsscskxsyhytsxgcqgxzzbhyxjscrhmkkbsczjyjymkqhzjfnbhmqhysnjnzybknqmcjgqhwlsnzswxkhljhyybqcbfcdsxdldspfzfskjjzwzxsddxjseeegjscssygclxxnwwyllymwwwgydkzjggggggsycknjwnjpcxbjjtqtjwdsspjxcxnzxnmelptfsxtllxcljxjjljsxctnswxlennlyqrwhsycsqnybyaywjejqfwqcqqcjqgxaldbzzyjgkgxbltqyfxjltpydkyqhpmatlcndnkxmtxynhklefxdllegqtymsawhzmljtkynxlyjzljeeyybqqffnlyxhdsctgjhxywlkllxqkcctnhjlqmkkzgcyygllljdcgydhzwypysjbzjdzgyzzhywyfqdtyzszyezklymgjjhtsmqwyzljyywzcsrkqyqltdxwcdrjalwsqzwbdcqyncjnnszjlncdcdtlzzzacqqzzddxyblxcbqjylzllljddzjgyqyjzyxnyyyexjxksdaznyrdlzyyynjlslldyxjcykywnqcclddnyyynycgczhjxcclgzqjgnwnncqqjysbzzxyjxjnxjf")
			_T("zbsbdsfnsfpzxhdwztdmpptflzzbzdmyypqjrsdzsqzsqxbdgcpzswdwcsqzgmdhzxmwwfybpngphdmjthzsmmbgzmbzjcfzhfcbbnmqdfmbcmcjxlgpnjbbxgyhyyjgptzgzmqbqdcgybjxlwnkydpdymgcftpfxyztzxdzxtgkptybbclbjaskytssqyymscxfjhhlsllsjpqjjqaklyldlycctsxmcwfgngbqxllllnyxtyltyxytdpjhnhgnkbyqnfjyyzbyyessessgdyhfhwtcqbsdzjtfdmxhcnjzymqwsrxjdzjqbdqbbsdjgnfbknbxdkqhmkwjjjgdllthzhhyyyyhhsxztyyyccbdbpypzyccztjpzywcbdlfwzcwjdxxhyhlhwczxjtcnlcdpxnqczczlyxjjcjbhfxwpywxzpcdzzbdccjwjhmlxbqxxbylrddgjrrctttgqdczwmxfytmmzcwjwxyywzzkybzcccttqnhxnwxxkhkfhtswoccjybcmpzzykbnnzpbthhjdlszddytyfjpxyngfxbyqxzbhxcpxxtnzdnnycnxsxlhkmzxlthdhkghxxsshqyhhcjyxglhzxcxnhekdtgqxqypkdhentykcnymyyjmkqyyyjxzlthhqtbyqhxbmyhsqckwwyllhcyylnneqxqwmcfbdccmljggxdqktlxkknqcdgcjwyjjlyhhqyttnwchhxcxwherzjydjccdbqcdgdnyxzdhcqrxcbhztqcbxwgqwyybxhmbymykdyecmqkyaqyngyzslfnkkqgyssqyshngjctxkzycssbkyxhyylstycxqthysmnscpmmgcccccmnztasmgqzjhklosjylswtmqzyqkdzljqqyplzycztcqqpbbcjzclpkhqcyyxxdtdddsjcxffllchqxmjlwcjcxtspycxndtjshjwhdqqqckxyamylsjhmlalygxcyydmamdqmlmcznnyybzxkyflmcncmlhxrcjjhs")
			_T("ylnmtjggzgywjxsrxcwjgjqhqzdqjdcjjskjkgdzcgjjyjylxzxxcdqhhheslmhlfsbdjsyyshfyssczqlpbdrfnztzdkykhsccgkwtqzckmsynbcrxqbjyfaxpzzedzcjykbcjwhyjbqzzywnyszptdkzpfpbaztklqnhbbzptpptyzzybhnydcpzmmcycqmcjfzzdcmnlfpbplngqjtbttajzpzbbdnjkljqylnbzqhksjznggqstzkcxchpzsnbcgzkddzqanzgjkdrtlzldwjnjzlywtxndjzjhxnatncbgtzcsskmljpjytsnwxcfjwjjtkhtzplbhsnjssyjbhbjyzlstlsbjhdnwqpslmmfbjdwajyzccjtbnnnzwxxcdslqgdsdpdzgjtqqpsqlyyjzlgyhsdlctcbjtktyczjtqkbsjlgnnzdncsgpynjzjjyyknhrpwszxmtncszzyshbyhyzaxywkcjtllckjjtjhgcssxyqyczbynnlwqcglzgjgqyqcczssbcrbcskydznxjsqgxssjmecnstjtpbdlthzwxqwqczexnqczgwesgssbybstscslccgbfsdqnzlccglllzghzcthcnmjgyzazcmsksstzmmzckbjygqljyjppldxrkzyxccsnhshhdznlzhzjjcddcbcjxlbfqbczztpqdnnxljcthqzjgylklszzpcjdscqjhjqkdxgpbajynnsmjtzdxlcjyryynhjbngzjkmjxltbsllrzpylssznxjhllhyllqqzqlsymrcncxsljmlzltzldwdjjllnzggqxppskyggggbfzbdkmwggcxmcgdxjmcjsdycabxjdlnbcddygskydqdxdjjyxhsaqazdzfslqxxjnqzylblxxwxqqzbjzlfbblylwdsljhxjyzjwtdjcyfqzqzzdzsxzzqlzcdzfxhwspynpqzmlpplffxjjnzzylsjnyqzfpfzgsywjjjhrdjzzxtxxglghtdxcskyswmmtc")
			_T("wybazbjkshfhgcxmhfqhyxxyzftsjyzbxyxpzlchmzmbxhzzssyfdmncwdabazlxktcshhxkxjjzjsthygxsxyyhhhjwxkzxssbzzwhhhcwtzzzpjxsyxqqjgzyzawllcwxznxgyxyhfmkhydwsqmnjnaycyspmjkgwcqhylajgmzxhmmcnzhbhxclxdjpltxyjkdyylttxfqzhyxxsjbjnayrsmxyplckdnyhlxrlnllstycyyqygzhhsccsmcctzcxhyqfpyyrpbflfqnntszlljmhwtcjqyzwtlnmlmdwmbzzsnzrbpdddlqjjbxtcsnzqqygwcsxfwzlxccrszdzmcyggdyqsgtnnnlsmymmsyhfbjdgyxccpshxczcsbsjyygjmpbwaffyfnxhydxzylremzgzzyndsznlljcsqfnxxkptxzgxjjgbmyyssnbtylbnlhbfzdcyfbmgqrrmzszxysjtznnydzzcdgnjafjbdknzblczszpsgcycjszlmnrznbzzldlnllysxsqzqlcxzlsgkbrxbrbzcycxzjzeeyfgklzlnyhgzcgzlfjhgtgwkraajyzkzqtsshjjxdzyznynnzyrzdqqhgjzxsszbtkjbbfrtjxllfqwjgclqtymblpzdxtzagbdhzzrbgjhwnjtjxlkscfsmwlldcysjtxkzscfwjlbnntzlljzllqblcqmqqcgcdfpbphzczjlpyyghdtgwdxfczqyyyqysrclqzfklzzzgffcqnwglhjycjjczlqzzyjbjzzbpdcsnnjgxdqnknlznnnnpsntsdyfwwdjzjysxyyczcyhzwbbyhxrylybhkjksfxtjjmmchhlltnyymsxxyzpdjjycsycwmdjjkqyrhllngpngtlyycljnnnxjyzfnmlrgjjtyzbsyzmsjyjhgfzqmsyxrszcytlrtqzsstkxgqkgsptgxdnjsgcqcqhmxggztqydjjznlbznxqlhyqgggthqscbyhjhhkyygkggc")
			_T("mjdzllcclxqsftgjslllmlcskctbljszszmmnytpzsxqhjcnnqnyexzqzcpshkzzyzxxdfgmwqrllqxrfztlystctmjcsjjthjnxtnrztzfqrhcgllgcnnnnjdnlnnytsjtlnyxsszxcgjzyqpylfhdjsbbdczgjjjqzjqdybssllcmyttmqnbhjqmnygjyeqyqmzgcjkpdcnmyzgqllslnclmholzgdylfzslncnzlylzcjeshnyllnxnjxlyjyyyxnbcljsswcqqnnyllzldjnllzllbnylnqchxyyqoxccqkyjxxxyklksxeyqhcqkkkkcsnyxxyqxygwtjohthxpxxhsnlcykychzzcbwqbbwjqcscszsslcylgddsjzmmymcytsdsxxscjpqqsqylyfzychdjynywcbtjsydchcyddjlbdjjsodzyqyskkyxdhhgqjyohdyxwgmmmazdybbbppbcmnnpnjzsmtxerxjmhqdntpjdcbsnmssythjtslmltrcplzszmlqdsdmjmqpnqdxcfrnnfsdqqyxhyaykqyddlqyyysszbydslntfgtzqbzmchdhczcwfdxtmqqsphqwwxsrgjcwnntzcqmgwqjrjhtqjbbgwzfxjhnqfxxqywyyhyscdydhhqmrmtmwctbszppzzglmzfollcfwhmmsjzttdhlmyffytzzgzyskjjxqyjzqbhmbzclyghgfmshpcfzsnclpbqsnjyzslxxfpmtyjygbxlldlxpzjyzjyhhzcywhjylsjexfszzywxkzjlnadymlymqjpwxxhxsktqjezrpxxzghmhwqpwqlyjjqjjzszcnhjlchhnxjlqwzjhbmzyxbdhhypylhlhlgfwlcfyytlhjjcwmscpxstkpnhjxsntyxxtestjctlsslstdlllwwyhdnrjzsfgxssyczykwhtdhwjglhtzdqdjzxxqgghltzphcsqfclnjtclzpfstpdynylgmjllycqhynspchylhqyqtmzym")
			_T("bywrfqykjsyslzdnjmpxyyssrhzjnyqtqdfzbwwdwwrxcwggyhxmkmyyyhmxmzhnksepmlqqmtcwctmxmxjpjjhfxyyzsjzhtybmstsyjznqjnytlhynbyqclcycnzwsmylknjxlggnnpjgtysylymzskttwlgsmzsylmpwlcwxwqcssyzsyxyrhssntsrwpccpwcmhdhhxzdzyfjhgzttsbjhgyglzysmyclllxbtyxhbbzjkssdmalhhycfygmqypjyjqxjllljgclzgqlycjcctotyxmtmshllwlqfxymzmklpszzcxhkjyclctyjcyhxsgyxnnxlzwpyjpxhjwpjpwxqqxlxsdhmrslzzydwdtcxknstzshbsccstplwsscjchjlcgchssphylhfhhxjsxallnylmzdhzxylsxlmzykcldyahlcmddyspjtqjzlngjfsjshctsdszlblmssmnyymjqbjhrzwtyydchjljapzwbgqxbkfnbjdllllyylsjydwhxpsbcmljpscgbhxlqhyrljxyswxhhzlldfhlnnymjljyflyjycdrjlfsyzfsllcqyqfgqyhnszlylmdtdjcnhbzllnwlqxygyyhbmgdhxxnhlzzjzxczzzcyqzfngwpylcpkpykpmclgkdgxzgxwqbdxzzkzfbddlzxjtpjpttbythzzdwslcpnhsltjxxqlhyxxxywzyswttzkhlxzxzpyhgzhknfsyhntjrnxfjcpjztwhplshfcrhnslxxjxxyhzqdxqwnnhyhmjdbflkhcxcwhjfyjcfpqcxqxzyyyjygrpynscsnnnnchkzdyhflxxhjjbyzwttxnncyjjymswyxqrmhxzwfqsylznggbhyxnnbwttcsybhxxwxyhhxyxnknyxmlywrnnqlxbbcljsylfsytjzyhyzawlhorjmnsczjxxxyxchcyqryxqzddsjfslyltsffyxlmtyjmnnyyyxltzcsxqclhzxlwyxzhnnlrxkxjcd")
			_T("yhlbrlmbrdlaxksnlljlyxxlynrylcjtgncmtlzllcyzlpzpzyawnjjfybdyyzsepckzzqdqpbpsjpdyttbdbbbyndycncpjmtmlrmfmmrwyfbsjgygsmdqqqztxmkqwgxllpjgzbqrdjjjfpkjkcxbljmswldtsjxldlppbxcwkcqqbfqbccajzgmykbhyhhzykndqzybpjnspxthlfpnsygyjdbgxnhhjhzjhstrstldxskzysybmxjlxyslbzyslzxjhfybqnbylljqkygzmcyzzymccslnlhzhwfwyxzmwyxtynxjhbyymcysbmhysmydyshnyzchmjjmzcaahcbjbbhblytylsxsnxgjdhkxxtxxnbhnmlngsltxmrhnlxqqxmzllyswqgdlbjhdcgjyqyymhwfmjybbbyjyjwjmdpwhxqldyapdfxxbcgjspckrssyzjmslbzzjfljjjlgxzgyxyxlszqkxbexyxhgcxbpndyhwectwwcjmbtxchxyqqllxflyxlljlssnwdbzcmyjclwswdczpchqekcqbwlcgydblqppqzqfnqdjhymmcxtxdrmzwrhxcjzylqxdyynhyyhrslnrsywwjjymtltllgtqcjzyabtckzcjyccqlysqxalmzynywlwdnzxqdllqshgpjfjljnjabcqzdjgthhsstnyjfbswzlxjxrhgldlzrlzqzgsllllzlymxxgdzhgbdphzpbrlwnjqbpfdwonnnhlypcnjccndmbcpbzzncyqxldomzblzwpdwyygdstthcsqsccrsssyslfybnntyjszdfndpdhtqzmbqlxlcmyffgtjjqwftmnpjwdnlbzcmmcngbdzlqlpnfhyymjylsdchdcjwjcctljcldtljjcbddpndsszycndbjlggjzxsxnlycybjjxxcbylzcfzppgkcxqdzfztjjfjdjxzbnzyjqctyjwhdyczhymdjxttmpxsplzcdwslshxypzgtfmlcjtacbbmgde")
			_T("wycyzxdszjyhflystygwhkjyylsjcxgywjcbllcsnddbtzbsclyzczzssqdllmjyyhfllqllxfdyhabxggnywyypllsdldllbjcyxjznlhljdxyyqytdlllbngpfdfbbqbzzmdpjhgclgmjjpgaehhbwcqxajhhhzchxyphjaxhlphjpgpzjqcqzgjjzzgzdmqyybzzphyhybwhazyjhykfgdpfqsdlzmljxjpgalxzdaglmdgxmmzqwtxdxxpfdmmssympfmdmmkxksyzyshdzkjsysmmzzzmdydyzzczxbmlstmdyemxckjmztyymzmzzmsshhdccjewxxkljsthwlsqlyjzllsjssdppmhnlgjczyhmxxhgncjmdhxtkgrmxfwmckmwkdcksxqmmmszzydkmsclcmpcjmhrpxqpzdsslcxkyxtwlkjyahzjgzjwcjnxyhmmbmlgjxmhlmlgmxctkzmjlyscjsyszhsyjzjcdajzhbsdqjzgwtkqxfkdmsdjlfmnhkzqkjfeypzyszcdpynffmzqykttdzzefmzlbnpplplpbpszalltnlkckqzkgenjlwalkxydpxnhsxqnwqnkxqclhyxxmlnccwlymqyckynnlcjnszkpyzkcqzqljbdmdjhlasqlbydwqlwdgbqcryddztjybkbwszdxdtnpjdtcnqnfxqqmgnseclstbhpwslctxxlpwydzklnqgzcqapllkqcylbqmqczqcnjslqzdjxlddhpzqdljjxzqdjyzhhzlkcjqdwjppypqakjyrmpzbnmcxkllzllfqpylllmbsglzysslrsysqtmxyxzqzbscnysyztffmzzsmzqhzssccmlyxwtpzgxzjgzgsjzgkddhtqggzllbjdzlsbzhyxyzhzfywxytymsdnzzyjgtcmtnxqyxjscxhslnndlrytzlryylxqhtxsrtzcgyxbnqqzfhykmzjbzymkbpnlyzpblmcnqyzzzsjztjctzhhyzzjrdyzh")
			_T("nfxklfzslkgjtctssyllgzrzbbjzzklpkbczysnnyxbjfbnjzzxcdwlzyjxzzdjjgggrsnjkmsmzjlsjywqsnyhqjsxpjztnlsnshrnynjtwchglbnrjlzxwjqxqkysjycztlqzybbybyzjqdwgyzcytjcjxckcwdkkzxsnkdnywwyyjqyytlytdjlxwkcjnklccpzcqqdzzqlcsfqchqqgssmjzzllbjjzysjhtsjdysjqjpdszcdchjkjzzlpycgmzndjxbsjzzsyzyhgxcpbjydssxdzncglqmbtsfcbfdzdlznfgfjgfsmpnjqlnblgqcyyxbqgdjjqsrfkztjdhczklbsdzcfytplljgjhtxzcsszzxstjygkgckgynqxjplzbbbgcgyjzgczqszlbjlsjfzgkqqjcgycjbzqtldxrjnbsxxpzshszycfwdsjjhxmfczpfzhqhqmqnknlyhtycgfrzgnqxcgpdlbzcsczqlljblhbdcypscppdymzzxgyhckcpzjgslzlnscnsldlxbmsdlddfjmkdqdhslzxlsznpqpgjdlybdskgqlbzlnlkyyhzttmcjnqtzzfszqktlljtyyllnllqyzqlbdzlslyyzxmdfszsnxlxznczqnbbwskrfbcylctnblgjpmczzlstlxshtzcyzlzbnfmqnlxflcjlyljqcbclzjgnsstbrmhxzhjzclxfnbgxgtqncztmsfzkjmssncljkbhszjntnlzdntlmmjxgzjyjczxyhyhwrwwqnztnfjscpyshzjfyrdjsfscjzbjfzqzchzlxfxsbzqlzsgyftzdcszxzjbjpszkjrhxjzcgbjkhcggtxkjqglxbxfgtrtylxqxhdtsjxhjzjjcmzlcqsbtxwqgxtxxhxftsdkfjhzyjfjxnzldlllcqsqqzqwqxswqtwgwbzcgcllqzbclmqjtzgzyzxljfrmyzflxnsnxxjkxrmjdzdmmyxbsqbhgzmwfwygmjlzbyytgzyccd")
			_T("jyzxsngnyjyznbgpzjcqsyxsxrtfyzgrhztxszzthcbfclsyxzlzqmzlmplmxzjssfsbysmzqhxxnxrxhqzzzsslyflczjrcrxhhzxqndshxsjjhqcjjbcynsysxjbqjpxzqplmlxzkyxlxcnlcycxxzzlxdlllmjyhzxhyjwkjrwyhcpsgnrzlfzwfzznsxgxflzsxzzzbfcsyjdbrjkrdhhjxjljjtgxjxxstjtjxlyxqfcsgswmsbctlqzzwlzzkxjmltmjyhsddbxgzhdlbmyjfrzfcgclyjbpmlysmsxlszjqqhjzfxgfqfqbphngyyqxgztnqwyltlgwgwwhnlfmfgzjmgmgbgtjflyzzgzyzaflsspmlbflcwbjztljjmzlpjjlymqtmyyyfbgygqzglyzdxqyxrqqqhsxyyqxygjtyxfsfsllgnqcygycwfhcccfxpylypllzqxxxxxqqhhsshjzcftsczjxspzwhhhhhapylqnlpqafyhxdylnkmzqgggddesrenzltzgchyppcsqjjhclljtolnjpzljlhymhezdydsqycddhgznndzclzywllznteydgnlhslpjjbdgwxpcnntycklkclwkllcasstknzdnnjttlyyzssysszzryljqkcgdhhyrxrzydgrgcwcgzqffbppjfzynakrgywyjpqxxfkjtszzxswzddfbbqtbgtzkznpzfpzxzpjszbmqhkyyxyldkljnypkyghgdzjxxeaxpnznctzcmxcxmmjxnkszqnmnlwbwwqjjyhclstmcsxnjcxxtpcnfdtnnpglllzcjlspblpgjcdtnjjlyarscffjfqwdpgzdwmrzzcgodaxnssnyzrestyjwjyjdbcfxnmwttbqlwstszgybljpxglbnclgpcbjftmxzljylzxcltpnclcgxtfzjshcrxsfysgdkntlbyjcyjllstgqcbxnhzxbxklylhzlqzlnzcqwgzlgzjncjgcmnzzgjdzxtzjxy")
			_T("cyycxxjyyxjjxsssjstsstdppghtcsxwzdcsynptfbchfbblzjclzzdbxgcjlhpxnfzflsyltnwbmnjhszbmdnbcysccldnycndqlyjjhmqllcsgljjsyfpyyccyltjantjjpwycmmgqyysxdxqmzhszxbftwwzqswqrfkjlzjqqyfbrxjhhfwjgzyqacmyfrhcyybynwlpexcczsyyrlttdmqlrkmpbgmyyjprkznbbsqyxbhyzdjdnghpmfsgbwfzmfqmmbzmzdcgjlnnnxyqgmlrygqccyxzlwdkcjcggmcjjfyzzjhycfrrcmtznzxhkqgdjxccjeascrjthpljlrzdjrbcqhjdnrhylyqjsymhzydwcdfryhbbydtssccwbxglpzmlzjdqsscfjmmxjcxjytycghycjwynsxlfemwjnmkllswtxhyyyncmmcyjdqdjzglljwjnkhpzggflccsczmcbltbhbqjxqdjpdjztghglfjawbzyzjltstdhjhctcbchflqmpwdshyytqwcnntjtlnnmnndyyyxsqkxwyyflxxnzwcxypmaelyhgjwzzjbrxxaqjfllpfhhhytzzxsgqjmhspgdzqwbwpjhzjdyjcqwxkthxsqlzyymysdzgnqckknjlwpnsyscsyzlnmhqsyljxbcxtlhzqzpcycykpppnsxfyzjjrcemhszmnxlxglrwgcstlrsxbygbzgnxcnlnjlclynymdxwtzpalcxpqjcjwtcyyjlblxbzlqmyljbghdslssdmxmbdczsxyhamlczcpjmcnhjyjnsykchskqmczqdllkablwjqsfmocdxjrrlyqchjmybyqlrhetfjzfrfksryxfjdwtsxxywsqjyslyxwjhsdlxyyxhbhawhwjcxlmyljcsqlkydttxbzslfdxgxsjkhsxxybssxdpwncmrptqzczenygcxqfjxkjbdmljzmqqxnoxslyxxlylljdzptymhbfsttqqwlhsgynlzzalzxcl")
			_T("htwrrqhlstmypyxjjxmnsjnnbryxyjllyqyltwylqyfmlkljdnlltfzwkzhljmlhljnljnnlqxylmbhhlnlzxqchxcfxxlhyhjjgbyzzkbxscqdjqdsndzsygzhhmgsxcsymxfepcqwwrbpyyjqryqcyjhqqzyhmwffhgzfrjfcdbxntqyzpcyhhjlfrzgpbxzdbbgrqstlgdgylcqmgchhmfywlzyxkjlypjhsywmqqggzmnzjnsqxlqsyjtcbehsxfszfxzwfllbcyyjdytdthwzsfjmqqyjlmqsxlldttkghybfpwdyysqqrnqwlgwdebzwcyygcnlkjxtmxmyjsxhybrwfymwfrxyymxysctzztfykmldhqdlgyjnlcryjtlpsxxxywlsbrrjwxhqybhtydnhhxmmywytycnnmnssccdalwztcpqpyjllqzyjswjwzzmmglmxclmxnzmxmzsqtzppjqblpgxjzhfljjhycjsrxwcxsncdlxsyjdcqzxslqyclzxlzzxmxqrjmhrhzjbhmfljlmlclqnldxzlllfyprgjynxcqqdcmqjzzxhnpnxzmemmsxykynlxsxtljxyhwdcwdzhqyybgybcyscfgfsjnzdrzzxqxrzrqjjymcanhrjtldbpyzbstjhxxzypbdwfgzzrpymnnkxcqbyxnbnfyckrjjcmjegrzgyclnnzdnkknsjkcljspgyyclqqjybzssqlllkjftbgtylcccdblsppfylgydtzjqjzgkntsfcxbdkdxxhybbfytyhbclnnytgdhryrnjsbtcsnyjqhklllzslydxxwbcjqsbxnpjzjzjdzfbxxbrmladhcsnclbjdstblprznswsbxbcllxxlzdnzsjpynyxxyftnnfbhjjjgbygjpmmmmsszljmtlyzjxswxtyledqpjmpgqzjgdjlqjwjqllsdgjgygmscljjxdtygjqjjjcjzcjgdzdshqgzjggcjhqxsnjlzzbxhsgzxcxyljx")
			_T("yxyydfqqjhjfxdhctxjyrxysqtjxyefyyssyxjxncyzxfxcsxszxyyschshxzzzgzzzgfjdldylnpzgsjaztyqzpbxcbdztzczyxxyhhscjshcggqhjhgxhsctmzmehyxgebtclzkkwytjzrslekestdbcyhqqsayxcjxwwgsphjszsdncsjkqcxswxfctynydpccczjqtcwjqjzzzqzljzhlsbhpydxpsxshhezdxfptjqyzcxhyaxncfzyyhxgnqmywntzsjbnhhgymxmxqcnssbcqsjyxxtyyhybcqlmmszmjzzllcogxzaajzyhjmchhcxzsxsdznleyjjzjbhzwjzsqtzpsxzzdsqjjjlnyazphhyysrnqzthzhnyjyjhdzxzlswclybzyecwcycrylchzhzydzydyjdfrjjhtrsqtxyxjrjhojynxelxsfsfjzghpzsxzszdzcqzbyyklsgsjhczshdgqgxyzgxchxzjwyqwgyhksseqzzndzfkwyssdclzstsymcdhjxxyweyxczaydmpxmdsxybsqmjmzjmtjqlpjyqzcgqhyjhhhqxhlhdldjqcfdwbsxfzzyyschtytyjbhecxhjkgqfxbhyzjfxhwhbdzfyzbchpnpgdydmsxhkhhmamlnbyjtmpxejmcthqbzyfcgtyhwphftgzzezsbzegpbmdskftycmhbllhgpzjxzjgzjyxzsbbqsczzlzscstpgxmjsfdcczjzdjxsybzlfcjsazfgszlwbczzzbyztzynswyjgxzbdsynxlgzbzfygczxbzhzftpbgzgejbstgkdmfhyzzjhzllzzgjqzlsfdjsscbzgpdlfzfzszyzyzsygcxsnxxchczxtzzljfzgqsqqxcjqccccdjcdszzyqjccgxztdlgscxzsyjjqtcclqdqztqchqqyzynzzzpbkhdjfcjfztypqyqttynlmbdktjcpqzjdzfpjsbnjlgyjdxjdcqkzgqkxclbzjtcjdqbxdjjjst")
			_T("cxnxbxqmslyjcxntjqwwcjjnjjlllhjcwqtbzqqczczpzzdzyddcyzdzccjgtjfzdprntctjdcxtqzdtjnplzbcllctdsxkjzqdmzlbznbtjdcxfczdbczjjltqqpldckztbbzjcqdcjwynllzlzccdwllxwzlxrxntqjczxkjlsgdnqtddglnlajjtnnynkqlldzntdnycygjwyxdxfrsqstcdenqmrrqzhhqhdldazfkapbggpzrebzzykyqspeqjjglkqzzzjlysyhyzwfqznlzzlzhwcgkypqgnpgblplrrjyxcccgyhsfzfwbzywtgzxyljczwhncjzplfflgskhyjdeyxhlpllllcygxdrzelrhgklzzyhzlyqszzjzqljzflnbhgwlczcfjwspyxzlzlxgccpzbllcxbbbbnbbcbbcrnnzccnrbbnnldcgqyyqxygmqzwnzytyjhyfwtehznjywlccntzyjjcdedpwdztstnjhtymbjnyjzlxtsstphndjxxbyxqtzqddtjtdyztgwscszqflshlnzbcjbhdlyzjyckwtydylbnydsdsycctyszyyebgexhqddwnygyclxtdcystqnygzascsszzdzlcclzrqxyywljsbymxshzdembbllyyllytdqyshymrqnkfkbfxnnsbychxbwjyhtqbpbsbwdzylkgzskyghqzjxhxjxgnljkzlyycdxlfwfghljgjybxblybxqpqgntzplncybxdjyqydymrbeyjyyhkxxstmxrczzjwxyhybmcflyzhqyzfwxdbxbcwzmslpdmyckfmzklzcyqycclhxfzlydqzpzygyjyzmdxtzfnnyttqtzhgsfcdmlccytzxjcytjmkslpzhysnwllytpzctzccktxdhxxtqcyfksmqccyyazhtjplylzlyjbjxtfnyljyynrxcylmmnxjsmybcsysslzylljjgyldzdlqhfzzblfndsqkczfyhhgqmjdsxycttxnqnjpy")
			_T("ybfcjtyyfbnxejdgyqbjrcnfyyqpghyjsyzngrhtknlnndzntsmgklbygbpyszbydjzsstjztsxzbhbscsbzczptqfzlqflypybbjgszmnxdjmtsyskkbjtxhjcegbsmjyjzcstmljyxrczqscxxqpyzhmkyxxxjcljyrmyygadyskqlnadhrskqxzxztcggzdlmlwxybwsyctbhjhcfcwzsxwwtgzlxqshnyczjxemplsrcgltnzntlzjcyjgdtclglbllqpjmzpapxyzlaktkdwczzbncctdqqzqyjgmcdxltgcszlmlhbglkznnwzndxnhlnmkydlgxdtwcfrjerctzhydxykxhwfzcqshknmqqhzhhymjdjskhxzjzbzzxympajnmctbxlsxlzynwrtsqgscbptbsgzwyhtlkssswhzzlyytnxjgmjrnsnnnnlskztxgxlsammlbwldqhylakqcqctmycfjbslxclzjclxxknbnnzlhjphqplsxsckslnhpsfqcytxjjzljldtzjjzdlydjntptnndskjfsljhylzqqzlbthydgdjfdbyadxdzhzjnthqbyknxjjqczmlljzkspldsclbblnnlelxjlbjycxjxgcnlcqplzlznjtsljgyzdzpltqcssfdmnycxgbtjdcznbgbqyqjwgkfhtnbyqzqgbkpbbyzmtjdytblsqmbsxtbnpdxklemyycjynzdtldykzzxtdxhqshygmzsjycctayrzlpwltlkxslzcggexclfxlkjrtlqjaqzncmbqdkkcxglczjzxjhptdjjmzqykqsecqzdshhadmlzfmmzbgntjnnlhbyjbrbtmlbyjdzxlcjlpldlpcqdhlhzlycblcxccjadqlmzmmsshmybhbnkkbhrsxxjmxmdznnpklbbrhgghfchgmnklltsyyycqlcskymyehywxnxqywbawykqldnntndkhqcgdqktgpkxhcpdhtwnmssyhbwcrwxhjmkmzngwtml")
			_T("kfghkjyldyycxwhyyclqhkqhtdqkhffldxqwytyydesbpkyrzpjfyyzjceqdzzdlattpbfjllcxdlmjsdxegwgsjqxcfbssszpdyzcxznyxppzydlyjccpltxlnxyzyrscyyytylwwndsahjsygyhgywwaxtjzdaxysrltdpssyxfnejdxyzhlxlllzhzsjnyqyqyxyjghzgjcyjchzlycdshhsgczyjscllnxzjjyyxnfsmwfpyllyllabmddhwzxjmcxztzpmlqchsfwzynctlndywlslxhymmylmbwwkyxyaddxylldjpybpwnxjmmmllhafdllaflbnhhbqqjqzjcqjjdjtffkmmmpythygdrjrddwrqjxnbysrmzdbyytbjhpymyjtjxaahggdqtmystqxkbtzbkjlxrbyqqhxmjjbdjntgtbxpgbktlgqxjjjcdhxqdwjlwrfmjgwqhcnrxswgbtgygbwhswdwrfhwytjjxxxjyzyslphyypyyxhydqpxshxyxgskqhywbdddpplcjlhqeewjgsyykdpplfjthkjltcyjhhjttpltzzcdlyhqkcjqysteeyhkyzyxxyysddjkllpymqyhqgxqhzrhbxpllnqydqhxsxxwgdqbshyllpjjjthyjkyphthyyktyezyenmdshlzrpqfbnfxzbsftlgxsjbswyysksflxlpplbbblnsfbfyzbsjssylpbbffffsscjdstjsxtryjcyffsyzyzbjtlctsbsdhrtjjbytcxyyeylycbnebjdsysyhgsjzbxbytfzwgenhhhthjhhxfwgcstbgxklstyymtmbyxjskzscdyjrcythxzfhmymcxlznsdjtxtxrycfyjsbsdyerxhljxbbdeynjghxgckgscymblxjmsznskgxfbnbbthfjyafxwxfbxmyfhdttcxzzpxrsywzdlybbktyqwqjbzypzjznjpzjlztfysbttslmptzrtdxqsjehbnylndxljsqmlhtx")
			_T("tjecxalzzspktlzkqqyfsyjywpcpqfhjhytqxzkrsgtksqczlptxcdyyzsslzslxlzmacpcqbzyxhbsxlzdltztjtylzjyytbzypltxjsjxhlbmytxcqrblzssfjzztnjytxmyjhlhpblcyxqjqqkzzscpzkswalqsplczzjsxgwwwygyatjbbctdkhqhkgtgpbkqyslbxbbckbmllndzstbklggqkqlzbkktfxrmdkbftpzfrtppmferqnxgjpzsstlbztpszqzsjdhljqlzbpmsmmsxlqqnhknblrddnhxdkddjcyyljfqgzlgsygmjqjkhbpmxyxlytqwlwjcpbmjxcyzydrjbhtdjyeqshtmgsfyplwhlzffnynnhxqhpltbqpfbjwjdbygpnxtbfzjgnnntjshxeawtzylltyqbwjpgxghnnkndjtmszsqynzggnwqtfhclssgmnnnnynzqqxncjdqgzdlfnykljcjllzlmzznnnnsshthxjlzjbbhqjwwycrdhlyqqjbeyfsjhthnrnwjhwpslmssgzttygrqqwrnlalhmjtqjsmxqbjjzjqzyzkxbjqxbjxshzssfglxmxnxfghkzszggslcnnarjxhnlllmzxelglxydjytlfbkbpnlyzfbbhptgjkwetzhkjjxzxxglljlstgshjjyqlqzfkcgnndjsszfdbctwwseqfhqjbsaqtgypjlbxbmmywxgslzhglsgnyfljbyfdjfngsfmbyzhqffwjsyfyjjphzbyyzffwotjnlmftwlbzgyzqxcdjygzyyryzynyzwegazyhjjlzrthlrmgrjxzclnnnljjyhtbwjybxxbxjjtjteekhwslnnlbsfazpqqbdlqjjtyyqlyzkdksqjnejzldqcgjqnnjsncmrfqthtejmfctyhypymhydmjncfgyyxwshctxrljgjzhzcyyyjltkttntmjlzclzzayyoczlrlbszywjytsjyhbyshfjlykjxxtmzyyltxxyp")
			_T("slqyjzyzyypnhmymdyylblhlsyygqllnjjymsoycbzgdlyxylcqyxtszegxhzglhwbljheyxtwqmakbpqcgyshhegqcmwyywljyjhyyzlljjylhzyhmgsljljxcjjyclycjbcpzjzjmmwlcjlnqljjjlxyjmlszljqlycmmgcfmmfpqqmfxlqmcffqmmmmhnznfhhjgtthxkhslnchhyqzxtmmqdcydyxyqmyqylddcyaytazdcymdydlzfffmmycqcwzzmabtbyctdmndzggdftypcgqyttssffwbdttqssystwnjhjytsxxylbyyhhwhxgzxwznnqzjzjjqjccchykxbzszcnjtllcqxynjnckycynccqnxyewyczdcjycchyjlbtzyycqwlpgpyllgktltlgkgqbgychjxy");
		CString strTemp;

		int i;
		for (i = 0; i < wcslen(strName); i++)
		{
			WORD unicodeVal = (WORD)strName[i];

			if ( unicodeVal >= 0X4E00 && unicodeVal <= 0X9FA5 )           //unicode汉字编码范围
			{
				strTemp += wcsFiestLetterTable[unicodeVal - 0X4E00];
			}
			else                                            //非汉字保留
			{
				strTemp += strName[i];
			}
		}

		return  strTemp;
} 


// 得到新的政策代码
CString CDataProcess::GetNewPolicyCode(void)
{
	CString strRet(_T(""));
	srand((unsigned)GetTickCount());
	int n = random(1000);

	CTime t = CTime::GetCurrentTime();
	strRet.Format(_T("HI%ld%03d"),t.GetTime(),n);

	return strRet;
}


// 加载城市代码
bool CDataProcess::LoadCityCodes(void)
{
	CMarkup xml;
	if (!xml.Load(GetExePath() + _T("CityCodes.xml")))
	{
		return false;
	}
	if (!xml.FindElem(_T("CityCodes")))
	{
		return false;
	}
	
	if (xml.IntoElem())
	{
		while (xml.FindElem(_T("cityinfo")))
		{
			xml.IntoElem();
			CString strName,strCode;
			if (xml.FindElem(_T("name")))
			{
				strName = xml.GetData();
			}
			if (xml.FindElem(_T("code")))
			{
				strCode = xml.GetData();
			}

			m_mapCityCodes.insert(pair<CString,CString>(strCode,strName));

			xml.OutOfElem();
		}
	}

	return true;
}



// 切换代理
int CDataProcess::ChangeProxy(WinHttpClient& httpClient)
{
	CStringW strWLog;
	wstring strwip = theApp.GetValidIP();
	httpClient.SetProxy(strwip);
	//strWLog.Format(L"切换IP:%s\r\n",strwip.c_str());
	//OutputDebugStringW(strWLog);

	return 0;

//	CStringA strIP;
//
//_find:
//	OutputDebugString(_T("\r\n开始查找可用IP\r\n"));
//
//
//	CStringA strLog;
//
//	//	WinHttpClient http(L"http://www.baidu.com");
//	WinHttpClient http(L"https://passport.china-sss.com/Default/LoginFrame");
//
//	wstring strHeaderBase = L"Accept: text/html";
//	strHeaderBase += L"Accept-Language: zh-cn\r\n";
//	strHeaderBase += L"User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET4.0C; .NET4.0E)\r\n";
//	strHeaderBase += L"Content-Type: application/x-www-form-urlencoded\r\n";
//
//	if (DBR_Succ != CDbCenter::GetInstance()->QueryProxyIP(strIP))
//	{
//		OutputDebugStringA("\r\n没有查找到代理IP\r\n");
//	}
//
//	http.SetTimeouts(0,6000U,3000U,3000U);
//	http.SetProxy(wstring(CStrA2CStrW(strIP).GetBuffer(0)));
//
//	strLog.Format("\r\n测试IP:%s\r\n",strIP);
//	OutputDebugStringA(strLog);
//
//	http.SendHttpRequest(L"GET");
//	if (0 != http.GetResponseStatusCode().compare(L"200"))
//	{
//		strLog.Format("\r\n无效IP:%s\r\n",strIP);
//		OutputDebugStringA(strLog);
//		CDbCenter::GetInstance()->UpdateProxyUsedCount(strIP,2);
//	//	theApp.AddLog(CStrA2CStrT(strLog));
//		goto _find;
//	}
//
//	httpClient.SetProxy(wstring(CStrA2CStrW(strIP).GetBuffer(0)));
//	CDbCenter::GetInstance()->UpdateProxyUsedCount(strIP,1);
//	strLog.Format("切换IP:%s\r\n",strIP);
//	OutputDebugStringA(strLog);
////	theApp.AddLog(CStrA2CStrT(strLog));
//
//	return 0;
}

void CDataProcess::DateStrToCTime(CString strDate, CTime& t)
{
	CString strTmp;
	strTmp = strDate.Left(4);
	int iYear = _tstoi(strTmp.GetBuffer(4));
	strTmp.ReleaseBuffer();

	strTmp = strDate.Mid(5, 2);
	int iMonth = _tstoi(strTmp.GetBuffer(2));
	strTmp.ReleaseBuffer();

	strTmp = strDate.Right(2);
	int iDay = _tstoi(strTmp.GetBuffer(2));
	strTmp.ReleaseBuffer();

	CTime tm(iYear, iMonth, iDay, 0, 0, 0);
	t = tm;
}

BOOL CDataProcess::__FindKeyInMap(std::map<CString, int> & mp, CString & strKey)
{
	std::map<CString, int>::iterator itMap;
	CString strKey2 = strKey.Right(3)+strKey.Left(3);
	for (itMap = mp.begin(); itMap != mp.end();itMap++)
	{
		if(0 == strKey.CompareNoCase(itMap->first) || 0 == strKey2.CompareNoCase(itMap->first))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CDataProcess::GenAirLine(list<PTAirLineDateInfo>& listAirDate)
{
	list<PTAirLineDateInfo>::iterator it;  
	PTAirLineDateInfo pInfo = NULL;
	std::map<CString, int> airLineMap;
	airLineMap.clear();
	int i = 0;
	for (it = listAirDate.begin(); it != listAirDate.end();it++)  
	{  
		pInfo = *it;
		CString strKey = pInfo->_airInfo.strFromCityCode+pInfo->_airInfo.strToCityCode;
		BOOL bFind = __FindKeyInMap(airLineMap, strKey);
		if (!bFind)
		{
			airLineMap.insert(pair<CString, int>(strKey, i));
			i++;
		}
	}

	TRACE(_T("\n-------------------total lines:%d, airLine:%d\n"), listAirDate.size(), airLineMap.size());
	std::map<CString, int>::iterator itMap;
	i = 1;
	for (itMap = airLineMap.begin(); itMap != airLineMap.end();itMap++)
	{
		CString strKey = itMap->first;
		TRACE(_T("\n%d=%s"), i, strKey);
		i++;
	}

	CString strPath = _T("D:\\sssAirlineDates.xml");
	CTime t = CTime(2014, 11, 15, 0, 0, 0);
	list<PTAirLineDateInfo> listAirDateData2;
	listAirDateData2.clear();
	for (itMap = airLineMap.begin(); itMap != airLineMap.end();itMap++)
	{
		CString strKey = itMap->first;
		PTAirLineDateInfo pLine = new TAirLineDateInfo;
		pLine->tStart = t;
		pLine->tEnd = t;
		pLine->_airInfo.strFromCityCode = strKey.Left(3);
		pLine->_airInfo.strToCityCode = strKey.Right(3);

		pLine->_airInfo.strFromCity = GetCityNameByCode(pLine->_airInfo.strFromCityCode);
		pLine->_airInfo.strToCity = GetCityNameByCode(pLine->_airInfo.strToCityCode);
		listAirDateData2.push_back(pLine);
	}
	SaveAirlineDateToXml(listAirDateData2, strPath);
}

void CDataProcess::__GenMinHangPriceXml()
{
	CString strAirlineIni = GetExePath() + _T("airLineCfg.ini");
	CString strPriceIni = GetExePath() + _T("minhangPrice.ini");
	UINT uMax = GetPrivateProfileInt(_T("count"), _T("max"), 0, strAirlineIni);
	std::list<CString> airlineList;
	airlineList.clear();
	TCHAR szTemp[256] = {0};
	CString strKey;
	for (int i = 0; i < uMax; i++)
	{
		CString strCity;
		strKey.Format(_T("%d"), i+1);
		GetPrivateProfileString(_T("line"), strKey, _T(""), szTemp, 256, strAirlineIni);
		strCity.Format(_T("%s"), szTemp);
		airlineList.push_back(strCity);
	}
	TRACE(_T("\n load %d airlines\n"), airlineList.size());
	std::list<CString>::iterator it;
	m_minHangPriceMap.clear();
	for (it = airlineList.begin(); it != airlineList.end(); it++)
	{
		CString str = *it;
		UINT uPrice = GetPrivateProfileInt(_T("price"), str, 0, strPriceIni);
		m_minHangPriceMap.insert(pair<CString, UINT>(str, uPrice));
	}
	TRACE(_T("\n load %d airline price pair\n"), m_minHangPriceMap.size());

	//save m_minHangPriceMap to xml
	CMarkup xml;
	CString strXmlFile = GetExePath() + _T("\\minHangPrice.xml");
	if (!xml.Load(strXmlFile))
	{
		xml.Load(_T(""),0);
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n"));
	}
	if (xml.FindElem(_T("AirLineInfo")))
	{
		xml.RemoveElem();
	}
	xml.AddElem(_T("AirLineInfo"));

	if (xml.IntoElem())
	{
		CString strTemp;
		std::map<CString, UINT>::iterator it;  
		for (it = m_minHangPriceMap.begin(); it != m_minHangPriceMap.end();it++)  
		{  
			CString str = it->first;
			UINT uPrice = it->second;
			xml.AddElem(_T("AirLine"));
			xml.AddChildElem(_T("name"), str);
			xml.AddChildElem(_T("price"), uPrice);
		}
	}
	xml.Save(strXmlFile);

}

//加载民航价格
BOOL CDataProcess::LoadMinHangPrice()
{
	CMarkup xml;
	CString strXmlFile = GetExePath() + _T("\minHangPrice.xml");
	if (!xml.Load(strXmlFile))
	{
		return FALSE;
	}
	if (!xml.FindElem(_T("AirLineInfo")))
	{
		return FALSE;
	}

	m_minHangPriceMap.clear();
	if (xml.IntoElem())
	{
		while (xml.FindElem(_T("AirLine")))
		{
			xml.IntoElem();
			CString str("");
			UINT uPrice = 0;
			if (xml.FindElem(_T("name")))
			{
				str = xml.GetData();
			}
			if (xml.FindElem(_T("price")))
			{
				CString strPrice = xml.GetData();
				uPrice = _tstoi(strPrice.GetBuffer(0));
			}
			m_minHangPriceMap.insert(pair<CString, UINT>(str, uPrice));

			xml.OutOfElem();
		}
	}

	return TRUE;
}
//得到航线的民航价格，不分始发，两个城市间的航线民航价格是固定的
UINT CDataProcess::GetMinHangPrice(std::map<CString, UINT> & priceMap, CString & strCity1Code, CString & strCity2Code)
{
	UINT uPrice = 0;
	UINT uPrice1 = 0;
	UINT uPrice2 = 0;

	CString strKey1 = strCity1Code + strCity2Code;
	CString strKey2 = strCity2Code + strCity1Code;
	std::map<CString, UINT>::iterator it;
	for (it = priceMap.begin(); it != priceMap.end(); it++)
	{
		CString str = it->first;
		if (0 == str.CompareNoCase(strKey1))
			uPrice1 = it->second;
		if (0 == str.CompareNoCase(strKey2))
			uPrice2 = it->second;
	}
#ifndef CEAIR_MOBILE_E
	//ASSERT((0 == uPrice1 && 0 != uPrice2) ||(0 == uPrice2 && 0 != uPrice1));
#endif
	uPrice = uPrice1;
	if (uPrice2 > uPrice1)
		uPrice = uPrice2;
	return uPrice;
}

CStringA CDataProcess::ConvertCtripTo9C(CStringA & straCode)
{
	if(0 == straCode.CompareNoCase("SIA"))
	{
		return "XIY";
	}
	else
		return straCode;
}