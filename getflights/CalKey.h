

#pragma once

#include <string>
#include <map>
using namespace std;
#include "CeairMobileEConst.h"


class CCalKey
{
public:
	CCalKey(void);
	~CCalKey(void);

public:
	static void	BYTEArrayCopy(const BYTE *pu8SrcBuf, int iSrcBufCopyPos, BYTE *pu8DstBuf, int iDstBufCopyPos, int iCopyByte);
	//输出pu8DstBuf = pu8Array1 + pu8Array2
	static void JoinByteArray(const BYTE *pu8Array1, int iArray1Bytes, const BYTE *pu8Array2, int iArray2Bytes, BYTE *pu8DstArray, int iDstArrayBytes=48);
	static void CreateMasterSecret(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, const BYTE * pByteArray3, int iByteArray3Bytes, int paramInt, BYTE *pDestArray, int iDstArrayBytes);
	static void PRF(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, const BYTE * pByteArray3, int iByteArray3Bytes, int paramInt, BYTE *pDestArray, int iDstArrayBytes);
	//数组异或操作时目标数组的大小由pByteArray1定
	static void xorArray(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, BYTE* pDstArray);
	static void prfHash(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, int paramInt, DWORD dwHashFlagId, BYTE* pDstHashBuf, int iDstHashBufBytes);

	static void encryptHMAC(const BYTE* pParamArrayOfByte1, int iParamArray1Bytes, const BYTE* pParamArrayOfByte2, int iParamArray2Bytes, DWORD dwHashFlagId, BYTE * pHashBuf, int iHashBufBytes);
	static void WriteByteArrayToStr(std::string & strDst, const BYTE* pBuf, int iBufBytes);

	static BOOL HMAC(const char * str, const char * password, DWORD dwAlgId/* = CALG_MD5*/, char * pHashBuf, int iHashBufBytes);

	static void CalClientKeyAndServerKey(const std::string & serverKeyData, BOOL bOutLog=FALSE);

	static void getFinalKey(BYTE* pArray1OfByte, int iArray1Bytes, BYTE* pArray2OfByte, int iArray2Bytes, BYTE * pClientKeyArray, int iClientKeyArrayBytes, BYTE * pSeverKeyArray, int iServerKeyArrayBytes);

	static void printByteArray(const char* pArrayNameStr, const BYTE *pBuf, int iEleMentNum);
	//bSplitBySpace位TRUE时，每行16个 用空格隔开的16进制字符，否则输出在一行，紧挨在一起
	static void printStdString(const char* pPrintName, const std::string & str, BOOL bSplitBySpace);
	static void printString(const char* pStrName, const std::string &str);

	//将一个字节中的16进制数转换为两个char， 注意iOutBufLen 中包含\0，pHexBuf 没有用\0结尾，用iHexBufBytes指明实际字节数。
	static void HexByteToTwoChar(unsigned char* pOutBuf, int iOutBufLen, unsigned char* pHexBuf, int iHexBufBytes= CEAIR_ME_SEVER_KEY_LEN);

	static void HexCharToByteArray(unsigned char* pOutBuf, int iOutBufLen, unsigned char* pHexBuf, int iHexBufBytes);

	static BYTE m_u8ClientKey[68];
	static BYTE m_u8ServerKey[68];

private:
	class CEncryptHMACResult
	{
	public:
		CEncryptHMACResult() : m_pBuf(NULL), m_iBufBytes(0)
		{

		}
		~CEncryptHMACResult()
		{
			if(NULL != this->m_pBuf)
			{
				delete this->m_pBuf;
				this->m_pBuf = NULL;
				this->m_iBufBytes = 0;
			}
		}
		CEncryptHMACResult(BYTE *pBufContent, int iBufByteSize) : m_pBuf(NULL), m_iBufBytes(0)
		{
			this->m_pBuf = new BYTE[iBufByteSize];
			this->m_iBufBytes = iBufByteSize;
			memcpy_s(this->m_pBuf, this->m_iBufBytes, pBufContent,  iBufByteSize);
		}
		CEncryptHMACResult & operator=(const CEncryptHMACResult & res)
		{
			if(NULL != this->m_pBuf)
			{
				delete this->m_pBuf;
				this->m_pBuf = NULL;
				this->m_iBufBytes = 0;
			}
			this->m_pBuf = new BYTE[res.m_iBufBytes];
			this->m_iBufBytes = res.m_iBufBytes;
			memcpy_s(this->m_pBuf, this->m_iBufBytes, res.m_pBuf,  res.m_iBufBytes);
			return *this;
		}
	public:
		BYTE*	m_pBuf;
		int		m_iBufBytes;
	};

	static void __ReleaseHashBufMap(std::map<int, CEncryptHMACResult*> & localArrayMap);

};

