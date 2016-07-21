#include "StdAfx.h"
#include "HtmlParse.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CHtmlParse::CHtmlParse(void)
{
}


CHtmlParse::~CHtmlParse(void)
{
}


int CHtmlParse::ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight)
{
	return 0;
}


bool CHtmlParse::FindNode(TidyNode tnod, ctmbstr stratt, ctmbstr strvalue, TidyNode& tnOut)
{
	TidyNode child;
	for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
	{
		if (IsHaveThisAttr(child,stratt,strvalue))
		{
			tnOut = child;
			return true;
		}

		TidyNode tntmp;
		if (FindNode(child,stratt,strvalue,tntmp))
		{
			tnOut = tntmp;
			return true;
		}
	}

	return false;
}


bool CHtmlParse::IsHaveThisAttr(TidyNode tnod,ctmbstr stratt, ctmbstr strvalue)
{
	TidyAttr attr;

	for ( attr = tidyAttrFirst(tnod); attr; attr = tidyAttrNext(attr) )
	{
		CStringA strLog;

		ctmbstr aa = tidyAttrName(attr);
		ctmbstr bb = tidyAttrValue(attr);
	//	strLog.Format("tag:%s\r\n",tidyAttrName(attr));
	//	OutputDebugStringA(strLog);
	//	strLog.Format(("tag:%s\r\n"),tidyAttrValue(attr));
	//	OutputDebugStringA(strLog);

		if ((0 == strcmp(tidyAttrName(attr),stratt)) && (0 == strcmp(tidyAttrValue(attr),strvalue)))
		{
			return true;
		}
	}
	return false;
}


// 得到属性值
ctmbstr CHtmlParse::GetAttValue(TidyNode tnod, ctmbstr stratt)
{
	TidyAttr attr;

	for ( attr = tidyAttrFirst(tnod); attr; attr = tidyAttrNext(attr) )
	{
		if (0 == strcmp(tidyAttrName(attr),stratt))
		{
			return tidyAttrValue(attr);
		}
	}
	return NULL;
}

// 得到节点文本内容
CStringA CHtmlParse::GetNodeContent(TidyDoc tdoc,TidyNode tnod)
{
	CStringA strRet("");
	TidyNode child;
	for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
	{
		ctmbstr name = tidyNodeGetName( child );
		TidyNodeType type = tidyNodeGetType(child);
		switch ( type )
		{
		case TidyNode_Comment:
			{
				TidyBuffer text = {0};
				tidyBufInit(&text);
				if (tidyNodeGetText(tdoc, child, &text))
				{
				//	printf("TidyNode_Comment: %s\n", text.bp);
					tidyBufFree(&text);
				}
			}
			break;
		case TidyNode_Text: 
			{ 
				TidyBuffer text = {0};
				tidyBufInit(&text);
				if (tidyNodeGetText(tdoc, child, &text))
				{
					//printf("TidyNode_Text: %s\n", text.bp);
					strRet.Format("%s",text.bp);
					tidyBufFree(&text);

					return strRet;
				}
			}
			break;
		case TidyNode_CDATA: 
			{
				TidyBuffer text = {0};
				tidyBufInit(&text);
				if (tidyNodeGetText(tdoc, child, &text))
				{
				//	printf("TidyNode_CDATA: %s\n", text.bp);
					tidyBufFree(&text);
				}
			}
			break;
		case TidyNode_Start:
			{
		//		return GetNodeContent( tdoc, child);
			}
			break;
		default:
			break;
		}
	}

	return strRet;
}

// 根据节点内容查找节点
bool CHtmlParse::FindNodeByContent(TidyDoc tdoc, TidyNode tnod, ctmbstr strContent,TidyNode& tnRet)
{
	CStringA strCont;
	strCont.Format("%s",strContent);
	CStringA strTemp;
	strTemp = GetNodeContent(tdoc,tnod);
	strTemp = strTemp.Mid(0,strTemp.GetLength() < strCont.GetLength() ? strTemp.GetLength() : strCont.GetLength());
	int nRet = strTemp.Compare(strCont);
	if (0 == strTemp.Compare(strCont))
	{
		tnRet = tnod;
		return true;
	}

	TidyNode child;
	for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
	{
		if (FindNodeByContent(tdoc,child,strContent,tnRet))
		{
			return true;
		}
	}
	
	return false;
}

//查找子节点下的span节点的文本内容
bool CHtmlParse::GetChildSpanContent(TidyDoc tdoc, TidyNode tnod,CStringA& straRet)
{
	TidyNode child;
	for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
	{
		if (tidyNodeIsSPAN(child))
		{
			straRet = GetNodeContent(tdoc,child);
			return true;
		}
		else
		{
			if (GetChildSpanContent(tdoc,child,straRet))
			{
				return true;
			}
		}
	}

	return false;
}

//取出日期字符串中的年月日，输入日期字符串格式：2014-10-29
void CHtmlParse::GetYearMonthDay(const CStringA & straDate, int *piYear, int *piMonth, int *piDay)
{
	CStringA straYear = straDate.Left(4);
	CStringA straMonth = straDate.Mid(5,2);
	CStringA straDay = straDate.Right(2);
	*piYear = atoi(straYear);
	*piMonth = atoi(straMonth);
	*piDay = atoi(straDay);
}

//取出时间字符串中的时间,输入时间字符串格式：00:00
void CHtmlParse::GetHourMinSec(const CStringA & straTime, int *piHour, int *piMin)
{
	int iPos = straTime.Find(':');
	CStringA straHour = straTime.Left(iPos);
	CStringA straMin = straTime.Mid(iPos+1);
	*piHour = atoi(straHour);
	*piMin = atoi(straMin);
}

//取出时间字符串中的时间,输入时间字符串格式：00:00:00
void CHtmlParse::GetHourMinSec(const CStringA & straTime, int *piHour, int *piMin, int *piSec)
{
	int iPos = straTime.Find(':');
	CStringA straHour = straTime.Left(iPos);
	CStringA straMin = straTime.Mid(iPos+1, 2);
	*piHour = atoi(straHour);
	*piMin = atoi(straMin);
	*piSec = 0;
}