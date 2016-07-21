#pragma once

#include "../tidyinclude/tidy.h"
#include "../tidyinclude/buffio.h"
#include "common/CStringToolEx.h"
#include "DataProcess.h"

#include <list>

using namespace std;


class CHtmlParse
{
public:
	CHtmlParse(void);
	virtual ~CHtmlParse(void);
	virtual int ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight);
	static bool FindNode(TidyNode tnod, ctmbstr stratt, ctmbstr strvalue, TidyNode& tnOut);
	static bool IsHaveThisAttr(TidyNode tnod,ctmbstr stratt, ctmbstr strvalue);
	// 得到属性值
	static ctmbstr GetAttValue(TidyNode tnod, ctmbstr stratt);

	//查找子节点下的span节点的文本内容
	static bool GetChildSpanContent(TidyDoc tdoc, TidyNode tnod,CStringA& straRet);

	// 得到节点文本内容
	static CStringA GetNodeContent(TidyDoc tdoc,TidyNode tnod);
	// 根据节点内容查找节点
	static bool FindNodeByContent(TidyDoc tdoc, TidyNode tnod, ctmbstr strContent,TidyNode& tnRet);

public:
	//取出日期字符串中的年月日，输入日期字符串格式：2014-10-29
	void GetYearMonthDay(const CStringA & straDate, int *piYear, int *piMonth, int *piDay);
	//取出时间字符串中的时间,输入时间字符串格式：00:00
	void GetHourMinSec(const CStringA & straTime, int *piHour, int *piMin);
	//取出时间字符串中的时间,输入时间字符串格式：00:00:00
	void GetHourMinSec(const CStringA & straTime, int *piHour, int *piMin, int *piSec);
};

