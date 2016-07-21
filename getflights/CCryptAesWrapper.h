

#pragma once

#include <string>  
using namespace std;

#include "ByteBuf.h"

class CCryptAesWrapper
{
public:
	CCryptAesWrapper(void){};
	~CCryptAesWrapper(void){};

public:
	static std::string ECB_AESEncryptStr(const std::string & sKey, const char *plainText);  
	static std::string ECB_AESDecryptStr(const std::string & sKey, const char *cipherText);    

	static void CBC_AESEncryptStr(const std::string & sKey, const std::string & sIV, const std::string & strTxt, std::string & strDstCipherTxt);    
	static std::string CBC_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText, bool bHexStr=true); 
	static void CBC_AESDecryptStr2(const std::string & sKey, const std::string & sIV, const std::string & cipherText, std::string & strOut, bool bInputHexStr=true);
	static bool CBC_AESDecryptBufToBuf(const std::string & sKey, const std::string & sIV, const BYTE* pBuf, size_t iBufBytesLen, CByteBuf * pBytebuf);

	static std::string CBC_CTS_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText);     
	static std::string CBC_CTS_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);    

	static std::string CFB_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText);     
	static std::string CFB_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);

	static std::string OFB_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText); 
	static std::string OFB_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);     

	static std::string CTR_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText);
	static std::string CTR_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText);   

	static BOOL gzip_decompress (const void* pInDate, size_t nSize, std::string& raw_data);

	//in指向的字符串要以\0结尾
	static void Base64Encode(const char *in, bool bHexStr, std::string & strResult);
	static void Base64Encode(const BYTE *pBuf, int iElementNum, bool bHexStr, bool bInsertLineBreaks, std::string & strResult);
	static void Base64Encode(const std::string & strSrc, bool bHexStr, bool bInsertLineBreaks, std::string & strResult);
	//in指向的字符串要以\0结尾
	static void Base64Decode(const char *in,  std::string & strResult);
	static void Base64Decode(const std::string & strSrc,  std::string & strResult);
	//base64解码一段buf，buf长度由iBufBytesLen指定,
	static bool Base64DecodeBufToBuf(const BYTE *in,  size_t iBufBytesLen, CByteBuf * pBytebuf);
	//in指向的字符串要以\0结尾
	static void DecodeHexString(const char *in, std::string & strResult);
	//DecodeHexStrToBinBuf功能：
	//将16进制的字符串转成二进制串
	//将16进制串中的每两个字符转成一个字节，分别占整个字节的高低4位.如果16进制字串长度不是2的倍数，最后字符会被舍弃掉
	//如果16进制串的长度（不含\0）是2的倍数，则转换后的二进制串长度是转换前的一半，
	//如果16进制串的长度（不含\0）不是2的倍数，则转换后的二进制串长度是转换前的一半，16进制串最后一个字符舍弃掉不转换
	static void DecodeHexStrToBinBuf(const std::string & strHexSrc, std::string & strBinDst);
	static void DecodeHexStrToBinBuf(const BYTE* pHexBuf, int iElmentNum, std::string & strBinDst);
	//EncodeBinBufToHexStr功能：
	//将字节buf中的数值转换成16进制字符型的buf。每个字节的高低4位分别转成一个16进制字符，存放在一个字节中
	//十进制的0～9转成16进制的0X30~0X39,十进制的10～15转成16进制的0X41～0X46
	//转换后的字串长度是是字节数组长度的2倍
	static void EncodeBinBufToHexStr(const BYTE* pBuf, int iElementNum, std::string & strHex);
	static void EncodeBinBufToHexStr(const std::string & strBinBuf, std::string & strHex);

	//解压\0结尾的字符串
	static void GunzipString(std::string & strComproessed, std::string & strOut);
	//解压一段buf，buf长度由iBufBytesLen指定
	static bool GunzipBuf(const BYTE* pBuf, int iBufBytesLen, std::string & strOut);
	//解压一段buf，buf长度由iBufBytesLen指定,
	static bool GunzipBufToBuf(const BYTE* pBuf, size_t iBufBytesLen, CByteBuf * pBytebuf);
};

