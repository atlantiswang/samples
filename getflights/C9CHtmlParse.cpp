#include "StdAfx.h"
#include "C9CHtmlParse.h"
#include "util.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int		C9CHtmlParse::m_iExtraAddPrice = 0;
C9CHtmlParse::C9CHtmlParse(void)
{
}


C9CHtmlParse::~C9CHtmlParse(void)
{
}

int C9CHtmlParse::ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight)
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

int C9CHtmlParse::GetMinPrice(int nPrice1, int nPrice2, int nPrice3)
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

int C9CHtmlParse::ParsePrice(CStringA stra)
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
int C9CHtmlParse::ParseNewSiteJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight, UINT uMinHangPrice, const CTime & tSel9Start, const CTime & tSel9End, BOOL bIgnoreP4Ticket, BOOL bIgnoreP5Ticket, BOOL bSelSpecialPriceTicket, int nP4SpecialPrice)
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
		Json::Value fligtsPackage = jRoot["Packages"];
		//循环每个航班
		int iFightCount = fligtsPackage.size();
		for (int i = 0; i < iFightCount; i++)
		{
			int k = 0;
			Json::Value flights = fligtsPackage[i];
			PT9CFlightInfo pInfo = new T9CFlightInfo;

			//航班号
			pInfo->straCompany = "9C";
			CStringA straFlightNo;
			straFlightNo.Format("%s",flights[k]["No"].asCString());
			pInfo->straFlightNo = straFlightNo.Right(straFlightNo.GetLength()-2);

			//出发机场代码，出发城市名
			CStringA straAirPortCode("");
			CStringA straAirPortName("");
			straAirPortCode.Format("%s",flights[k]["DepartureCode"].asCString());
			straAirPortName.Format("%s",flights[k]["DepartureStation"].asCString());
			//上海有两个机场，新版网站返回的全是SHA，
			if (0 == straAirPortCode.CompareNoCase("SHA"))
			{
				if(-1 != straAirPortName.Find("虹桥"))
					pInfo->straFromCityCode = "SHA";
				else
					pInfo->straFromCityCode = "PVG";
			}
			else
			{
				pInfo->straFromCityCode = straAirPortCode;
			}
			//新网站返回的西安机场代码是SIA，位了兼容已有程序，强制改为XIY
			if (0 == straAirPortCode.CompareNoCase("SIA"))
			{
				pInfo->straFromCityCode = "XIY";
			}

			//到达机场代码，到达城市名
			straAirPortCode.Format("%s",flights[k]["ArrivalCode"].asCString());
			straAirPortName.Format("%s",flights[k]["ArrivalStation"].asCString());
			if (0 == straAirPortCode.CompareNoCase("SHA"))
			{
				if(-1 != straAirPortName.Find("虹桥"))
					pInfo->straToCityCode = "SHA";
				else
					pInfo->straToCityCode = "PVG";
			}
			else
			{
				pInfo->straToCityCode = straAirPortCode;
			}
			//新网站返回的西安机场代码是SIA，位了兼容已有程序，强制改为XIY
			if (0 == straAirPortCode.CompareNoCase("SIA"))
			{
				pInfo->straToCityCode = "XIY";
			}
			
			pInfo->nMinHangPrice = uMinHangPrice;

			//航班日期
			CStringA straDateTime;
			straDateTime.Format("%s",flights[k]["DepartureTime"].asCString());
			pInfo->straFromDate = straDateTime.Left(10);
			//straDateTime.Format("%s",flights[k]["ArrivalTime"].asCString());
			//pInfo->straToDate = straDateTime.Left(10);
			//跨天的航班，有时候政策更新的时候会有些问题
			pInfo->straToDate = pInfo->straFromDate;
			pInfo->straFromTime = "";
			pInfo->straToTime = "";

			pInfo->nPrice1 = pInfo->nPrice2 = pInfo->nPrice3 = 0;

			Json::Value cabinInfo = flights[k]["CabinInfos"];
			int ncabinCount = cabinInfo.size();

			if (ncabinCount >0)
			{
				//商务
				int iCabinId = 0;
				if (bIgnoreP5Ticket)
					pInfo->nPrice1 = 0;
				else
				{
					Json::Value bestCabin = cabinInfo[iCabinId]["Cabins"];
					if (bestCabin.size() > 0)
					{
						int iBestCabinId = 0;
						pInfo->nPrice1 = bestCabin[iBestCabinId]["CabinPrice"].asUInt();
					}
					else
					{
						pInfo->nPrice1 = 0;
					}
				}

				//绿翼
				iCabinId = 1;
				if (bIgnoreP5Ticket)
					pInfo->nPrice2 = 0;
				else
				{
					Json::Value midCabin = cabinInfo[iCabinId]["Cabins"];
					if (midCabin.size() > 0)
					{
						int iMidCabinId = 0;
						pInfo->nPrice2 = midCabin[iMidCabinId]["CabinPrice"].asUInt();
					}
					else
					{
						pInfo->nPrice2 = 0;
					}
				}


				//4折以下
				if (bIgnoreP4Ticket)
					pInfo->nPrice3 = 0;//不上4折以下的票
				else
				{
					//上4折以下的票
					iCabinId = 2;
					Json::Value normalCabin = cabinInfo[iCabinId]["Cabins"];
					if (normalCabin.size() > 0)
					{
						int iNorCabinId = 0;
						pInfo->nPrice3 = normalCabin[iNorCabinId]["CabinPrice"].asUInt();
					}
					else
					{
						pInfo->nPrice3 = 0;
					}

					int nGw = pInfo->nPrice3 % 10;
					if (bSelSpecialPriceTicket)
					{
						//只在指定的时间范围内上4折以下的票
						if (9 == nGw)
						{
							//超过规定的时间范围了，不上
							if (tCur < tSel9Start || tCur >= tSel9End)
							{
								pInfo->nPrice3 = 0;
							}
						}
					}
					else //(!bSelSpecialPriceTicket)
					{
						//以下带9的票不上
						//4折以下，600以下且末尾带9的票不上（由于不能通过电话订）
						if (9 == nGw)
						{
							if (pInfo->nPrice3 < nP4SpecialPrice)
							{
								pInfo->nPrice3 = 0;
							}
						}
					}
				}
			}
			//做安全检查，去掉9，59这样的特价机票，票量少，容易升舱，此处强行置0
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
			//end 做安全检查，去掉9，59这样的特价机票，票量少，容易升舱，此处强行置0

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			if (pInfo->nMinHangPrice < 0)
				pInfo->nMinPrice = 0;

			//额外加价，应对春秋系统维护时
			if (0 != pInfo->nMinPrice)
			{
				pInfo->nMinPrice = pInfo->nMinPrice + m_iExtraAddPrice;
				if(pInfo->nMinPrice > pInfo->nMinHangPrice)
					pInfo->nMinPrice = pInfo->nMinPrice -1;
			}
			//end 额外加价，应对春秋系统维护时

			listFlight.push_back(pInfo);
			nCount++;
		}
	}

	return nCount;
}

int C9CHtmlParse::ParseJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight, BOOL bIgnoreP4Ticket, BOOL bIgnoreP5Ticket, BOOL bSelSpecialPriceTicket, int nP4SpecialPrice)
{
	int nCount = 0;
	Json::Reader reader;
	Json::Value jRoot;
	if (reader.parse(strHtmlData,jRoot))
	{
		Json::Value fligts = jRoot["Flights"];
		//循环每个航班
		for (int i = 0; i < fligts.size(); i++)
		{
			PT9CFlightInfo pInfo = new T9CFlightInfo;
			pInfo->straCompany.Format("%s",fligts[i]["CompanyCode"].asCString());
			pInfo->nMinHangPrice = fligts[i]["Price"].asInt();
			CStringA straFlightNo;
			straFlightNo.Format("%s",fligts[i]["FlightNo"].asCString());
			pInfo->straFlightNo = straFlightNo.Right(straFlightNo.GetLength()-2);
			pInfo->straFromCityCode.Format("%s",fligts[i]["OriAirportCode"].asCString());
			pInfo->straToCityCode.Format("%s",fligts[i]["DestAirportCode"].asCString());
			pInfo->straFromDate.Format("%s",fligts[i]["FlightDateBJ"].asCString());
			pInfo->straToDate.Format("%s",fligts[i]["FlightDateBJ"].asCString());
			pInfo->straFromTime.Format("%s",fligts[i]["OriTimeBJ"].asCString());
			pInfo->straToTime.Format("%s",fligts[i]["DestTimeBJ"].asCString());
			
			Json::Value rates = fligts[i]["RoteOfLate"];
			int nsize = rates.size();
			if (rates.size()>=2)
			{
				int nTmp = 0;
				double  dRate = 0;
				if (bIgnoreP5Ticket)
					pInfo->nPrice2 = 0;
				else
				{
					dRate = rates[nTmp].asDouble();
					char szRate[65]={0};
					sprintf_s(szRate,sizeof(szRate),"%0lf",dRate);
					int nPrice = fligts[i]["MinSeatAPriceWeb"].asInt();
					char szPrice[65]={0};
					//itoa(nPrice,szPrice,10);
					//_itoa_s(nPrice, szPrice, 65, 10);
					sprintf_s(szPrice,sizeof(szPrice),"%d",nPrice);
					string strRate(szRate);
					string strPrice(szPrice);
					pInfo->straPrice2Json.Format("%s_%s", strRate.c_str(), strPrice.c_str());
					pInfo->nPrice2 = CalcJsonPrice2(strRate.c_str(), strPrice.c_str());
				}

				if (bIgnoreP4Ticket)
					pInfo->nPrice3 = 0;
				else
				{
					nTmp = 1;
					dRate = rates[nTmp].asDouble();
					char szRate2[65]={0};
					sprintf_s(szRate2,sizeof(szRate2),"%0lf",dRate);
					int nPrice2 = fligts[i]["MinSeatBPriceWeb"].asInt();
					char szPrice2[65]={0};
					//itoa(nPrice,szPrice2,10);
					//_itoa_s(nPrice2, szPrice2, 65, 10);
					sprintf_s(szPrice2,sizeof(szPrice2),"%d",nPrice2);
					string strRate3(szRate2);
					string strPrice3(szPrice2);
					pInfo->straPrice3Json.Format("%s_%s", strRate3.c_str(), strPrice3.c_str());
					pInfo->nPrice3 = CalcJsonPrice2(strRate3.c_str(), strPrice3.c_str());

					if (!bSelSpecialPriceTicket)
					{
						//4折以下，600以下且末尾带9的票不上（由于不能通过电话订）
						if (pInfo->nPrice3 < nP4SpecialPrice)
						{
							int nGw = pInfo->nPrice3 % 10;
							if (9 == nGw)
							{
								pInfo->nPrice3 = 0;
							}
						}
						//
					}
				}			
			}
			Json::Value supers = fligts[i]["lSuperSeatInfo"];
			if (bIgnoreP5Ticket)
				pInfo->nPrice1 = 0;
			else
			{
				if (supers.size() > 0)
				{
					int nTmp = 0;
					int nPrice1 = supers[nTmp]["superSeatsPrice"].asInt();
					char szPrice1[65]={0};
					//itoa(nPrice,szPrice,10);
					//_itoa_s(nPrice1, szPrice1, 65, 10);
					sprintf_s(szPrice1,sizeof(szPrice1),"%d",nPrice1);
					string strRate1 = supers[nTmp]["RoteOfLate"].asString();
					string strPrice1(szPrice1);
					pInfo->straPrice1Json.Format("%s_%s_%d", strRate1.c_str(), strPrice1.c_str(), supers[nTmp]["subProdPrice"].asInt());
					pInfo->nPrice1 = CalcJsonPrice2(strRate1.c_str(), strPrice1.c_str()) + supers[nTmp]["subProdPrice"].asInt();
				}
			}

			//做安全检查，去掉9，59这样的特价机票，票量少，容易升舱，此处强行置0
			int nMinSafePrice = 90;
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
			//end 做安全检查，去掉9，59这样的特价机票，票量少，容易升舱，此处强行置0

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);

			//CString strlog;
			//strlog.Format(_T("minhang:%d,min:%d,p1=%d,p2=%d,p3=%d"), pInfo->nMinHangPrice, pInfo->nMinPrice, pInfo->nPrice1, pInfo->nPrice2, pInfo->nPrice3);
			//OutputDebugString(strlog);

			listFlight.push_back(pInfo);
			nCount++;
		}
	}

	return nCount;
}

int C9CHtmlParse::CalcJsonPrice(const char* pstrRate, const char* pstrPrice)
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

int C9CHtmlParse::CalcJsonPrice2(const char* pstrRate, const char* pstrPrice)
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