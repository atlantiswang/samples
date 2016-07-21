#pragma once
#include "DataProcess.h"

class CZlProxyIp
{
public:
	CZlProxyIp();
	~CZlProxyIp();
public:	
	void			AppendProxyIp(char* pIp);
	void			GetProxyIp(char* pDstIp, int nBufChar);
	BOOL			IsBufOk();
	BOOL			IsAllIpUsed();
	int				GetIpCount();
	void			Reset();
	void			dump();

private:
	BOOL			__find(char* pIp, int nBufChar);
	CCriticalSection	m_lock;
	int					m_nRPos;
	int					m_nWPos;
	BOOL				m_bBufOk;
	char				m_szProxyIp[PROXY_IP_BUF_MAX_COUNT][PROXY_IP_MAX_CHAR+1];
	BOOL				m_bAllIpUsed;
};

