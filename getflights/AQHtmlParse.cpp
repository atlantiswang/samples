#include "StdAfx.h"
#include "AQHtmlParse.h"
#include "util.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int		CAQHtmlParse::m_iExtraAddPrice = 0;
CAQHtmlParse::CAQHtmlParse(void)
{
}


CAQHtmlParse::~CAQHtmlParse(void)
{
}

int CAQHtmlParse::ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight)
{
	TidyDoc doc = tidyCreate();
	tidySetCharEncoding(doc,"raw");
	tidyParseString(doc,strHtmlData.c_str());
	TidyNode tnRoot = tidyGetRoot(doc);

	CStringA straFromCode,straToCode,straFromDate,straToDate;
	TidyNode tnFrom,tnTo;
	if (FindNode(tnRoot,"id","OriCityCode",tnFrom))
	{
		straFromCode.Format("%s",GetAttValue(tnFrom,"value"));
	}
	if (FindNode(tnRoot,"id","DestCityCode",tnTo))
	{
		straToCode.Format("%s",GetAttValue(tnTo,"value"));
	}
	if (FindNode(tnRoot,"id","FLY_TIME",tnTo))
	{
		straFromDate.Format("%s",GetAttValue(tnTo,"value"));
	}
	if (FindNode(tnRoot,"id","RETURN_TIME",tnTo))
	{
		straToDate.Format("%s",GetAttValue(tnTo,"value"));
	}
	CStringA straContent;
	int nMinHangPrice = 0;
	if (FindNode(tnRoot,"id","goMinHang",tnTo))
	{
		straContent = GetNodeContent(doc,tnTo);
		nMinHangPrice = ParsePrice(straContent);
	}

	TidyNode tnSearchresult;
	if (FindNode(tnRoot,"id","goFlightsShow",tnSearchresult))
	{
		//循环解析航班,goFlightsShow下的每一个一级子节点即为一个航班
		TidyNode tnFlight;
		for ( tnFlight = tidyGetChild(tnSearchresult); tnFlight; tnFlight = tidyGetNext(tnFlight) )
		{
			TidyNode tnChild;
			int nIndex = 0;

			PT9CFlightInfo pInfo = new T9CFlightInfo;
			pInfo->straCompany = "9C";
			pInfo->straFromCityCode = straFromCode;
			pInfo->straToCityCode = straToCode;
			pInfo->straFromDate = straFromDate;
			pInfo->straToDate = straToDate;
			pInfo->nMinHangPrice = nMinHangPrice;

			for ( tnChild = tidyGetChild(tnFlight); tnChild; tnChild = tidyGetNext(tnChild) )
			{
				switch(nIndex)
				{
				case 0:
					{
						//航班号
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							pInfo->straFlightNo = straContent;
						}
					}
					break;
				case 1:
					{
						//出发时间
						pInfo->straFromTime = GetNodeContent(doc,tnChild);
					}
					break;
				case 2:
					{
						//到达时间
						pInfo->straToTime = GetNodeContent(doc,tnChild);
					}
					break;
				case 3:
					{
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							if (0 == straContent.Left(2).Compare("--"))
							{
								pInfo->nPrice1 = 0;
							}
							else
							{
								pInfo->nPrice1 = ParsePrice(straContent);
							}
						}
					}
					break;
				case 4:
					{
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							if (0 == straContent.Left(2).Compare("--"))
							{
								pInfo->nPrice2 = 0;
							}
							else
							{
								pInfo->nPrice2 = ParsePrice(straContent);
							}
						}
					}
					break;
				case 5:
					{
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							if (0 == straContent.Left(2).Compare("--"))
							{
								pInfo->nPrice3 = 0;
							}
							else
							{
								pInfo->nPrice3 = ParsePrice(straContent);
							}
						}
					}
					break;
				}

				nIndex++;
			}

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			listFlight.push_back(pInfo);
		}
	}

	tidyRelease(doc);	

	return 0;
}

int CAQHtmlParse::GetMinPrice(int nPrice1, int nPrice2, int nPrice3)
{
	int nMinPrice = 0;
	if (nPrice1 != 0)
	{
		nMinPrice = nPrice1;
	}
	if (nPrice2 != 0)
	{
		if (nMinPrice == 0 || nMinPrice > nPrice2)
		{
			nMinPrice = nPrice2;
		}
	}
	if (nPrice3 != 0)
	{
		if (nMinPrice == 0 || nMinPrice > nPrice3)
		{
			nMinPrice = nPrice3;
		}
	}

	return nMinPrice;
}

int CAQHtmlParse::ParsePrice(CStringA stra)
{
	int nPrice = 0;
	int n = sizeof('￥');
	int nPos = stra.Find("￥");
	if (nPos >= 0)
	{
	//	stra = stra.Left(stra)
		int nLength = stra.GetLength();
	//	stra = "民航公布价：￥1260";
	//	nLength = stra.GetLength();
		CStringA str = stra.Mid(nPos + 2,nLength - nPos - n);
		nPrice = atoi(str.GetBuffer(0));
	}

	return nPrice;
}
//抓取春秋新网站航班数据
int CAQHtmlParse::ParseJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight,
	UINT uMinHangPrice, const CTime & tSel9Start, const CTime & tSel9End, BOOL bIgnoreP4Ticket, BOOL bIgnoreP5Ticket, BOOL bSelSpecialPriceTicket, int nP4SpecialPrice)
{
	int nCount = 0;
	Json::Reader reader;
	Json::Value jRoot;
	CTime tCur = CTime::GetCurrentTime();
	listFlight.clear();
	if (reader.parse(strHtmlData,jRoot))
	{
		if(jRoot.isNull() || !jRoot.isObject())
			return 0;
//		Json::Value fligtsPackage = jRoot["Packages"];
		Json::Value flightsGoflight = jRoot["goflight"];
		//循环每个航班
		int iFightCount = flightsGoflight.size();
		for (int i = 0; i < iFightCount; i++)
		{
			int k = 0;
			Json::Value flights = flightsGoflight[i]["flight"];
			PT9CFlightInfo pInfo = new T9CFlightInfo;
			//航班号
			pInfo->straCompany = "AQ";
			CStringA straFlightNo;
			straFlightNo.Format("%s",flights[k]["fltno"].asCString());
			pInfo->straFlightNo = straFlightNo.Right(straFlightNo.GetLength()-2);

			//出发机场代码，出发城市名
			CStringA straAirPortCode("");
			CStringA straAirPortName("");
			straAirPortCode.Format("%s",flights[k]["ori"].asCString());
			straAirPortName.Format("%s",flights[k]["oricn"].asCString());
			//上海有两个机场，新版网站返回的全是SHA，
//			if (0 == straAirPortCode.CompareNoCase("SHA"))
//			{
//				if(-1 != straAirPortName.Find("虹桥"))
//				pInfo->straFromCityCode = "SHA";
//				else
//					pInfo->straFromCityCode = "PVG";
//			}
//			else
//			{
				pInfo->straFromCityCode = straAirPortCode;
//			}
			//新网站返回的西安机场代码是SIA，位了兼容已有程序，强制改为XIY
//			if (0 == straAirPortCode.CompareNoCase("SIA"))
//			{
//				pInfo->straFromCityCode = "XIY";
//			}

			//到达机场代码，到达城市名
			straAirPortCode.Format("%s",flights[k]["dest"].asCString());
			straAirPortName.Format("%s",flights[k]["destcn"].asCString());
//			if (0 == straAirPortCode.CompareNoCase("SHA"))
//			{
//				if(-1 != straAirPortName.Find("虹桥"))
//					pInfo->straToCityCode = "SHA";
//				else
//					pInfo->straToCityCode = "PVG";
//			}
//			else
//			{
				pInfo->straToCityCode = straAirPortCode;
//			}
			//新网站返回的西安机场代码是SIA，位了兼容已有程序，强制改为XIY
//			if (0 == straAirPortCode.CompareNoCase("SIA"))
//			{
//				pInfo->straToCityCode = "XIY";
//			}
			
			pInfo->nMinHangPrice = uMinHangPrice;

			//航班日期
			CStringA straDateTime;
			straDateTime.Format("%s",flights[k]["fltdate"].asCString());
//			pInfo->straFromDate = straDateTime.Left(4)+'-'+straDateTime.Mid(4,2)
//				+'-'+straDateTime.Mid(6,2);
			pInfo->straFromDate.Format("%s-%s-%s",straDateTime.Mid(0,4),straDateTime.Mid(4,2),straDateTime.Mid(6,2));
			//straDateTime.Format("%s",flights[k]["ArrivalTime"].asCString());
			//pInfo->straToDate = straDateTime.Left(10);
			//跨天的航班，有时候政策更新的时候会有些问题
			pInfo->straToDate = pInfo->straFromDate;
			pInfo->straFromTime = "";
			pInfo->straToTime = "";

			pInfo->nPrice1 = pInfo->nPrice2 = pInfo->nPrice3 = 0;
			//
//			Json::Value cabinInfo = flights[k]["CabinInfos"];
//			int ncabinCount = cabinInfo.size();

//			if (ncabinCount >0)
//			{
				//商务
//				int iCabinId = 0;
			string strText;
			//flightsGoflight[i]["fare03"].asString();
			pInfo->nMinPrice = 0;//atoi(strText.c_str());

				
			//精打细算
			strText=flightsGoflight[i]["fare01"].asString();
			pInfo->nPrice3 = atoi(strText.c_str());
				
			//灵动实惠
			strText=flightsGoflight[i]["fare02"].asString();
			pInfo->nPrice2 = atoi(strText.c_str());
			//商务精选	
			strText=flightsGoflight[i]["fare03"].asString();
			pInfo->nPrice1 = atoi(strText.c_str());

			/*if(pInfo ->nPrice3 != 0)
			{
				pInfo->nPrice1 = pInfo->nPrice2 = pInfo->nPrice3 = 0;
			}*/
			//做安全检查，去掉9，59这样的特价机票，票量少，容易升舱，此处强行置0
				/*
			int nMinSafePrice = 60;
			if (pInfo->nPrice1 < nMinSafePrice )
			{
				pInfo->nPrice1 = 0;
			}
			if (pInfo->nPrice2 < nMinSafePrice )
			{
				pInfo->nPrice2 = 0;
			}
			if (pInfo->nPrice3 < nMinSafePrice )
			{
				pInfo->nPrice3 = 0;
			}
			*/
			//end 做安全检查，去掉9，59这样的特价机票，票量少，容易升舱，此处强行置0

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			if (pInfo->nMinHangPrice < 0)
				pInfo->nMinPrice = 0;

			//额外加价，应对春秋系统维护时
			/*
			if (0 != pInfo->nMinPrice)
			{
				pInfo->nMinPrice = pInfo->nMinPrice + m_iExtraAddPrice;
				if(pInfo->nMinPrice > pInfo->nMinHangPrice)
					pInfo->nMinPrice = pInfo->nMinPrice -1;
			}*/
			//end 额外加价，应对春秋系统维护时
			
			listFlight.push_back(pInfo);
			nCount++;
		}//循环每一个航班
	}

	return nCount;
}

int CAQHtmlParse::CalcJsonPrice(const char* pstrRate, const char* pstrPrice)
{
	int nPrice = 0;
	std::string strRateTmp(pstrRate);
	std::string strPriceTmp(pstrPrice);
	if (strRateTmp.empty() || strPriceTmp.empty())
		return 0;
	for (int n = strPriceTmp.length() - 1; n >= 0; n--)
	{
		char a = strPriceTmp.at(n);
		//int nPos = atoi(&a);//此处错误，a的地址直到遇到\’0‘才算字符串技术，所以atoi(&a)这个有bug，a地址指向的字符串是不定的，所以程序结果也不定
		int nPos =  a - '0';

		string::iterator it;
		int nPostmp = 0;
		for (it = strRateTmp.begin(); it != strRateTmp.end(); it++)
		{
			if (nPostmp == nPos)
			{
				char c = *it;
				int nTmp = c - '0';
				for (int i = 0; i < strPriceTmp.length() - 1 - n; i++)
				{
					nTmp *= 10;
				}
				nPrice += nTmp;

				strRateTmp.erase(it);
			}
			nPostmp++;
		}
	}

	return nPrice;
}

int CAQHtmlParse::CalcJsonPrice2(const char* pstrRate, const char* pstrPrice)
{
	int nPrice = 0;
	int nPriceStrLength = strlen(pstrPrice);
	char szRate[50] = {0};
	char szTmp[50] = {0};
	sprintf_s(szRate, sizeof(szRate), "%s", pstrRate);

	for (int n = nPriceStrLength - 1; n >= 0; n--)
	{
		char a = *(pstrPrice + n);
		int nPos =  a - '0';
		int nStrRateLen = strlen(szRate);
		for (int k = 0; k < nStrRateLen; k++)
		{
			if (k == nPos)
			{
				char c = szRate[k];
				int nTmp = c - '0';
				for (int i = 0; i < nPriceStrLength - 1 - n; i++)
				{
					nTmp *= 10;
				}
				nPrice += nTmp;

				//移除当前字符
				SecureZeroMemory(szTmp, sizeof(szTmp));
				sprintf_s(szTmp, sizeof(szTmp), "%s", szRate);
				//nStrRateLen-k-1为从后往前移动元素的个数
				for (int j = 0; j < nStrRateLen-k-1; j++)
				{
					//后面的元素前移
					szTmp[j+k] = szTmp[j+k+1];
				}
				//字符串少了一个字符，设置字符串结束标志
				szTmp[nStrRateLen-1] = '\0';
				//将移除当前字符后的字符串保存到原字符串待下次处理
				sprintf_s(szRate, sizeof(szRate), "%s", szTmp);
				break;
			}
		}
	}

	//CStringA stralog;
	//stralog.Format("%s_%s, nPriceStrLength=%d, nPrice=%d", pstrRate, pstrPrice, nPriceStrLength, nPrice);
	//OutputDebugStringA(stralog);

	return nPrice;
}