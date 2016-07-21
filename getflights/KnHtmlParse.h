#pragma once

#include "HtmlParse.h"
#include "common/json/json.h"

using namespace Json;
class CKnHtmlParse :
	public CHtmlParse
{
public:
	CKnHtmlParse(void);
	~CKnHtmlParse(void);

public:
	static void SetExtraAddPrice(int nPrice){m_iExtraAddPrice = nPrice;};

public:
	int ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight);
	int ParseKnJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight, UINT uMinHangPrice, const CTime & tSel9Start, const CTime & tSel9End, BOOL bIgnoreP4Ticket=TRUE, BOOL bIgnoreP5Ticket=TRUE, BOOL bSelSpecialPriceTicket=TRUE, int nP4SpecialPrice=800);

	int CalcJsonPrice(const char* pstrRate, const char* pstrPrice);
	int CalcJsonPrice2(const char* pstrRate, const char* pstrPrice);

	int GetMinPrice(int nPrice1, int nPrice2, int nPrice3);
	int ParsePrice(CStringA stra);

private:
	static int		m_iExtraAddPrice;	//额外加价。春秋系统维护时，额外加钱上政策
};


