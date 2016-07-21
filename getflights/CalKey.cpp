
#include "stdafx.h"
#include "CalKey.h"
#include "CeairMobileEConst.h"

#include "HMAC_SHA1.h"
#include "HMAC_MD5_API.h"
#include "FixByteArray.h"

//此宏仅在Debug模式下开关输出窗口中的调试信息
//#define PRINT_CEAIR_LOG

#include <list>
#include <map>
using namespace std;

typedef struct _my_blob{
	BLOBHEADER header;
	DWORD len;
	BYTE key[0];
}my_blob;


#pragma comment(lib, "crypt32.lib")


BYTE CCalKey::m_u8ClientKey[68] = {0};
BYTE CCalKey::m_u8ServerKey[68] = {0};

CCalKey::CCalKey(void)
{

}

CCalKey::~CCalKey(void)
{

}

void CCalKey::BYTEArrayCopy(const BYTE *pu8SrcBuf, int iSrcBufCopyPos, BYTE *pu8DstBuf, int iDstBufCopyPos, int iCopyByte)
{
	memcpy_s(pu8DstBuf+iDstBufCopyPos, iCopyByte, pu8SrcBuf+iSrcBufCopyPos, iCopyByte);
}
//pu8DstArray = pu8Array1 + pu8Array2
void CCalKey::JoinByteArray(const BYTE *pu8Array1, int iArray1Bytes, const BYTE *pu8Array2, int iArray2Bytes, BYTE *pu8DstArray, int iDstArrayBytes)
{
	BYTEArrayCopy(pu8Array1, 0, pu8DstArray, 0, iArray1Bytes);
	BYTEArrayCopy(pu8Array2, 0, pu8DstArray, iArray1Bytes, iArray2Bytes);
}

void CCalKey::printByteArray(const char* pArrayNameStr, const BYTE *pBuf, int iEleMentNum)
{
#ifdef PRINT_CEAIR_LOG
	TRACE("\r\n%s :", pArrayNameStr);
	const BYTE *pTmp = pBuf;
	for (int i = 0; i < iEleMentNum; i++)
	{
		TRACE("%02X", *pTmp);
		pTmp++;
	}
#endif
}

void CCalKey::printStdString(const char* pPrintName, const std::string & str, BOOL bSplitBySpace)
{
#ifdef PRINT_CEAIR_LOG
	BYTE * pBuf = (BYTE*)str.data();
	int iElementNum = str.size();
	if (bSplitBySpace)
	{
		TRACE("\r\n%s\r\n", pPrintName);
		for (int i = 0; i < iElementNum; i++)
		{
			if (0 != i && 0 == (i %16))
			{
				TRACE(_T("\r\n"));
			}
			TRACE("%02X ", *pBuf);
			pBuf++;
		}
	}
	else
	{
		TRACE("\r\n%s:", pPrintName);
		for (int i = 0; i < iElementNum; i++)
		{
			TRACE("%c", *pBuf);
			pBuf++;
		}
	}
#endif
}
void CCalKey::CalClientKeyAndServerKey(const std::string & serverKeyData, BOOL bOutLog)
{
	BYTE* pServerKeyData = (BYTE*)serverKeyData.c_str();
	BYTE arrayOfByte3[4] = {0};
	BYTEArrayCopy(pServerKeyData, 0, arrayOfByte3, 0, 4);    
	BYTE arrayOfByte4[28] = {0};
	BYTEArrayCopy(pServerKeyData, 4, arrayOfByte4, 0, 28);

	BYTE arrayOfByte5[2] = {0};
	BYTEArrayCopy(pServerKeyData, 32, arrayOfByte5, 0, 2);
	BYTE arrayOfByte6[46] = {0};
	BYTEArrayCopy(pServerKeyData, 34, arrayOfByte6, 0, 46);
	printByteArray("arrayOfByte5", arrayOfByte5, 2);
	printByteArray("arrayOfByte6", arrayOfByte6, 46);

	BYTE arrayOfByte7[20] = {0};
	BYTEArrayCopy(pServerKeyData, 80, arrayOfByte7, 0, 20);

	BYTE arrayOfByte9[48] = {0};
	JoinByteArray(arrayOfByte5, 2, arrayOfByte6, 46, arrayOfByte9, 48);
	printByteArray("arrayOfByte9", arrayOfByte9, 48);
	//RNC_ + RNS_ 共64字节
	BYTE  arrayOfByte11[64] = {0};
	JoinByteArray(RNC_, 32, RNS_, 32, arrayOfByte11, 64);
	printByteArray("arrayOfByte11", arrayOfByte11, 64);

	//byte[] PMS2_ = arrayOfByte9;
	//byte[][] arrayOfByte10 = new byte[2][];
	//arrayOfByte10[0] = RNC_;
	//arrayOfByte10[1] = RNS_;
	//byte[] arrayOfByte11 = jogBytes(arrayOfByte10);

	BYTE MS2_[48] = {0};
	CreateMasterSecret(arrayOfByte9, 48, MasterConst, 14, arrayOfByte11, 64, 48, MS2_, 48);
	printByteArray("CreateMasterSecret MS2_", MS2_, 48);
	//byte[] MS2_ = createMasterSecret(arrayOfByte9, masterConst,arrayOfByte11,48);
	//getFinalKey(MS2_, arrayOfByte11);

	
	SecureZeroMemory(m_u8ClientKey, sizeof(m_u8ClientKey));
	SecureZeroMemory(m_u8ServerKey, sizeof(m_u8ServerKey));
	getFinalKey(MS2_, 48, arrayOfByte11, 64, m_u8ClientKey, 68, m_u8ServerKey, 68);

	if (bOutLog)
	{
		FILE *pStream = NULL;
		int  numwritten = 0;
		char *pFilePath = "ceairlog_key.log";
		char szClientKeyStr[]="clientKey:";
		char szServerKeyStr[]="serverKey:";
		if( fopen_s( &pStream, pFilePath, "a+b" ) == 0 )
		{
			numwritten = fwrite( szClientKeyStr, 1, strlen(szClientKeyStr), pStream );
			numwritten = fwrite( m_u8ClientKey, 1, 68, pStream );
			numwritten = fwrite( szServerKeyStr, 1, strlen(szServerKeyStr), pStream );
			numwritten = fwrite( m_u8ServerKey, 1, 68, pStream );
			fclose( pStream );
		}
	}
#ifdef _DEBUG
	TRACE(_T("\r\nfinal client key:"));
	for (int i = 0; i < 68; i++)
	{
		//if (0 != i && 0 == (i %16))
		//{
		//	TRACE(_T("\r\n"));
		//}
		//TRACE("%02X ", dstClientKey[i]);
		TRACE("%02X", m_u8ClientKey[i]);
	}
	TRACE(_T("\r\nfinal server key:"));
	for (int i = 0; i < 68; i++)
	{
		//if (0 != i && 0 == (i %16))
		//{
		//	TRACE(_T("\r\n"));
		//}
		//TRACE("%02X ", dstServerKey[i]);
		TRACE("%02X", m_u8ServerKey[i]);
	}
#endif
}

void CCalKey::CreateMasterSecret(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, const BYTE * pByteArray3, int iByteArray3Bytes, int paramInt, BYTE *pDestArray, int iDstArrayBytes)
{
	PRF(pByteArray1, iByteArray1Bytes, pByteArray2, iByteArray2Bytes, pByteArray3, iByteArray3Bytes, paramInt, pDestArray, iDstArrayBytes);
}

void CCalKey::PRF(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, const BYTE * pByteArray3, int iByteArray3Bytes, int paramInt, BYTE *pDestArray, int iDstArrayBytes)
{
	int i = 1;
	if (iByteArray1Bytes % 2 != 0)
		return;

	int n = iByteArray1Bytes / 2;

	BYTE* pByteBuf1 = new BYTE[n];
	BYTE* pByteBuf2 = new BYTE[n];
	BYTEArrayCopy(pByteArray1, 0, pByteBuf1, 0, n);
	BYTEArrayCopy(pByteArray1, n, pByteBuf2, 0, n);
	int nByteBuf3Bytes = iByteArray2Bytes + iByteArray3Bytes;
	BYTE* pByteBuf3 = new BYTE[nByteBuf3Bytes];
	BYTEArrayCopy(pByteArray2, 0, pByteBuf3, 0, iByteArray2Bytes);
	BYTEArrayCopy(pByteArray3, 0, pByteBuf3, iByteArray2Bytes, iByteArray3Bytes);
	printByteArray("pByteBuf1", pByteBuf1, n);
	printByteArray("pByteBuf2", pByteBuf2, n);
	printByteArray("pByteBuf3", pByteBuf3, nByteBuf3Bytes);

	BYTE *pDstHashBuf1 = new BYTE[paramInt];
	SecureZeroMemory(pDstHashBuf1, paramInt);
	BYTE *pDstHashBuf2 = new BYTE[paramInt];
	SecureZeroMemory(pDstHashBuf2, paramInt);
	prfHash(pByteBuf1, n, pByteBuf3, nByteBuf3Bytes, paramInt, CALG_MD5, pDstHashBuf1, paramInt);
	prfHash(pByteBuf2, n, pByteBuf3, nByteBuf3Bytes, paramInt, CALG_SHA1, pDstHashBuf2, paramInt);

	xorArray(pDstHashBuf1, paramInt, pDstHashBuf2, paramInt, pDestArray);
}

void CCalKey::printString(const char* pStrName, const std::string &str)
{
#ifdef PRINT_CEAIR_LOG
	TRACE("\r\n%s:", pStrName);
	const char * pTmp = str.c_str();
	int iLen = str.length();
	BYTE u8 = 0;
	for(int i = 0; i < iLen; i++)
	{
		u8 = *pTmp;
		TRACE("%02X", u8);
		pTmp++;
	}
#endif
}
void CCalKey::__ReleaseHashBufMap(std::map<int, CEncryptHMACResult*> & hmacResultMap)
{
	CEncryptHMACResult * pRes = NULL;
	for (std::map<int, CEncryptHMACResult*>::iterator it = hmacResultMap.begin(); it != hmacResultMap.end(); it++)
	{
		pRes = it->second;
		delete pRes;
		pRes = NULL;
	}
	hmacResultMap.clear();
}
void CCalKey::prfHash(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, int paramInt, DWORD dwHashFlagId, BYTE* pDstHashBuf, int iDstHashBufBytes)
{
	std::map<int, CEncryptHMACResult*> localArrayMap;//key为元素Id， value为hash计算的结果buf
	localArrayMap.clear();

	int iHashBufId = 0;
	CEncryptHMACResult* pHashRes = new CEncryptHMACResult(const_cast<BYTE*>(pByteArray2), iByteArray2Bytes);
	localArrayMap.insert(pair<int, CEncryptHMACResult*>(iHashBufId, pHashRes));
	std::map<int, CEncryptHMACResult*>::reverse_iterator mapIt = localArrayMap.rbegin();
	CFixByteArray fixArray;

	int iLen = 16;
	if (CALG_MD5 == dwHashFlagId)
	{
		iLen = 16;
	}
	else if(CALG_SHA1 == dwHashFlagId)
	{
		iLen = 20;
	}
	else
	{
		ASSERT(0);
	}
	int iHashBufBytes = iLen;
	BYTE * pHashBuf1 = new BYTE[iHashBufBytes];
	SecureZeroMemory(pHashBuf1, iHashBufBytes);
	BYTE * pHashBuf2 = new BYTE[iHashBufBytes];
	SecureZeroMemory(pHashBuf2, iHashBufBytes);
	int iencryptHMAC2BufBytes = iHashBufBytes + iByteArray2Bytes;
	BYTE* pEncryptHMAC2Buf = new BYTE[iencryptHMAC2BufBytes];
	SecureZeroMemory(pEncryptHMAC2Buf, iencryptHMAC2BufBytes);

	CEncryptHMACResult* pLastHashRes = NULL;
	while (1)
	{
		if (fixArray.GetCurElementNum() >= paramInt)
		{
			fixArray.CopyBuf(pDstHashBuf, iDstHashBufBytes);
			printByteArray("prfHash return", pDstHashBuf, iDstHashBufBytes);
			goto prfHash_Ret;
		}
		mapIt = localArrayMap.rbegin();
		pLastHashRes = mapIt->second;
		encryptHMAC(pLastHashRes->m_pBuf, pLastHashRes->m_iBufBytes, (BYTE*)pByteArray1, iByteArray1Bytes, dwHashFlagId, pHashBuf1, iHashBufBytes);
		printByteArray("prfHash encryptHMAC hashbuf", pHashBuf1, iHashBufBytes);
		CEncryptHMACResult* pNewHashRes = new CEncryptHMACResult(pHashBuf1, iHashBufBytes);
		iHashBufId++;
		localArrayMap.insert(pair<int, CEncryptHMACResult*>(iHashBufId, pNewHashRes));
		JoinByteArray(pHashBuf1, iHashBufBytes, pByteArray2, iByteArray2Bytes, pEncryptHMAC2Buf, iencryptHMAC2BufBytes);
		encryptHMAC(pEncryptHMAC2Buf, iencryptHMAC2BufBytes, pByteArray1, iByteArray1Bytes, dwHashFlagId, pHashBuf2, iHashBufBytes);
		fixArray.AppendArray(pHashBuf2, iHashBufBytes);
#ifdef PRINT_CEAIR_LOG
		fixArray.Dump("******prfHashfixArray");
#endif
	}

prfHash_Ret:

	__ReleaseHashBufMap(localArrayMap);

	delete [] pHashBuf1;
	pHashBuf1 = NULL;

	delete [] pHashBuf2;
	pHashBuf2 = NULL;

	delete [] pEncryptHMAC2Buf;
	pEncryptHMAC2Buf = NULL;
	localArrayMap.clear();
}

void CCalKey::WriteByteArrayToStr(std::string & strDst, const BYTE* pBuf, int iBufBytes)
{
	char* pTmpBuf = new char[iBufBytes+1];
	SecureZeroMemory(pTmpBuf, iBufBytes+1);
	memcpy(pTmpBuf, pBuf, iBufBytes);
	*(pTmpBuf+iBufBytes) = '\0';
	strDst = strDst + pTmpBuf;

	delete [] pTmpBuf;
	pTmpBuf = NULL;
}
//pParamArrayOfByte1-待加密字串， pParamArrayOfByte2-密钥字串
void CCalKey::encryptHMAC(const BYTE* pParamArrayOfByte1, int iParamArray1Bytes, const BYTE* pParamArrayOfByte2, int iParamArray2Bytes, DWORD dwHashFlagId, BYTE * pHashBuf, int iHashBufBytes)
{
	//SecureZeroMemory(pHashBuf, iHashBufBytes);
	//BOOL bOk = HMAC((char*)pParamArrayOfByte1, (char*)pParamArrayOfByte2, dwHashFlagId, (char*)pHashBuf, iHashBufBytes);
	if (CALG_SHA1 == dwHashFlagId)
	{
		//BYTE Key[20] ;
		//BYTE digest[20] ; 

		//unsigned char *test = "Hi There" ; 
		//memset(Key, 0x0b, 20) ;
		//CHMAC_SHA1 HMAC_SHA1 ;
		//HMAC_SHA1.HMAC_SHA1(test, strlen(test), Key, sizeof(Key), digest) ;
		printByteArray("encryptHMAC SHA1 pParamArrayOfByte1", pParamArrayOfByte1, iParamArray1Bytes);
		printByteArray("encryptHMAC SHA1 pParamArrayOfByte2", pParamArrayOfByte2, iParamArray2Bytes);
		CHMAC_SHA1 HMAC_SHA1 ;
		HMAC_SHA1.HMAC_SHA1((BYTE*)pParamArrayOfByte1, iParamArray1Bytes, (BYTE*)pParamArrayOfByte2, iParamArray2Bytes, pHashBuf) ;
		printByteArray("encryptHMAC SHA1 return ", pHashBuf, iHashBufBytes);
	}
	else if (CALG_MD5 == dwHashFlagId)
	{	
		printByteArray("encryptHMAC MD5 pParamArrayOfByte1", pParamArrayOfByte1, iParamArray1Bytes);
		printByteArray("encryptHMAC MD5 pParamArrayOfByte2", pParamArrayOfByte2, iParamArray2Bytes);
		int nBytes = HMAC_MD5_Hash((BYTE*)pParamArrayOfByte1, iParamArray1Bytes, (BYTE*)pParamArrayOfByte2, iParamArray2Bytes, pHashBuf);
		printByteArray("encryptHMAC MD5 return ", pHashBuf, iHashBufBytes);
		//TRACE(_T("\r\n HMAC_MD5_Hash return %d bytes\r\n"), nBytes);
	}
	else
	{

	}
}

BOOL CCalKey::HMAC(const char * str, const char * password, DWORD dwAlgId/* = CALG_MD5*/, char * pHashBuf, int iHashBufBytes)
{
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HCRYPTKEY hKey = 0;
	HCRYPTHASH hHmacHash = 0;
	BYTE * pbHash = 0;
	DWORD dwDataLen = 0;
	HMAC_INFO HmacInfo;
	ZeroMemory(&HmacInfo, sizeof(HmacInfo));
	BOOL bOk = FALSE;
	SecureZeroMemory(pHashBuf, iHashBufBytes);

	int err = 0;

	if (dwAlgId == CALG_MD5)
	{
		HmacInfo.HashAlgid = CALG_MD5;
		pbHash = new BYTE[16];
		dwDataLen = 16;
	}
	else if(dwAlgId == CALG_SHA1)
	{
		HmacInfo.HashAlgid = CALG_SHA1;
		pbHash = new BYTE[20];
		dwDataLen = 20;
	}
	else
	{
		return bOk;
	}

	ZeroMemory(pbHash, sizeof(dwDataLen));

	my_blob * kb = NULL;
	DWORD kbSize = sizeof(my_blob) + strlen(password);

	kb = (my_blob*)malloc(kbSize);
	kb->header.bType = PLAINTEXTKEYBLOB;
	kb->header.bVersion = CUR_BLOB_VERSION;
	kb->header.reserved = 0;
	kb->header.aiKeyAlg = CALG_RC2;
	memcpy(&kb->key, password, strlen(password));
	kb->len = strlen(password);

	if (!CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL,CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET))
	{
		err = 1;
		goto Exit;
	}

	if (!CryptImportKey(hProv, (BYTE*)kb, kbSize, 0, CRYPT_IPSEC_HMAC_KEY, &hKey))
	{
		err = 1;
		goto Exit;
	}

	if (!CryptCreateHash(hProv, CALG_HMAC, hKey, 0, &hHmacHash))
	{
		err = 1;
		goto Exit;
	}

	if (!CryptSetHashParam(hHmacHash, HP_HMAC_INFO, (BYTE*)&HmacInfo, 0))
	{
		err = 1;
		goto Exit;
	}

	if (!CryptHashData(hHmacHash, (BYTE*)str, strlen(str), 0))
	{
		err = 1;
		goto Exit;
	}

	if (!CryptGetHashParam(hHmacHash, HP_HASHVAL, pbHash, &dwDataLen, 0))
	{
		err = 1;
		goto Exit;
	}

	char * temp;
	temp = new char[3];
	ZeroMemory(temp, 3);
	for (unsigned int m = 0; m < dwDataLen; m++)
	{
		sprintf(temp, "%2x", pbHash[m]);
		if (temp [1] == ' ') 
			temp [1] = '0'; // note these two: they are two CORRECTIONS to the conversion in HEX, sometimes the Zeros are
		if (temp [0] == ' ') 
			temp [0] = '0'; // printed with a space, so we replace spaces with zeros; (this error occurs mainly in HMAC-SHA1)
		sprintf(pHashBuf,"%s%s", pHashBuf, temp);
	}

	delete [] temp;

Exit:
	free(kb);
	if(hHmacHash)
		CryptDestroyHash(hHmacHash);
	if(hKey)
		CryptDestroyKey(hKey);
	if(hHash)
		CryptDestroyHash(hHash);
	if(hProv)
		CryptReleaseContext(hProv, 0);

	if (err == 1)
	{
		bOk = FALSE;
	}
	else
		bOk = TRUE;

	return bOk;
}

void CCalKey::xorArray(const BYTE * pByteArray1, int iByteArray1Bytes, const BYTE * pByteArray2, int iByteArray2Bytes, BYTE* pDstArray)
{
	TRACE(_T("\r\nCCalKey::xorArray()"));
	BYTE* pTmp = pDstArray;
	BYTE* pBuf1 = (BYTE*)pByteArray1;
	BYTE* pBuf2 = (BYTE*)pByteArray2;

	printByteArray("pBuf1", pBuf1, iByteArray1Bytes);
	printByteArray("pBuf2", pBuf2, iByteArray2Bytes);
	for (int i = 0; i < iByteArray1Bytes; i++)
	{
		*pTmp = *pBuf1 ^ *pBuf2;
		pTmp++;
		pBuf1++;
		pBuf2++;
	}
	printByteArray("xor desBuf", pDstArray, iByteArray1Bytes);
}

void CCalKey::getFinalKey(BYTE* pArray1OfByte, int iArray1Bytes, BYTE* pArray2OfByte, int iArray2Bytes, BYTE * pClientKeyArray, int iClientKeyArrayBytes, BYTE * pSeverKeyArray, int iServerKeyArrayBytes)
{		
	BYTE dstBuf[136] = {0};
	//SecureZeroMemory(pDstBuf, 136);
	printByteArray("getFinalKey PRF pArray1OfByte", pArray1OfByte, iArray1Bytes);
	printByteArray("getFinalKey PRF ServerConst", ServerConst, 13);
	printByteArray("getFinalKey PRF pArray2OfByte", pArray2OfByte, iArray2Bytes);

	PRF(pArray1OfByte, iArray1Bytes, ServerConst, 13, pArray2OfByte, iArray2Bytes, 136, dstBuf, 136);
	printByteArray("getFinalKey PRF dstBuf", dstBuf, 136);
	BYTEArrayCopy(dstBuf, 0, pClientKeyArray, 0, 68);
	BYTEArrayCopy(dstBuf, 68, pSeverKeyArray, 0, 68);

	//delete [] pDstBuf;
	//pDstBuf = NULL;
}

void CCalKey::HexByteToTwoChar(unsigned char* pOutBuf, int iOutBufLen, unsigned char* pHexBuf, int iHexBufBytes)
{
	unsigned char* pChar = pOutBuf;
	unsigned char u8Tmp = 0;
	TRACE("\r\nEncrypt severkey:\r\n");
	for (int i = 0; i < iHexBufBytes; i++)
	{
		u8Tmp = ((*pHexBuf) & 0XF0)>>4;
		if (u8Tmp >=0 && u8Tmp <= 9)
		{
			//0~9转为0X31～0X39
			u8Tmp = u8Tmp + 0X30;
		}
		else//10～15
		{
			//10~15转为0X41～0X46，即大写字母A～F
			u8Tmp = u8Tmp + 0X37;
		}
		*pChar = u8Tmp;

		u8Tmp = (*pHexBuf) & 0X0F;
		if (u8Tmp >=0 && u8Tmp <= 9)
		{
			//0~9转为0X31～0X39
			u8Tmp = u8Tmp + 0X30;
		}
		else//10～15
		{
			//10~15转为0X41～0X46，即大写字母A～F
			u8Tmp = u8Tmp + 0X37;
		}
		*(pChar+1) = u8Tmp;
		TRACE("%c%c", *pChar, *(pChar+1));
		pChar = pChar+2;
		pHexBuf++;
	}
	*pChar = '\0';
}

void CCalKey::HexCharToByteArray(unsigned char* pOutBuf, int iOutBufLen, unsigned char* pHexBuf, int iHexBufBytes)
{

}