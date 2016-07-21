#include "StdAfx.h"
#include "ZlProxyIp.h"


CZlProxyIp::CZlProxyIp(void)
{
	Reset();
}


CZlProxyIp::~CZlProxyIp(void)
{
}

BOOL CZlProxyIp::__find(char* pIp, int nBufChar)
{
	BOOL bFind = FALSE;
	int nEnd = m_nWPos;
	if (m_nWPos >= PROXY_IP_BUF_MAX_COUNT)
		nEnd = PROXY_IP_BUF_MAX_COUNT-1;
	for (int i = 0; i < nEnd; i++)
	{
		if (0 == strcmp(m_szProxyIp[i], pIp))
		{
			bFind = TRUE;
			break;
		}
	}
	return bFind;
}
void CZlProxyIp::AppendProxyIp(char* pIp)
{
	m_lock.Lock();
	if (m_bBufOk)
		goto CZlProxyIp_AppendProxyIp_Ret;
	
	if(__find(pIp, PROXY_IP_MAX_CHAR))
		goto CZlProxyIp_AppendProxyIp_Ret;
	sprintf_s(m_szProxyIp[m_nWPos], PROXY_IP_MAX_CHAR, "%s", pIp);
	
	if (m_nWPos < PROXY_IP_BUF_MAX_COUNT)
		m_nWPos++;

	if (m_nWPos == PROXY_IP_BUF_MAX_COUNT)
		m_bBufOk = TRUE;
CZlProxyIp_AppendProxyIp_Ret:

	m_lock.Unlock();
}

void CZlProxyIp::GetProxyIp(char* pDstIp, int nBufChar)
{
	m_lock.Lock();
	sprintf_s(pDstIp, nBufChar, "%s", m_szProxyIp[m_nRPos]);
	m_nRPos++;
	if (m_nRPos >= PROXY_IP_BUF_MAX_COUNT)
		m_bAllIpUsed = TRUE;
	m_nRPos = m_nRPos % PROXY_IP_BUF_MAX_COUNT;
	m_lock.Unlock();
}

BOOL CZlProxyIp::IsBufOk()
{
	BOOL bRet = FALSE;
	m_lock.Lock();
	bRet = m_bBufOk;
	m_lock.Unlock();

	return m_bBufOk;
}
int	CZlProxyIp::GetIpCount()
{
	int nCount = 0;
	m_lock.Lock();
	nCount = m_nWPos;
	m_lock.Unlock();

	return nCount;
}

void CZlProxyIp::Reset()
{
	m_lock.Lock();

	m_nRPos = 0;
	m_nWPos = 0;
	m_bBufOk = FALSE;
	SecureZeroMemory(m_szProxyIp, sizeof(m_szProxyIp));
	m_bAllIpUsed = FALSE;

	m_lock.Unlock();
}
void CZlProxyIp::dump()
{
#ifdef _DEBUG
	m_lock.Lock();
	for (int i = 0; i < PROXY_IP_BUF_MAX_COUNT; i++)
	{
		CStringA stra;
		stra.Format("\nm_szProxyIp[%d]:%s", i, m_szProxyIp[i]);
		TRACE(stra);
	}
	m_lock.Unlock();
#endif
}

BOOL CZlProxyIp::IsAllIpUsed()
{
	BOOL bUsed = FALSE;
	m_lock.Lock();
	bUsed = m_bAllIpUsed;
	m_lock.Unlock();

	return bUsed;
}