#include "StdAfx.h"
#include "KnHtmlParse.h"
#include "util.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int		CKnHtmlParse::m_iExtraAddPrice = 0;
CKnHtmlParse::CKnHtmlParse(void)
{
}


CKnHtmlParse::~CKnHtmlParse(void)
{
}

int CKnHtmlParse::ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight)
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

int CKnHtmlParse::GetMinPrice(int nPrice1, int nPrice2, int nPrice3)
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

int CKnHtmlParse::ParsePrice(CStringA stra)
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
//抓取联航新网站航班数据
int CKnHtmlParse::ParseKnJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight, UINT uMinHangPrice, const CTime & tSel9Start, const CTime & tSel9End, BOOL bIgnoreP4Ticket, BOOL bIgnoreP5Ticket, BOOL bSelSpecialPriceTicket, int nP4SpecialPrice)
{
	int nCount = 0;
	Json::Reader reader;
	Json::Value jRoot;
	CTime tCur = CTime::GetCurrentTime();
	listFlight.clear();
	CStringA lastFlightNo;
	if (reader.parse(strHtmlData,jRoot))
	{
		if(jRoot.isNull() || !jRoot.isObject())
			return 0;
		Json::Value productUnits = jRoot["airResultDto"]["productUnits"];
		//循环每个航班
		int iFightCount = productUnits.size();
		for (int i = 0; i < iFightCount; i++)
		{
			int k = 0;
//			Json::Value flights = productUnits[i];
			PT9CFlightInfo pInfo = new T9CFlightInfo;
			//航班号
			pInfo->straCompany = "KN";
			CStringA straFlightNo;
			straFlightNo.Format("%s",productUnits[i]["flightNoGroup"].asCString());
			pInfo->straFlightNo = straFlightNo.Right(straFlightNo.GetLength()-2);
			//如果航班相同，直接跳过
			if(pInfo->straFlightNo == lastFlightNo)
			{
				delete pInfo;
				continue;
			}
			lastFlightNo = pInfo->straFlightNo;
			//出发机场代码，出发城市名
			CStringA straAirPortCode("");
			CStringA straAirPortName("");
			Json::Value oriDestOption = productUnits[i]["oriDestOption"];
			Json::Value flights = oriDestOption[k]["flights"];//k要等于0
		//	Json::Value departureAirport = flights[k]["departureAirport"]["code"].asCString();
		//	Json::Value arrivalAirport = flights[k]["arrivalAirport"];
			straAirPortCode.Format("%s",flights[k]["departureAirport"]["code"].asCString());
			straAirPortName.Format("%s",flights[k]["departureAirport"]["cityCode"].asCString());
			pInfo->straFromCityCode = straAirPortCode;
			//新网站返回的西安机场代码是SIA，位了兼容已有程序，强制改为XIY
			if (0 == straAirPortCode.CompareNoCase("SIA"))
			{
				pInfo->straFromCityCode = "XIY";
			}

			//到达机场代码，到达城市名
			straAirPortCode.Format("%s",flights[k]["arrivalAirport"]["code"].asCString());
			straAirPortName.Format("%s",flights[k]["arrivalAirport"]["cityCode"].asCString());
			pInfo->straToCityCode = straAirPortCode;
			//新网站返回的西安机场代码是SIA，位了兼容已有程序，强制改为XIY
			if (0 == straAirPortCode.CompareNoCase("SIA"))
			{
				pInfo->straToCityCode = "XIY";
			}

			pInfo->nMinHangPrice = uMinHangPrice;

			//航班日期
			CStringA straDateTime;
			straDateTime.Format("%s",flights[k]["departureDateTime"].asCString());
			pInfo->straFromDate = straDateTime.Left(10);
			//straDateTime.Format("%s",flights[k]["ArrivalTime"].asCString());
			//pInfo->straToDate = straDateTime.Left(10);
			//跨天的航班，有时候政策更新的时候会有些问题
			pInfo->straToDate = pInfo->straFromDate;
			pInfo->straFromTime = "";
			pInfo->straToTime = "";

			pInfo->nPrice1 = pInfo->nPrice2 = pInfo->nPrice3 = 0;

			Json::Value fareInfoView = productUnits[i]["fareInfoView"];

			CStringA fareBasisCode;
			fareBasisCode.Format("%s",fareInfoView[k]["fareBasisCode"].asCString());
//			if(fareBasisCode == "V" || fareBasisCode == "T")
//			AfxMessageBox(CStrA2CStrW(productUnits[i]["productInfo"]["productName"].asCString()));
			if(productUnits[i]["productInfo"]["productCode"].asString() == "HLY")
			{
				pInfo->nPrice1 = atoi(fareInfoView[k]["fare"]["salePrice"].asString().c_str());
				if(productUnits[i+1]["productInfo"]["productCode"].asString() == "CYY")
				{
					Json::Value fareInfoView = productUnits[i+1]["fareInfoView"];
					pInfo->nPrice2 = atoi(fareInfoView[k]["fare"]["salePrice"].asString().c_str());
					i++;
				}
			}
			else if(productUnits[i]["productInfo"]["productCode"].asString() == "CYY")
			{
				pInfo->nPrice2 = atoi(fareInfoView[k]["fare"]["salePrice"].asString().c_str());
				CString db;
				db.Format(_T("------------%d--\r\n"),pInfo->nPrice2);
				OutputDebugString(db);
			}
			else 
			{
				delete pInfo;
				nCount++;
				continue;
			}
			
			/*
			else if(fareBasisCode == "R")
				pInfo->nPrice2 = atoi(fareInfoView[k]["fare"]["salePrice"].asString().c_str());
			else if(fareBasisCode == "H")
				pInfo->nPrice3 = atoi(fareInfoView[k]["fare"]["salePrice"].asString().c_str());
			else pInfo->nPrice3 = atoi(fareInfoView[k]["fare"]["salePrice"].asString().c_str());*/

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			if (pInfo->nMinHangPrice < 0)
				pInfo->nMinPrice = 0;

			listFlight.push_back(pInfo);
			nCount++;
		}
	}

	return nCount;
}

int CKnHtmlParse::CalcJsonPrice(const char* pstrRate, const char* pstrPrice)
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

int CKnHtmlParse::CalcJsonPrice2(const char* pstrRate, const char* pstrPrice)
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