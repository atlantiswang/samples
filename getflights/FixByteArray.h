

#pragma once

#define		CEAIR_HASH_BUF_MAX_BYTE	(512)

class CFixByteArray
{
public:
	CFixByteArray(void);
	~CFixByteArray(void);

public:
	void	AppendArray(const BYTE* pBuf, int nElementNum);
	int		GetCurElementNum(){return m_nBufCurUesElement;};
	void	CopyBuf(BYTE* pDstBuf, int nDstBufBytes);
	void	Dump(const char* pObjNameStr);

private:
	BYTE	m_szu8Buf[CEAIR_HASH_BUF_MAX_BYTE];
	int		m_nBufCurUesElement;
};

