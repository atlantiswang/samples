
#pragma once
#include <string>
#include <list>
using namespace std;
#include "CeairMobileEConst.h"

#define AES_KEY_BYTE_LEN	(32)
#define AES_IV_BYTE_LEN	(16)
#define AES_XEMP_KEY_BYTE_LEN	(20)
#define SESSIONID_MAX_CHAR		(100)

class CGrapCeFlight
{

public:
	CGrapCeFlight();
	~CGrapCeFlight();

public:
	static void SetOutlogFlag(BOOL bOutlog){ m_bOutLog = bOutlog;}
	static void	InitAesKeys(BYTE * pu8AesEncryptKey, BYTE * pu8AesEncryptIV, BYTE * pu8XempEncryptKey, BYTE * pu8AesDecryptKey, BYTE * pu8AesDecryptIV);
	static void SetSessionId(const std::string & strSessionId);
	static BOOL	GrapFlight(BOOL bChangeProxyIp, const CStringA & straDCode, const CStringA & straACode, const CStringA & straFlightStratDate, std::list<SCeairFlightInfo*> & flightList);

private:
	static BOOL __ParseCeairFlight(const std::string & strXml, std::list<SCeairFlightInfo*> & flightList);
	//static void __WriteHttpResponse(const CStringA & straFileName, const BYTE* pBuf, int nBufBytes);

private:
	static	BYTE m_u8AesEncryptKey[AES_KEY_BYTE_LEN+1];
	static	BYTE m_u8AesEncryptIV[AES_IV_BYTE_LEN+1];
	static	BYTE m_u8XempEncryptKey[AES_XEMP_KEY_BYTE_LEN+1];
	static	BYTE m_u8AesDecryptKey[AES_KEY_BYTE_LEN+1];
	static	BYTE m_u8AesDecryptIV[AES_IV_BYTE_LEN+1];
	static	BYTE m_u8SessionId[SESSIONID_MAX_CHAR+1];

	static	BOOL m_bOutLog;

};

