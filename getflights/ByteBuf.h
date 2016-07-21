

#pragma once

class CByteBuf
{
public:
	CByteBuf(BOOL bNullTerminate=FALSE);
	~CByteBuf();
public:
	//Resize会破坏已存在buf中的内容
	void	Resize(size_t iSize);
	BYTE*	GetBufPtr(void){return m_pBuf;}
	size_t Size(void) {return m_uBufByteLen;}

private:
	CByteBuf(const CByteBuf&); //not implement
	CByteBuf& operator=(const CByteBuf&);//not implement

	size_t			m_uBufByteLen;
	BYTE*			m_pBuf;
	BOOL			m_bNullTerminateStr;
};
