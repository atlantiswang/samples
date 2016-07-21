
#include "stdafx.h"

#include "dll.h"
#include "filters.h"
#include "CCryptAesWrapper.h"
#include "./Cryptopp/base64.h"

#include <aes.h>  
#include <Hex.h>      // StreamTransformationFilter  
#include <modes.h>    // CFB_Mode  
#include <gzip.h>
#include <iostream>              // std:cerr    
#include <sstream>               // std::stringstream    
#include <string>  

#include "./common/zlib/gzip.h"

USING_NAMESPACE(CryptoPP)
//USING_NAMESPACE(std)
//#pragma comment( lib, "cryptlib.lib" )  

std::string CCryptAesWrapper::ECB_AESEncryptStr(const std::string & sKey, const char *plainText)  
{  
	std::string outstr;  

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    


	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    

	ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);  
	StreamTransformationFilter ecbEncryptor(ecbEncryption, new HexEncoder(new StringSink(outstr)));    
	ecbEncryptor.Put((byte *)plainText, strlen(plainText));    
	ecbEncryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::ECB_AESDecryptStr(const std::string & sKey, const char *cipherText)    
{    
	std::string outstr;    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	ECB_Mode<AES >::Decryption ecbDecryption((byte *)key, AES::MAX_KEYLENGTH);    

	HexDecoder decryptor(new StreamTransformationFilter(ecbDecryption, new StringSink(outstr)));    
	decryptor.Put((byte *)cipherText, strlen(cipherText));    
	decryptor.MessageEnd();    

	return outstr;    
}    

void CCryptAesWrapper::CBC_AESEncryptStr(const std::string & sKey, const std::string & sIV, const std::string & strTxt, std::string & strDstCipherTxt)  
{  

	//填key    
	int iMaxKeyLength = AES::MAX_KEYLENGTH;
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );
	int iSKeySize = sKey.size();
	if (sKey.size()<=AES::MAX_KEYLENGTH)
		memcpy(key,sKey.c_str(),sKey.size());
	else
		memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);  
	int iIvSize = sIV.size();
	if(sIV.size()<=AES::BLOCKSIZE)
		memcpy(iv,sIV.c_str(),sIV.size());
	else
		memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

/*	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    

	CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);    

	StreamTransformationFilter cbcEncryptor(cbcEncryption, new HexEncoder(new StringSink(outstr)));    
	cbcEncryptor.Put((byte *)plainText, strlen(plainText));    
	cbcEncryptor.MessageEnd(); */ 


	CBC_Mode< AES >::Encryption e;
	e.SetKeyWithIV((byte *)key, key.size(), iv);

	StreamTransformationFilter filter(e, NULL, CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING);
	filter.Put((const byte*)strTxt.data(), strTxt.size());
	filter.MessageEnd();

	const size_t ret = filter.MaxRetrievable();
	strDstCipherTxt.resize(ret);
	filter.Get((byte*)strDstCipherTxt.data(), strDstCipherTxt.size());
}    

std::string CCryptAesWrapper::CBC_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText, bool bHexStr)    
{    
	std::string outstr("");    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key, 0x30, key.size() );  

	if(sKey.size()<=AES::MAX_KEYLENGTH)
		memcpy(key,sKey.c_str(),sKey.size());
	else
		memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv, 0x30, AES::BLOCKSIZE);    
	if(sIV.size()<=AES::BLOCKSIZE)
		memcpy(iv,sIV.c_str(),sIV.size());
	else
		memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	CBC_Mode<AES >::Decryption cbcDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    

	if(bHexStr)
	{
		HexDecoder decryptor(new StreamTransformationFilter(cbcDecryption, new StringSink(outstr), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));    
		int iLen = strlen(cipherText);
		decryptor.Put((byte *)cipherText, iLen);    
		decryptor.MessageEnd(); 


		//CryptoPP::StringSource( cipherText, true,
		//	new CryptoPP::StreamTransformationFilter( cbcDecryption,
		//	new CryptoPP::StringSink( outstr ),
		//	CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
		//	) // StreamTransformationFilter
		//	); // StringSource


		//StringSource(cipherText, true,
		//	new StreamTransformationFilter( cbcDecryption,
		//	new StringSink( outstr ),
		//	BlockPaddingSchemeDef::BlockPaddingScheme::ONE_AND_ZEROS_PADDING,
		//	true)
		//	);

		//输入的字符串编码成16进制的字符串
		//string strEncodedCipherText;
		//StringSource ss((const byte*)cipherText, icipherTextCharNum, true,
		//	new HexEncoder(
		//	new StringSink(strEncodedCipherText)
		//	) // HexEncoder
		//	); // StringSource
	}
	else
	{
		CryptoPP::StringSource s(cipherText, true, 
			new StreamTransformationFilter(cbcDecryption, new StringSink(outstr) ) // StreamTransformationFilter
			); // StringSource
	}

	return outstr;   
}    

void CCryptAesWrapper::CBC_AESDecryptStr2(const std::string & sKey, const std::string & sIV, const std::string & cipherText, std::string & strOut, bool bInputHexStr)
{
	std::string strDec("");    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key, 0x30, key.size() );  

	if(sKey.size()<=AES::MAX_KEYLENGTH)
		memcpy(key,sKey.c_str(),sKey.size());
	else
		memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv, 0x30, AES::BLOCKSIZE);    
	if(sIV.size()<=AES::BLOCKSIZE)
		memcpy(iv,sIV.c_str(),sIV.size());
	else
		memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	CBC_Mode<AES >::Decryption cbcDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    

	if(bInputHexStr)
	{
		//以下这种方式可以输出结果，但string析构时会出现堆破坏错误，原因与cryptopp库的内存管理机制有关，如果修改？？
		//std::string hexDecStr;
		//StringSource ss(cipherText, true,
		//	new HexDecoder(
		//	new StringSink(hexDecStr)
		//	) // HexDecoder
		//	); // StringSource

		//CryptoPP::StringSource s(hexDecStr, true, 
		//	new StreamTransformationFilter(cbcDecryption, new StringSink(strDec) ) // StreamTransformationFilter
		//	); // StringSource
		//strOut = strDec;
		//end 会奔溃的代码

		std::string hexDecStr;
		HexDecoder hexDec;
		hexDec.Put( (byte*)cipherText.data(), cipherText.size() );
		hexDec.MessageEnd();

		word64 size = hexDec.MaxRetrievable();
		if(size && size <= SIZE_MAX)
		{
			hexDecStr.resize(size);		
			hexDec.Get((byte*)hexDecStr.data(), hexDecStr.size());
		}

		StreamTransformationFilter filter(cbcDecryption, NULL, CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING);
		filter.Put((const byte*)hexDecStr.data(), hexDecStr.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		if(ret && ret <= SIZE_MAX)
		{
			strDec.resize(ret);
			filter.Get((byte*)strDec.data(), strDec.size());
		}

		strOut = strDec;

		//CryptoPP::StringSource( cipherText, true,
		//	new CryptoPP::StreamTransformationFilter( cbcDecryption,
		//	new CryptoPP::StringSink( outstr ),
		//	CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
		//	) // StreamTransformationFilter
		//	); // StringSource


		//CryptoPP::StringSource s2((const byte*)cipherText, true,
		//	new CryptoPP::HexDecoder(
		//	new CryptoPP::StreamTransformationFilter( cbcDecryption, new CryptoPP::StringSink( outstr ), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING)//StreamTransformationFilter
		//	) //HexDecoder
		//	);


		//CryptoPP::StringSource s(cipherText, true, 
		//	new StreamTransformationFilter(cbcDecryption, new StringSink(outstr), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING) // StreamTransformationFilter
		//	); // StringSource
	}
	else
	{
		//CryptoPP::StringSource s(cipherText, true, 
		//	new StreamTransformationFilter(cbcDecryption, new StringSink(strDec) ) // StreamTransformationFilter
		//	); // StringSource

		StreamTransformationFilter filter(cbcDecryption, NULL, CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING);
		filter.Put((const byte*)cipherText.data(), cipherText.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		if(ret && ret <= SIZE_MAX)
		{
			strDec.resize(ret);
			filter.Get((byte*)strDec.data(), strDec.size());
		}

		strOut = strDec;
	} 
}
bool CCryptAesWrapper::CBC_AESDecryptBufToBuf(const std::string & sKey, const std::string & sIV, const BYTE* pBuf, size_t iBufBytesLen, CByteBuf * pBytebuf)
{
	bool bOk = false;
	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key, 0x30, key.size() );  

	if(sKey.size()<=AES::MAX_KEYLENGTH)
		memcpy(key,sKey.c_str(),sKey.size());
	else
		memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv, 0x30, AES::BLOCKSIZE);    
	if(sIV.size()<=AES::BLOCKSIZE)
		memcpy(iv,sIV.c_str(),sIV.size());
	else
		memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	CBC_Mode<AES >::Decryption cbcDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    
	StreamTransformationFilter filter(cbcDecryption);
	filter.Put((const byte*)pBuf, iBufBytesLen);
	filter.MessageEnd();

	const size_t avail = filter.MaxRetrievable();
	if(avail)
	{
		pBytebuf->Resize(avail);
		filter.Get((byte*)pBytebuf->GetBufPtr(), pBytebuf->Size());
		bOk = true;
	}

	return bOk;
}
std::string CCryptAesWrapper::CBC_CTS_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText)  
{  
	std::string outstr;  

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);   
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    

	CBC_CTS_Mode_ExternalCipher::Encryption cbcctsEncryption(aesEncryption, iv);    

	StreamTransformationFilter cbcctsEncryptor(cbcctsEncryption, new HexEncoder(new StringSink(outstr)));    
	cbcctsEncryptor.Put((byte *)plainText, strlen(plainText));    
	cbcctsEncryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::CBC_CTS_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText)    
{    
	std::string outstr;    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);    
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	CBC_CTS_Mode<AES >::Decryption cbcctsDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    

	HexDecoder decryptor(new StreamTransformationFilter(cbcctsDecryption, new StringSink(outstr)));    
	decryptor.Put((byte *)cipherText, strlen(cipherText));    
	decryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::CFB_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText)  
{  
	std::string outstr;  

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);   
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    

	CFB_Mode_ExternalCipher::Encryption cfbEncryption(aesEncryption, iv);    

	StreamTransformationFilter cfbEncryptor(cfbEncryption, new HexEncoder(new StringSink(outstr)));    
	cfbEncryptor.Put((byte *)plainText, strlen(plainText));    
	cfbEncryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::CFB_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText)    
{    
	std::string outstr;    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);    
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	CFB_Mode<AES >::Decryption cfbDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    

	HexDecoder decryptor(new StreamTransformationFilter(cfbDecryption, new StringSink(outstr)));    
	decryptor.Put((byte *)cipherText, strlen(cipherText));    
	decryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::OFB_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText)  
{  
	std::string outstr;  

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);   
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    

	OFB_Mode_ExternalCipher::Encryption ofbEncryption(aesEncryption, iv);    

	StreamTransformationFilter ofbEncryptor(ofbEncryption, new HexEncoder(new StringSink(outstr)));    
	ofbEncryptor.Put((byte *)plainText, strlen(plainText));    
	ofbEncryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::OFB_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText)    
{    
	std::string outstr;    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);    
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	OFB_Mode<AES >::Decryption ofbDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    

	HexDecoder decryptor(new StreamTransformationFilter(ofbDecryption, new StringSink(outstr)));    
	decryptor.Put((byte *)cipherText, strlen(cipherText));    
	decryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::CTR_AESEncryptStr(const std::string & sKey, const std::string & sIV, const char *plainText)  
{  
	std::string outstr;  

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);   
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);    

	CTR_Mode_ExternalCipher::Encryption ctrEncryption(aesEncryption, iv);    

	StreamTransformationFilter ctrEncryptor(ctrEncryption, new HexEncoder(new StringSink(outstr)));    
	ctrEncryptor.Put((byte *)plainText, strlen(plainText));    
	ctrEncryptor.MessageEnd();    

	return outstr;    
}    

std::string CCryptAesWrapper::CTR_AESDecryptStr(const std::string & sKey, const std::string & sIV, const char *cipherText)    
{    
	std::string outstr;    

	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);    
	memset(key,0x30,key.size() );    
	sKey.size()<=AES::MAX_KEYLENGTH?memcpy(key,sKey.c_str(),sKey.size()):memcpy(key,sKey.c_str(),AES::MAX_KEYLENGTH);    

	//填iv    
	byte iv[AES::BLOCKSIZE];    
	memset(iv,0x30,AES::BLOCKSIZE);    
	sIV.size()<=AES::BLOCKSIZE?memcpy(iv,sIV.c_str(),sIV.size()):memcpy(iv,sIV.c_str(),AES::BLOCKSIZE);  

	CTR_Mode<AES >::Decryption ctrDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);    

	HexDecoder decryptor(new StreamTransformationFilter(ctrDecryption, new StringSink(outstr)));    
	decryptor.Put((byte *)cipherText, strlen(cipherText));    
	decryptor.MessageEnd();    

	return outstr;    
}    

BOOL CCryptAesWrapper::gzip_decompress (const void* pInDate, size_t nSize, std::string& raw_data)
{
	z_stream   zs ;
	ZeroMemory (&zs, sizeof(zs)) ;

	std::vector<BYTE>   temp_buf (8 * 1024) ;

	BOOL   bRet = FALSE ;
	int    nErr = inflateInit2 (&zs, 47) ;
	if (nErr == Z_OK)
	{
		zs.next_in = (BYTE*)const_cast<void*>(pInDate) ;
		zs.avail_in = (UINT)nSize ;

		for (;;)
		{
			zs.avail_out = (UINT)temp_buf.size() ;
			zs.next_out = &temp_buf[0] ;

			nErr = inflate (&zs, Z_NO_FLUSH) ;

			size_t   nWrite = zs.total_out - raw_data.size() ;
			if (nWrite)
			{
				raw_data.append ((char*)&temp_buf[0], nWrite) ;
			}

			if (nErr == Z_STREAM_END)
			{
				bRet = TRUE ;
				break;
			}
			else if (nErr == Z_OK) // continue
			{
			}
			else
			{
				break;
			}
		}
		inflateEnd (&zs) ;
	}
	assert(bRet) ;
	return bRet ;
}

void CCryptAesWrapper::Base64Encode(const char *in, bool bHexStr, std::string & strResult)
{
	if (bHexStr)
	{
		std::string strDecode("");
		DecodeHexString(in, strDecode);
		CryptoPP::StringSource sEncode(strDecode, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(strResult), false));
	}
	else
	{
		std::string strInput(in);
		CryptoPP::StringSource sEncode(strInput, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(strResult), false));
	}
}

void CCryptAesWrapper::Base64Encode(const std::string & strSrc, bool bHexStr, bool bInsertLineBreaks, std::string & strResult)
{
	if (bHexStr)
	{
		std::string strBin("");
		DecodeHexStrToBinBuf(strSrc, strBin);

		//默认每行72个字符，默认在行尾部插入换行符0X0A,
		Base64Encoder encoder(NULL, bInsertLineBreaks);
		encoder.Put((byte*)strBin.data(), strBin.size());
		encoder.MessageEnd();

		word64 avail = encoder.MaxRetrievable();
		if(avail)
		{
			strResult.resize(avail);
			encoder.Get((byte*)strResult.data(), strResult.size());
		}
	}
	else
	{
		//默认每行72个字符，默认在行尾部插入换行符0X0A,
		Base64Encoder encoder(NULL, bInsertLineBreaks);
		encoder.Put((byte*)strSrc.data(), strSrc.size());
		encoder.MessageEnd();

		word64 avail = encoder.MaxRetrievable();
		if(avail)
		{
			strResult.resize(avail);
			encoder.Get((byte*)strResult.data(), strResult.size());
		}
	}
}

void CCryptAesWrapper::Base64Encode(const BYTE *pBuf, int iElementNum, bool bHexStr, bool bInsertLineBreaks, std::string & strResult)
{
	if (bHexStr)
	{
		std::string strBin("");
		DecodeHexStrToBinBuf(pBuf, iElementNum, strBin);

		//默认每行72个字符，默认在行尾部插入换行符0X0A,
		Base64Encoder encoder(NULL, bInsertLineBreaks);
		encoder.Put((byte*)strBin.data(), strBin.size());
		encoder.MessageEnd();

		word64 avail = encoder.MaxRetrievable();
		if(avail)
		{
			strResult.resize(avail);
			encoder.Get((byte*)strResult.data(), strResult.size());
		}
	}
	else
	{
		//默认每行72个字符，默认在行尾部插入换行符0X0A,
		Base64Encoder encoder(NULL, bInsertLineBreaks);
		encoder.Put((byte*)pBuf, iElementNum);
		encoder.MessageEnd();

		word64 avail = encoder.MaxRetrievable();
		if(avail)
		{
			strResult.resize(avail);
			encoder.Get((byte*)strResult.data(), strResult.size());
		}
	}
}
void CCryptAesWrapper::Base64Decode(const char *in,  std::string & strResult)
{
	std::string strInput(in);
	CryptoPP::StringSource sDecode(strInput, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(strResult)));
}

void CCryptAesWrapper::Base64Decode(const std::string & strSrc,  std::string & strResult)
{
	Base64Decoder decoder;
	decoder.Put((byte*)strSrc.data(), strSrc.size());
	decoder.MessageEnd();

	word64 avail = decoder.MaxRetrievable();
	if(avail)
	{
		strResult.resize(avail);
		decoder.Get((byte*)strResult.data(), strResult.size());
	}
}

bool CCryptAesWrapper::Base64DecodeBufToBuf(const BYTE *in,  size_t iBufBytesLen, CByteBuf * pBytebuf)
{
	bool bOk = false;
	Base64Decoder decoder;
	decoder.Put((byte*)in, iBufBytesLen);
	decoder.MessageEnd();

	word64 avail = decoder.MaxRetrievable();
	if(avail)
	{
		pBytebuf->Resize(avail);
		decoder.Get(pBytebuf->GetBufPtr(), pBytebuf->Size());
		bOk = true;
	}

	return bOk;
}
void CCryptAesWrapper::DecodeHexString(const char *in, std::string & strDecoded)
{
	std::string strEncoded(in);
	HexDecoder decoder;
	decoder.Put( (byte*)strEncoded.data(), strEncoded.size() );
	decoder.MessageEnd();

	word64 size = decoder.MaxRetrievable();
	if(size && size <= SIZE_MAX)
	{
		strDecoded.resize(size);		
		decoder.Get((byte*)strDecoded.data(), strDecoded.size());
	}
}

void CCryptAesWrapper::DecodeHexStrToBinBuf(const std::string & strHexSrc, std::string & strBinDst)
{
	HexDecoder decoder;
	decoder.Put( (byte*)strHexSrc.data(), strHexSrc.size() );
	decoder.MessageEnd();

	word64 size = decoder.MaxRetrievable();
	if(size && size <= SIZE_MAX)
	{
		strBinDst.resize(size);		
		decoder.Get((byte*)strBinDst.data(), strBinDst.size());
	}
}

void CCryptAesWrapper::DecodeHexStrToBinBuf(const BYTE* pHexBuf, int iElmentNum, std::string & strBinDst)
{
	HexDecoder decoder;
	decoder.Put( (byte*)pHexBuf, iElmentNum );
	decoder.MessageEnd();

	word64 size = decoder.MaxRetrievable();
	if(size && size <= SIZE_MAX)
	{
		strBinDst.resize(size);		
		decoder.Get((byte*)strBinDst.data(), strBinDst.size());
	}
}
void CCryptAesWrapper::EncodeBinBufToHexStr(const std::string & strBinBuf, std::string & strHex)
{
	HexDecoder decoder;
	decoder.Put( (byte*)strBinBuf.data(), strBinBuf.size() );
	decoder.MessageEnd();

	word64 size = decoder.MaxRetrievable();
	if(size && size <= SIZE_MAX)
	{
		strHex.resize(size);		
		decoder.Get((byte*)strHex.data(), strHex.size());
	}
}
void CCryptAesWrapper::EncodeBinBufToHexStr(const BYTE* pBuf, int iElementNum, std::string & strHex)
{
	HexEncoder encoder;
	encoder.Put(pBuf, iElementNum);
	encoder.MessageEnd();

	word64 size = encoder.MaxRetrievable();
	if(size)
	{
		strHex.resize(size);		
		encoder.Get((byte*)strHex.data(), strHex.size());
	}
}
//解压\0结尾的字符串
void CCryptAesWrapper::GunzipString(std::string & strComproessed, std::string & strOut)
{
	CryptoPP::Gunzip unzipper(new StringSink(strComproessed));
	unzipper.Put((byte*) strOut.data(), strOut.size());
	unzipper.MessageEnd();
}

//解压一段buf，buf长度由iBufBytesLen指定
bool CCryptAesWrapper::GunzipBuf(const BYTE* pBuf, int iBufBytesLen, std::string & strOut)
{
	bool bOk = false;
	Gunzip unzipper;
	unzipper.Put((byte*)pBuf, iBufBytesLen);
	unzipper.MessageEnd();

	word64 avail = unzipper.MaxRetrievable();
	if(avail)
	{
		strOut.resize(avail);
		unzipper.Get((byte*)&strOut[0], strOut.size());
		bOk = true;
	}

	return bOk;
}
bool CCryptAesWrapper::GunzipBufToBuf(const BYTE* pBuf, size_t iBufBytesLen, CByteBuf * pBytebuf)
{
	bool bOk = false;
	Gunzip unzipper;
	unzipper.Put((byte*)pBuf, iBufBytesLen);
	unzipper.MessageEnd();

	word64 avail = unzipper.MaxRetrievable();
	if(avail)
	{
		pBytebuf->Resize(avail);
		unzipper.Get(pBytebuf->GetBufPtr(), pBytebuf->Size());
		bOk = true;
	}
	return bOk;
}
//int _tmain(int argc, _TCHAR* argv[])  
//{  
//	string plainText = "This Program shows how to use ECB, CBC, CBC_CTS, CFB, OFB and CTR mode of AES in Crypto++.";  
//	string aesKey = "0123456789ABCDEF0123456789ABCDEF";//256bits, also can be 128 bits or 192bits  
//	string aesIV = "ABCDEF0123456789";//128 bits  
//	string ECB_EncryptedText,ECB_DecryptedText,  
//		CBC_EncryptedText,CBC_DecryptedText,  
//		CBC_CTS_EncryptedText,CBC_CTS_DecryptedText,  
//		CFB_EncryptedText,CFB_DecryptedText,  
//		OFB_EncryptedText,OFB_DecryptedText,  
//		CTR_EncryptedText,CTR_DecryptedText;  
//
//	//ECB  
//	ECB_EncryptedText = ECB_AESEncryptStr(aesKey, plainText.c_str());//ECB加密  
//	ECB_DecryptedText = ECB_AESDecryptStr(aesKey,ECB_EncryptedText.c_str());//ECB解密  
//
//	//CBC  
//	CBC_EncryptedText = CBC_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CBC加密  
//	CBC_DecryptedText = CBC_AESDecryptStr(aesKey, aesIV, CBC_EncryptedText.c_str());//CBC解密  
//
//	//CBC_CTS  
//	CBC_CTS_EncryptedText = CBC_CTS_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CBC_CTS加密  
//	CBC_CTS_DecryptedText = CBC_CTS_AESDecryptStr(aesKey, aesIV, CBC_CTS_EncryptedText.c_str());//CBC_CTS解密  
//
//	//CFB  
//	CFB_EncryptedText = CFB_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CFB加密  
//	CFB_DecryptedText = CFB_AESDecryptStr(aesKey, aesIV, CFB_EncryptedText.c_str());//CFB解密  
//
//	//OFB  
//	OFB_EncryptedText = OFB_AESEncryptStr(aesKey, aesIV, plainText.c_str());//OFB加密  
//	OFB_DecryptedText = OFB_AESDecryptStr(aesKey, aesIV, OFB_EncryptedText.c_str());//OFB解密  
//
//	//CTR  
//	CTR_EncryptedText = CTR_AESEncryptStr(aesKey, aesIV, plainText.c_str());//CTR加密  
//	CTR_DecryptedText = CTR_AESDecryptStr(aesKey, aesIV, CTR_EncryptedText.c_str());//CTR解密  
//
//
//	cout << "Crypto++ AES-256 加密测试"<< endl;  
//	cout << "分别使用ECB，CBC, CBC_CTR，CFB，OFB和CTR模式"<< endl;  
//	cout << "加密用密钥:" << aesKey << endl;  
//	cout << "密钥长度:" << AES::MAX_KEYLENGTH*8 <<"bits" << endl;  
//	cout << "IV:" << aesIV << endl;  
//	cout << endl;  
//
//	cout << "ECB测试"<< endl;  
//	cout << "原文：" << plainText << endl;  
//	cout << "密文：" << ECB_EncryptedText << endl;  
//	cout << "恢复明文：" << ECB_DecryptedText << endl << endl;  
//
//	cout << "CBC测试"<< endl;  
//	cout << "原文：" << plainText << endl;  
//	cout << "密文：" << CBC_EncryptedText << endl;  
//	cout << "恢复明文：" << CBC_DecryptedText << endl << endl;  
//
//	cout << "CBC_CTS测试"<< endl;  
//	cout << "原文：" << plainText << endl;  
//	cout << "密文：" << CBC_CTS_EncryptedText << endl;  
//	cout << "恢复明文：" << CBC_CTS_DecryptedText << endl << endl;  
//
//	cout << "CFB测试"<< endl;  
//	cout << "原文：" << plainText << endl;  
//	cout << "密文：" << CFB_EncryptedText << endl;  
//	cout << "恢复明文：" << CFB_DecryptedText << endl << endl;  
//
//	cout << "OFB测试"<< endl;  
//	cout << "原文：" << plainText << endl;  
//	cout << "密文：" << OFB_EncryptedText << endl;  
//	cout << "恢复明文：" << OFB_DecryptedText << endl << endl;  
//
//	cout << "CTR测试"<< endl;  
//	cout << "原文：" << plainText << endl;  
//	cout << "密文：" << CTR_EncryptedText << endl;  
//	cout << "恢复明文：" << CTR_DecryptedText << endl << endl;  
//
//
//	getchar();  
//	return 0;  
//}  