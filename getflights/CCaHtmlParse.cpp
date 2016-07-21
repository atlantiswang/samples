
#include "stdafx.h"
#include "CCaHtmlParse.h"


CTime	CCaHtmlParse::m_tGetEndTime;
bool	CCaHtmlParse::m_bGetAllCaTuanFlight = true;
int		CCaHtmlParse::m_nMinTicketWarnNum = 2;

void dumpNode( TidyNode tnod, int indent );

CCaHtmlParse::CCaHtmlParse(void)
{

}

CCaHtmlParse::~CCaHtmlParse(void)
{

}

BOOL CCaHtmlParse::__IsFlightValid(const TidyNode & tdChild)
{
	BOOL bValid = TRUE;
	TidyNode tRadioNode;
	CStringA straValid;
	tRadioNode = tidyGetChild(tdChild);
	straValid.Format("%s", GetAttValue(tRadioNode, "disabled"));
	if (0 == straValid.CompareNoCase("disabled"))
		bValid = FALSE;

	return bValid;
}
int CCaHtmlParse::ParseCaHtmlFlights(std::list<SCaLowPriceFlightDetail*> & listFlight, const std::string& strHtmlData, const CStringA & straDCode, const CStringA & straACode, const SCaLowPriceFlightInfo*	pLowPriceFlightInfo)
{
	TidyDoc doc = tidyCreate();
	tidySetCharEncoding(doc,"raw");
	tidyParseString(doc,strHtmlData.c_str());
	TidyNode tnRoot = tidyGetRoot(doc);

	TidyNode tFlightTab;
	TidyNode tdChild;
	int nIndexTd = 0;

	CTime tCurrent = CTime::GetCurrentTime();
	SCaLowPriceFlightDetail *pfindFlight = NULL;
	if (FindNode(tnRoot,"class","CA_table mt_10 clear",tFlightTab))
	{
		//循环解析结算价,tblPolicy下的每一个子节点即为一条结算价信息
		TidyNode trFlight;
		int nIndexTr = 0;
		BOOL bValid = FALSE;
		CStringA straDPortCode = straDCode;
		CStringA straAPortCode = straACode;
		CStringA straFlightNo("");
		CStringA straFlightStartDate("");
		CStringA straSaleEndDate("");
		CStringA straSaleEndTime("");
		CStringA straFlightStartTime("");

		UINT uPrice = 0;
		UINT uRemainTicket = 0;
		for ( trFlight = tidyGetChild(tFlightTab); trFlight; trFlight = tidyGetNext(trFlight) )
		{
			if (0 == nIndexTr)//跳过表头
			{
				nIndexTr++;
				continue;
			}

			nIndexTd = 0;
			bValid = FALSE;
			straFlightNo = "";
			straFlightStartDate = "";
			straSaleEndDate = "";
			straSaleEndTime = "";
			straFlightStartTime = "";
			uPrice = 0;
			uRemainTicket = 0;
			for ( tdChild = tidyGetChild(trFlight); tdChild; tdChild = tidyGetNext(tdChild) )
			{
				switch(nIndexTd)
				{
				case 0:
					{
						//选择，是否为disabled
						bValid = __IsFlightValid(tdChild);
						TRACE(_T("Flight valid:%d-"), bValid);
						
					}
					break;
				case 1:
					{
						//日期/航班号
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						__GetFlightNoAndFlightStartDate(straFlightNo, straFlightStartDate, doc, tdChild);
						TRACE("date:%s, no:%s-", straFlightStartDate, straFlightNo);
						 //TRACE("%s\r\n", GetNodeContent(doc, tdChild));
					}
					break;
				case 2:
					{
						//起降时间
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						 //TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						__GetFlightStartTime(straFlightStartTime, doc, tdChild);
					}
					break;
				case 3:
					{
						//机场
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						 //TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						if (__IsTwoAirPort(straDCode, straACode))
						{
							__GetAirPortCode(straDPortCode, straAPortCode, doc, tdChild);
							if(straDPortCode.IsEmpty())
								straDPortCode = straDCode;
							if(straAPortCode.IsEmpty())
								straAPortCode = straACode;
							TRACE("%s->%s-", straDPortCode, straAPortCode);
						}

					}
					break;
				case 4:
					{
						//销售结束日期,时间
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						//TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						__GetSaleEndDate(straSaleEndDate, straSaleEndTime, doc, tdChild);
						TRACE("sale end date:%s, %s-", straSaleEndDate, straSaleEndTime);
					}
					break;
				case 5:
					{
						//团购价
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						//TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						//CStringA straSetPrice = GetNodeContent(doc, tdChild);

						//double fSetPrice = atof(straSetPrice.GetBuffer(0));
						//straSetPrice.ReleaseBuffer();
						//tidyRelease(doc);
						//return fSetPrice;
						__GetPriceAndRamainTicket(&uPrice, &uRemainTicket, doc, tdChild);
						TRACE("price:%d, remain %d seats", uPrice, uRemainTicket);
					}
					break;
				}

				nIndexTd++;
			}
			TRACE(_T("\r\n"));

			//截至日期之后的航班不抓取
			//得到起飞日期
			int nFlightStartYear = 2014;
			int nFlightStartMonth = 12;
			int nFlightStartDay = 12;
			GetYearMonthDay(straFlightStartDate, &nFlightStartYear, &nFlightStartMonth, &nFlightStartDay);
			
			CTime tStart(nFlightStartYear, nFlightStartMonth, nFlightStartDay, 0, 0, 0);
			//if (!m_bGetAllCaTuanFlight)
			//{
			//	if (tStart > m_tGetEndTime)
			//		continue;
			//}
			//
			
			//double d6 = pLowPriceFlightInfo->iMinHangPrice * 0.6;
			//UINT u6 = (UINT)d6;
			////6折以上普通团购退改签要收费（低价申请不受限制），所以不上
			//if (uPrice > d6 && CA_TUAN_PRODUCT == pLowPriceFlightInfo->iProductType)
			//{
			//	bValid = FALSE;
			//	uRemainTicket = 0;
			//	continue;
			//}
			//相同日期、时间、班次的航班，只取最低价
			BOOL bFind = __findCaFlight(&pfindFlight, straFlightStartDate, straDPortCode, straAPortCode, straFlightNo, listFlight);
			if (bFind)
			{
				int nCurPrice = (int)uPrice;
				//当前解析出的这个比上次解析出的便宜
				if(pfindFlight->nPrice > nCurPrice)
				{
					if (uRemainTicket > m_nMinTicketWarnNum)
					{
						//当前票的数量充足时，用当前票的数量更新上次解析出的数量
						pfindFlight->nRemainSeat = uRemainTicket;
						pfindFlight->nPrice = nCurPrice;
						pfindFlight = NULL;
					}
				}
				else //(pfindFlight->nPrice <= nCurPrice)
				{
					if(pfindFlight->nRemainSeat <= m_nMinTicketWarnNum)
					{
						pfindFlight->nRemainSeat = uRemainTicket;
						pfindFlight->nPrice = nCurPrice;
						pfindFlight = NULL;
					}
				}

				continue;
			}

			//保存解析出来的航班信息,调用者负责释放内存
			if (bValid)
			{
				SCaLowPriceFlightDetail* pDetail = new SCaLowPriceFlightDetail;
				pDetail->straCompany = "CA";	
				pDetail->straFromCityCode = straDPortCode;	
				pDetail->straToCityCode = straAPortCode;	
				pDetail->straFlightNo = straFlightNo;		
				pDetail->straFromDate = straFlightStartDate;	
				//由于携程订单进入需要一定的时间，国航下班16：00下班，所以当天的票,第2天12:00之前的票，销售结束时间提前30分钟，	
				//取销售间隔
				int nSaleEndYear = 2014;
				int nSaleEndMonth = 12;
				int nSaleEndDay = 12;
				GetYearMonthDay(straSaleEndDate, &nSaleEndYear, &nSaleEndMonth, &nSaleEndDay);
				int nSaleEndHour = 12;
				int nSaleEndMin = 0;
				GetHourMinSec(straSaleEndTime, &nSaleEndHour, &nSaleEndMin);
				CTime tSaleEndDate(nSaleEndYear, nSaleEndMonth, nSaleEndDay, nSaleEndHour, nSaleEndMin, 0);
				CTimeSpan tSpan = tSaleEndDate - tCurrent;
				//end 取销售间隔
				//得到起飞时间
				int nFlightStartHour = 12;
				int nFlightStartMin = 0;
				GetHourMinSec(straFlightStartTime, &nFlightStartHour, &nFlightStartMin);
				CTime tFlightStartTime(nFlightStartYear, nFlightStartMonth, nFlightStartDay, nFlightStartHour, nFlightStartMin, 0);
				CTime tTimeKey(nFlightStartYear, nFlightStartMonth, nFlightStartDay, 12, 0, 0);
				//end 得到起飞时间
	
				//今明两天的、起飞时间在12点之前、且是低价申请的，销售结束时间为 前一天的官网销售结束的前30分钟
				if ((CA_TUAN_LOW_PRICE_APPLY_PRODUT == pLowPriceFlightInfo->iProductType) && (1 == tSpan.GetDays()))//明天的的低价申请
				{	
					if(tFlightStartTime <= tTimeKey)//明天12起飞的低价申请, 今天下午3：25前有效（国航4点下班）
					{
						pDetail->straSaleEndDate.Format("%d-%02d-%02d", tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay());
						CTime tSaleEnd(tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay(), 15, 25, 0);
						pDetail->straSaleEndTime.Format("%02d:%02d:%02d", tSaleEnd.GetHour(), tSaleEnd.GetMinute(), 0);	
					}
					else//明天12后起飞的低价申请，明早可以出票
					{
						pDetail->straSaleEndDate = straSaleEndDate;
						pDetail->straSaleEndTime.Format("%02d:%02d:%02d", nSaleEndHour, nSaleEndMin, 0);
					}
				}
				else if ((CA_TUAN_LOW_PRICE_APPLY_PRODUT == pLowPriceFlightInfo->iProductType) && (tSpan.GetDays() < 1))//今天的的低价申请，今天下午3：30前有效（国航4点下班）
				{
					pDetail->straSaleEndDate.Format("%d-%02d-%02d", tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay());
					CTime tSaleEnd(tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay(), 15, 30, 0);
					pDetail->straSaleEndTime.Format("%02d:%02d:%02d", tSaleEnd.GetHour(), tSaleEnd.GetMinute(), 0);	
				}
				else//普通团购，后天及以后的低价申请
				{
					pDetail->straSaleEndDate = straSaleEndDate;
					pDetail->straSaleEndTime.Format("%02d:%02d:%02d", nSaleEndHour, nSaleEndMin, 0);
				}

				//政策销售时间到，删除政策
				GetYearMonthDay(pDetail->straSaleEndDate,  &nSaleEndYear, &nSaleEndMonth, &nSaleEndDay);
				int nSaleEndSec = 0;
				GetHourMinSec(pDetail->straSaleEndTime, &nSaleEndHour, &nSaleEndMin, &nSaleEndSec);
				CTime tPolicyDeleteTime(nSaleEndYear, nSaleEndMonth, nSaleEndDay, nSaleEndHour, nSaleEndMin, nSaleEndSec);
				if (tCurrent >= tPolicyDeleteTime)
					uRemainTicket = 0;

				pDetail->nPrice = uPrice;				
				pDetail->nProductId = pLowPriceFlightInfo->iProductId;			
				pDetail->nRemainSeat = uRemainTicket;	
				pDetail->nProductType = pLowPriceFlightInfo->iProductType;

				listFlight.push_back(pDetail);
			}
		}
	}

	tidyRelease(doc);	

	return -1.0;
}

BOOL CCaHtmlParse::__findCaFlight(SCaLowPriceFlightDetail** pFind, const CStringA & straFlightStartDate, const CStringA & straDPortCode
	, const CStringA & straAPortCode, const CStringA & straFlightNo, const std::list<SCaLowPriceFlightDetail*> & listFlight)
{
	*pFind = NULL;
	BOOL bFind = FALSE;
	SCaLowPriceFlightDetail* pCur = NULL;
	for (std::list<SCaLowPriceFlightDetail*>::const_iterator it = listFlight.begin(); it != listFlight.end();  it++)
	{
		pCur = *it;
		if (0 == straFlightNo.CompareNoCase(pCur->straFlightNo) && 0 == straDPortCode.CompareNoCase(pCur->straFromCityCode)
			&& 0 == straAPortCode.CompareNoCase(pCur->straToCityCode) && 0 == straFlightStartDate.CompareNoCase(pCur->straFromDate))
		{
			bFind = TRUE;
			*pFind = pCur;
			break;
		}
	}
	return bFind;
}
void CCaHtmlParse::__GetFlightStartTime(CStringA & strFlightStartTime, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	strFlightStartTime = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);

	CStringA straKey("\">");
	int iStartPos = straRet.Find(straKey);
	int iEndPos = straRet.Find("</strong>");
	iStartPos = iStartPos+straKey.GetLength();
	strFlightStartTime = straRet.Mid(iStartPos, iEndPos-iStartPos);

	tidyBufFree(&text);
}
BOOL CCaHtmlParse::__IsTwoAirPort(const CStringA & straCode1, const CStringA & straCode2)
{
	BOOL bRet = FALSE;
	if (0 == straCode1.CompareNoCase("SHA") || 0 == straCode1.CompareNoCase("PVG") || 0 == straCode1.CompareNoCase("PEK") || 0 == straCode1.CompareNoCase("NAY")
		|| 0 == straCode2.CompareNoCase("SHA") || 0 == straCode2.CompareNoCase("PVG") || 0 == straCode2.CompareNoCase("PEK") || 0 == straCode2.CompareNoCase("NAY"))
	{
		bRet = TRUE;
	}
	return bRet;
}
void CCaHtmlParse::__GetFlightNoAndFlightStartDate(CStringA & strFlightNo, CStringA & strFlightStartDate, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	strFlightNo = "";
	strFlightStartDate = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();
	strFlightStartDate = straRet.Mid(4, 10);
	int iStartPos = straRet.Find('C');//匹配CA，ca，Ca，cA，<br />后会插入回车换行符，
	if(-1 == iStartPos)//没找到大写C，匹配小写c
		iStartPos = straRet.Find('c');
	int iEndPos = straRet.Find("</");
	strFlightNo = straRet.Mid(iStartPos, iEndPos-iStartPos);//国航航班号有3位的，还有4位的
	strFlightNo = strFlightNo.MakeUpper();
	strFlightNo = strFlightNo.Mid(2);//去掉CA

	tidyBufFree(&text);
}

void CCaHtmlParse::__GetSaleEndDate(CStringA & straEndDate, CStringA & straEndTime, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	straEndDate = "";
	straEndTime = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();

	int iPos = straRet.Find("<br");
	straRet = straRet.Mid(4, iPos-4);
	straEndDate = straRet.Left(10);
	straEndTime = straRet.Mid(11);
	straEndTime.Trim();

	tidyBufFree(&text);
}

void CCaHtmlParse::__GetAirPortCode(CStringA & straDCode, CStringA & straACode, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	CStringA straSha("上海虹桥");
	CStringA straPvg("上海浦东");
	CStringA straPek("北京首都");
	CStringA straNay("北京南苑");

	straDCode = "";
	straACode = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();

	CStringA straKey("<br />");//<br />后有回车换行符
	int iPos = straRet.Find(straKey);
	CStringA straDCity = straRet.Mid(4, iPos-4);
	if (-1 != straDCity.Find(straSha))
		straDCode = "SHA";
	else if (-1 != straDCity.Find(straPvg))
		straDCode = "PVG";
	else if (-1 != straDCity.Find(straPek))
		straDCode = "PEK";
	else if(-1 != straDCity.Find(straNay))
		straDCode = "NAY";
	else
	{

	}

	//取到达机场，<br />后有回车换行符
	straRet = straRet.Mid(iPos+straKey.GetLength());
	straRet.Remove(0x0d);//去掉回车
	straRet.Remove(0x0a);//去掉换行
	int iEndPos = straRet.Find("</td>");
	CStringA straACity = straRet.Left(iEndPos);
	if (-1 != straACity.Find(straSha))
		straACode = "SHA";
	else if (-1 != straACity.Find(straPvg))
		straACode = "PVG";
	else if (-1 != straACity.Find(straPek))
		straACode = "PEK";
	else if(-1 != straACity.Find(straNay))
		straACode = "NAY";
	else
	{

	}

	tidyBufFree(&text);
}
void CCaHtmlParse::__GetPriceAndRamainTicket(UINT *pPrice, UINT *pRemainTicket, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	*pPrice = 0;
	*pRemainTicket = 0;

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();

	CStringA straKey("</font>");
	int iPos = straRet.Find(straKey);
	int iEndPos = straRet.Find("</strong>");
	int iStartPos = iPos+straKey.GetLength();
	CStringA straPrice = straRet.Mid(iStartPos, iEndPos-iStartPos);
	straPrice.Remove(0x0d);//去掉回车
	straPrice.Remove(0x0a);//去掉换行
	*pPrice = atoi(straPrice.GetBuffer(0));
	straPrice.ReleaseBuffer();

	//剩余座位
	straKey = "：";
	iPos = straRet.Find(straKey);
	iEndPos = straRet.Find("</td>");
	iStartPos = iPos+straKey.GetLength();
	CStringA straRemainSeat = straRet.Mid(iStartPos, iEndPos-iStartPos);
	*pRemainTicket = atoi(straRemainSeat.GetBuffer(0));
	straRemainSeat.ReleaseBuffer();

	tidyBufFree(&text);
}
void dumpNode( TidyNode tnod, int indent )
{
	TidyNode child;

	for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
	{
		ctmbstr name;
		switch ( tidyNodeGetType(child) )
		{
		case TidyNode_Root:       name = "Root";                    break;
		case TidyNode_DocType:    name = "DOCTYPE";                 break;
		case TidyNode_Comment:    name = "Comment";                 break;
		case TidyNode_ProcIns:    name = "Processing Instruction";  break;
		case TidyNode_Text:       name = "Text";                    break;
		case TidyNode_CDATA:      name = "CDATA";                   break;
		case TidyNode_Section:    name = "XML Section";             break;
		case TidyNode_Asp:        name = "ASP";                     break;
		case TidyNode_Jste:       name = "JSTE";                    break;
		case TidyNode_Php:        name = "PHP";                     break;
		case TidyNode_XmlDecl:    name = "XML Declaration";         break;

		case TidyNode_Start:
		case TidyNode_End:
		case TidyNode_StartEnd:
		default:
			name = tidyNodeGetName( child );
			break;
		}
		assert( name != NULL );
		TRACE( "------%d,%d, %s,%s", indent, indent, " ", name );
		dumpNode( child, indent + 4 );
	}
}