

#pragma once

#include <string>
#include <list>
using namespace std;
#include "CeairMobileEConst.h"


class CCeairMobileE
{
public:
	CCeairMobileE(void);
	~CCeairMobileE(void);

public:

	static void	SetOutLogFlag(BOOL bOutlog=FALSE){ m_bOutLog = bOutlog; }
	static BOOL	GetServerKey();
	static BOOL GetCeairMobileEFlight(BOOL bChangeProxyIp, const CStringA & strDCode, const CStringA & strACode, const CStringA & strFlightStratDate, std::list<SCeairFlightInfo*> & flightList);

private:
	static void	__GetSessionId(std::string & str, const std::wstring & httpResponseHeader);
	static void __Init();
	static void __PrintEncryptServerkey(const SCeairMERecvRawHeader *pRecvHeader);
public:
	static void __DecrptServerKeyWithAES(BYTE * pu8ServerKey, int nServerKeyBytes);

	static std::string m_strSessionId;
	static BYTE			m_u8EncryptSeverKey[CEAIR_ME_SEVER_KEY_LEN];
	static BOOL			m_bOutLog;

};

