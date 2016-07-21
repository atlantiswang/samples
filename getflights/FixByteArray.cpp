
#include "Stdafx.h"
#include "FixByteArray.h"

CFixByteArray::CFixByteArray(void)
{
	SecureZeroMemory(m_szu8Buf, sizeof(m_szu8Buf));
	m_nBufCurUesElement = 0;
}

CFixByteArray::~CFixByteArray(void)
{

}

void CFixByteArray::AppendArray(const BYTE* pBuf, int nElementNum)
{
	int nFreeBytes = (_countof(m_szu8Buf) - m_nBufCurUesElement)*sizeof(BYTE);
	ASSERT(nElementNum < nFreeBytes);
	int iCpBytes = nElementNum * sizeof(BYTE);
	memcpy_s(m_szu8Buf+m_nBufCurUesElement, nFreeBytes, pBuf, iCpBytes);
	m_nBufCurUesElement += nElementNum;
	TRACE(_T("\r\rn CFixByteArray::AppendArray size=%d\r\n"), m_nBufCurUesElement);
}

void CFixByteArray::CopyBuf(BYTE* pDstBuf, int nDstBufBytes)
{
	ASSERT(nDstBufBytes <= (m_nBufCurUesElement*sizeof(BYTE)));
	memcpy_s(pDstBuf, nDstBufBytes, m_szu8Buf, nDstBufBytes);
}

void CFixByteArray::Dump(const char* pObjNameStr)
{
#ifdef _DEBUG
	TRACE("\r\n:%s", pObjNameStr);
	for(int i = 0; i < m_nBufCurUesElement; i++)
	{
		TRACE("%02X", m_szu8Buf[i]);
	}
#endif
}