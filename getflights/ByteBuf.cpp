
#include "stdafx.h"
#include "ByteBuf.h"

CByteBuf::CByteBuf(BOOL bNullTerminate)
{
	m_uBufByteLen = 0;
	m_pBuf = NULL;
	m_bNullTerminateStr = bNullTerminate;
}

CByteBuf::~CByteBuf()
{
	if (NULL != m_pBuf)
	{
		delete [] m_pBuf;
		m_pBuf = NULL;
	}
}

void CByteBuf::Resize(size_t iSize)
{
	if(0 == iSize)
		return;
	if( 0 != m_uBufByteLen)
	{
		delete [] m_pBuf;
		m_pBuf = NULL;
	}

	if (m_bNullTerminateStr)
	{
		m_uBufByteLen = iSize+1;
	}
	else
	{
		m_uBufByteLen = iSize;
	}
	m_pBuf = new BYTE[m_uBufByteLen];
	SecureZeroMemory(m_pBuf, m_uBufByteLen);
	if (m_bNullTerminateStr)
	{
		*(m_pBuf+iSize) = '\0';
	}
}