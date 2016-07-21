
#include "stdafx.h"
#include "CeairMobileE.h"

#include "CeairMobileEConst.h"
#include "common/WinHttpClient.h"

#include "DataProcess.h"
#include "strconv.h"

#include "dll.h"
#include "CCryptAesWrapper.h"

#include "CalKey.h"
#include "GrapCeFlights.h"

USING_NAMESPACE(CryptoPP)
USING_NAMESPACE(std)

std::string CCeairMobileE::m_strSessionId="";
BYTE CCeairMobileE::m_u8EncryptSeverKey[CEAIR_ME_SEVER_KEY_LEN];
BOOL CCeairMobileE::m_bOutLog = FALSE;

CCeairMobileE::CCeairMobileE(void)
{

}

CCeairMobileE::~CCeairMobileE(void)
{

}

void CCeairMobileE::__Init()
{
	SecureZeroMemory(m_u8EncryptSeverKey, sizeof(m_u8EncryptSeverKey));
	//m_strSessionId
}

BOOL CCeairMobileE::GetServerKey()
{
	//////////////////////////////////////////////////////////////
	BOOL bOk = FALSE;

	//base 64 ±‡¬ÎΩ‚¬Î≤‚ ‘¥˙¬Î
	//BYTE u8Tmp[] = 
	//{
	//	0X82, 0XB7, 0XE7, 0XD0, 0X1D, 0X47, 0X6A, 0X47, 0X0C, 0X1A, 0XAB, 0XF2, 0X2C, 0X91, 0X04, 0X0C,
	//	0X51, 0XC0, 0X6B, 0X8C, 0
	//};
	//std::string strEn("");
	//std::string strDe("");
	//CCryptAesWrapper::Base64Encode((char*)u8Tmp, false, strEn);
	//CCryptAesWrapper::Base64Decode(strEn.c_str(), strDe);
	//end base 64 ±‡¬ÎΩ‚¬Î≤‚ ‘¥˙¬Î

	//CryptoPP::Base64Decoder base64De(new CryptoPP::StringSink(encoded));    
	//int iLen = encoded.length();
	//base64De.Put((byte *)encoded.c_str(), iLen);    
	//base64De.MessageEnd(); 
	
	//test
	//__DecrptServerKeyWithAES(NULL, 0);
	//unsigned char enCryptMsg[CEAIR_ME_SEVER_KEY_LEN*2+1] = {0};
	//unsigned char u8Content3[] = 
	//{
	//	0X7F, 0X34, 0X9D, 0X18, 0X5C, 0X56, 0XBD, 0X07, 0X87, 0X12, 0X3E, 0X90, 0X12, 0X3B, 0X52, 0XBA,
	//	0XB2, 0X41, 0X93, 0X2C, 0X77, 0X90, 0X9E, 0X95, 0X5B, 0X56, 0X9B, 0X09, 0XFC, 0X71, 0XAD, 0XE3,
	//	0XCD, 0X5D, 0X92, 0XE2, 0X49, 0XB2, 0X83, 0XBC, 0XE4, 0XA6, 0X20, 0XE5, 0XC4, 0X68, 0XC7, 0X10,
	//	0XD1, 0XD6, 0XEF, 0XE3, 0X2D, 0XD0, 0X29, 0XB7, 0XBF, 0XF9, 0X0D, 0XF1, 0X05, 0XF2, 0X2A, 0X85,
	//	0X23, 0XE0, 0XE9, 0X1A, 0X86, 0X9E, 0XE6, 0X51, 0X2D, 0XEB, 0X4E, 0X1F, 0X98, 0X41, 0XC6, 0X32,
	//	0X35, 0X5D, 0XEB, 0X9E, 0XA0, 0XAB, 0XDF, 0X18, 0XF8, 0X75, 0X6D, 0XE5, 0X39, 0X6A, 0XF2, 0X5E,
	//	0XD7, 0XED, 0X49, 0X74, 0X1D, 0XCD, 0X40, 0X5B, 0X37, 0X0F, 0X52, 0X95, 0XF9, 0X28, 0XEC, 0XFB
	//};
	//CCalKey::HexByteToTwoChar(enCryptMsg, CEAIR_ME_SEVER_KEY_LEN*2+1, (unsigned char*)u8Content3, CEAIR_ME_SEVER_KEY_LEN);
	//std::string strDecryptKeyData((char*)enCryptMsg);
	//CCalKey::CalClientKeyAndServerKey(strDecryptKeyData);

	//ok test
	//TRACE(_T("\r\nRNS_ key:"));
	//for (int i = 0; i < _countof(RNS_); i++)
	//{
	//	TRACE("%02X", RNS_[i]);
	//}
	//TRACE(_T("\r\nRNC_ key:"));
	//for (int i = 0; i < _countof(RNC_); i++)
	//{
	//	TRACE("%02X", RNC_[i]);
	//}
	//TRACE(_T("\r\nMasterConst key:"));
	//for (int i = 0; i < _countof(MasterConst); i++)
	//{
	//	TRACE("%02X", MasterConst[i]);
	//}

	//unsigned char enCryptMsg[CEAIR_ME_SEVER_KEY_LEN*2+1] = {0};
	//unsigned char u8Content3[] = 
	//{
	//	//0X1C, 0X46, 0X30, 0X98, 0X75, 0X8F, 0X65, 0X68, 0X99, 0XB9, 0XE4, 0X27, 0X5C, 0XE7, 0XDC, 0XA8, 
	//	//0X81, 0XE9, 0X49, 0XD7, 0XFE, 0X8C, 0X83, 0X12, 0X61, 0X5B, 0X2F, 0X66, 0X0B, 0X94, 0XDF, 0X99, 
	//	//0X40, 0XC2, 0X43, 0X00, 0X31, 0XB1, 0X98, 0X21, 0XCD, 0X98, 0XF3, 0X3A, 0X90, 0X0E, 0X2A, 0XC1, 
	//	//0XAB, 0X36, 0X3A, 0X9A, 0XF4, 0X9C, 0XF7, 0X4E, 0XE2, 0XA7, 0X16, 0X95, 0X62, 0X1D, 0XF1, 0X56, 
	//	//0XEA, 0X43, 0X66, 0X06, 0X11, 0X1F, 0X7B, 0XC1, 0X90, 0XD5, 0X40, 0XEC, 0XC9, 0X73, 0X0B, 0XA9, 
	//	//0XA4, 0X73, 0XD4, 0XC8, 0X19, 0X91, 0XEF, 0X2F, 0X6E, 0X1B, 0XFF, 0X85, 0X34, 0X2C, 0XB2, 0XB2, 
	//	//0X47, 0XF2, 0X39, 0X51, 0XB6, 0XA3, 0XCA, 0XA1, 0X0A, 0X2E, 0X06, 0X14, 0XDA, 0X94, 0X4A, 0XA8

	//		0X7F, 0X34, 0X9D, 0X18, 0X5C, 0X56, 0XBD, 0X07, 0X87, 0X12, 0X3E, 0X90, 0X12, 0X3B, 0X52, 0XBA,
	//		0XB2, 0X41, 0X93, 0X2C, 0X77, 0X90, 0X9E, 0X95, 0X5B, 0X56, 0X9B, 0X09, 0XFC, 0X71, 0XAD, 0XE3,
	//		0XCD, 0X5D, 0X92, 0XE2, 0X49, 0XB2, 0X83, 0XBC, 0XE4, 0XA6, 0X20, 0XE5, 0XC4, 0X68, 0XC7, 0X10,
	//		0XD1, 0XD6, 0XEF, 0XE3, 0X2D, 0XD0, 0X29, 0XB7, 0XBF, 0XF9, 0X0D, 0XF1, 0X05, 0XF2, 0X2A, 0X85,
	//		0X23, 0XE0, 0XE9, 0X1A, 0X86, 0X9E, 0XE6, 0X51, 0X2D, 0XEB, 0X4E, 0X1F, 0X98, 0X41, 0XC6, 0X32,
	//		0X35, 0X5D, 0XEB, 0X9E, 0XA0, 0XAB, 0XDF, 0X18, 0XF8, 0X75, 0X6D, 0XE5, 0X39, 0X6A, 0XF2, 0X5E,
	//		0XD7, 0XED, 0X49, 0X74, 0X1D, 0XCD, 0X40, 0X5B, 0X37, 0X0F, 0X52, 0X95, 0XF9, 0X28, 0XEC, 0XFB
	//};
	//unsigned char u8Content3[] =
	//{
	//	0X00, 0XEB, 0X73, 0XA9, 0X78, 0XAE, 0XEB, 0xD0, 0X80, 0X76, 0xEA, 0X43, 0X7B, 0X97, 0XD9, 0X05, 
	//	0XF5, 0XE0, 0X86, 0X9C, 0X58, 0X5B, 0XCD, 0xF0, 0X85, 0X0F, 0x13, 0X1A, 0XEE, 0X0B, 0X2D, 0X03, 
	//	0X76, 0X30, 0XA1, 0XB5, 0X93, 0X03, 0X19, 0x17, 0XF6, 0X4B, 0xED, 0X36, 0XB5, 0X09, 0X09, 0X73, 
	//	0XC0, 0X3A, 0XC9, 0XC3, 0X6C, 0X22, 0XFE, 0x1C, 0X02, 0XBB, 0x9B, 0XBF, 0X0A, 0XA6, 0X24, 0X42, 
	//	0X71, 0X44, 0X9C, 0XFD, 0XD7, 0X5B, 0XBD, 0xFD, 0X0A, 0X1F, 0x7F, 0X4F, 0XC1, 0X15, 0XED, 0X3A, 
	//	0XC5, 0X3A, 0XE1, 0X37, 0X74, 0X78, 0XE3, 0x4C, 0XED, 0X67, 0x8D, 0X6F, 0X1C, 0X97, 0X9F, 0XA3, 
	//	0X95, 0XE1, 0X93, 0XDB, 0X81, 0X81, 0X54, 0x9B, 0X64, 0X3B, 0xC8, 0X65, 0X33, 0XF3, 0X1D, 0XA1
	//};

	//std::string strEncryptServerKey("");
	//CCryptAesWrapper::EncodeBinBufToHexStr(u8Content3, sizeof(u8Content3), strEncryptServerKey);
	//CCalKey::printStdString("strEncryptServerKey", strEncryptServerKey, TRUE);	
	//std::string strTestKey((char*)AES_Key);
	//std::string strTestIv((char*)AES_IV);
	//std::string strAesDecryptServerKeyData("");
	//CCryptAesWrapper::CBC_AESDecryptStr2(strTestKey, strTestIv, strEncryptServerKey, strAesDecryptServerKeyData);//CCryptAesWrapper::CBC_AESDecryptStr(strTestKey, strTestIv, const_cast<char*>(strEncryptServerKey.c_str()));
	//CCalKey::printStdString("strAesDecryptServerKeyData", strAesDecryptServerKeyData, TRUE);	

	//CCalKey::printByteArray("AES decrypt serverKeyData", (BYTE*)strAesDecryptServerKeyData.c_str(), strAesDecryptServerKeyData.length());
	//CCalKey::CalClientKeyAndServerKey(strAesDecryptServerKeyData);
	//CGrapCeFlight::InitAesKeys(CCalKey::m_u8ClientKey, CCalKey::m_u8ClientKey+AES_KEY_BYTE_LEN, CCalKey::m_u8ClientKey+AES_KEY_BYTE_LEN+AES_IV_BYTE_LEN
	//	, CCalKey::m_u8ServerKey, CCalKey::m_u8ServerKey+AES_KEY_BYTE_LEN);

	//std::string strDcode("SHA");
	//std::string strAcode("PEK");
	//std::string strFlightDate("20141228");
	//std::list<SCeairFlightInfo*> flightList;
	//flightList.clear();
	//CGrapCeFlight::GrapFlight(strDcode, strAcode, strFlightDate, flightList);
	//end test

	//TRACE(_T("\r\nBlock size     : %d"),  AES::BLOCKSIZE );
	//TRACE(_T("\r\nMin key length : %d"),  AES::MIN_KEYLENGTH);
	//TRACE(_T("\r\nMax key length : %d"), AES::MAX_KEYLENGTH);

	__Init();
	wstring httpResponseContent(L"");
	CStringA straPostData = "AQAAACoBAAAVAB5pyssDZla5rRAdgE2X9yISdSWJVLe9B0yvDnG5AAAEAAcABgAJAAAAgHAb07eoNK9sxEKBnV9VESxw7umY1ZFINfFypgzt5VJS638gPmN3YU84B0ndvg3iETH8iRJA1pVUkHfTX69E+BaP82idm2wZdsGky/FHB13fjDPjs83BozY2IdSw7sgGvScD+P+2sUZXVT4CM2RzYF7x+ADg7gxEmHDYNKmWILozBwAAAAEACgAAAAzyTq3LXb9JzbAMEJI=";
	CString strUrl = _T("http://mobile.ceair.com/user/handshake?bankUserCode=&tmsUserCode=&ota_version=AD-UMP-3.0.0-080901&clientinfo=android-17-P188F07-3.0.0-JOP40D&is_first=1&imei=W0xXVlxaXV5TXVVSV01T&passportId=0000000000&account=&pwd=&pwdautologin=&logintype=&deviceModel=ZTE+V967S&is_install_samsung_wallet=false&channelType=RYT&hasOrNotBroken=1&telecomOperator=CMCC&networkType=wifi&resolution=540*960&app=ceair&o=i");
	WinHttpClient httpClient(strUrl.GetBuffer(0));
	httpClient.SetTimeouts(0, 25000U, 25000U, 40000U);
	//CDataProcess::GetInstance()->ChangeProxy(httpClient);

	std::string strResp;
	wstring headers = L"Host: mobile.ceair.com";
	headers += L"\r\nAccept: text/vnd.wap.wml";
	headers += L"\r\nUser-Agent: LightPole/3.0.0/android1.5";
	headers += L"\r\nPragma: no-cache";
	headers += L"\r\nConnection: Keep-Alive";
	headers += L"\r\nProxy-Connection: Keep-Alive";
	headers += L"\r\nContent-Type: application/x-www-form-urlencoded";
	headers += L"\r\nAccept-Encoding: gzip";
	headers += L"\r\nContent-Length:";

	wchar_t szSize[50] = L"";
	swprintf_s(szSize, L"%d", straPostData.GetLength());
	headers += szSize;

	httpClient.SetAdditionalDataToSend((BYTE *)straPostData.GetBuffer(0), straPostData.GetLength());
	httpClient.SetAdditionalRequestHeaders(headers);
	httpClient.SendHttpRequest(L"POST");
	wstring wstrStatus = httpClient.GetResponseStatusCode();
	if (0 != wstrStatus.compare(L"200"))
	{
		CString str;
		str.Format(_T("-----error code=%s\n"), httpClient.GetResponseStatusCode().c_str());
		OutputDebugString(str);
		bOk = FALSE;
	}
	else
		bOk = TRUE;

	if (bOk)
	{
		CByteBuf unzipBuf;
		wstring httpResponseHeader = httpClient.GetResponseHeader();
		//get _session_id
		__GetSessionId(m_strSessionId, httpResponseHeader);
		CGrapCeFlight::SetSessionId(m_strSessionId);
		const BYTE* pResponse = httpClient.GetRawResponseContent();
		if (pResponse[0] == 0x1f && pResponse[1] == 0x8b)
		{
			//gzipΩ‚—π
			strconv_t strConv;

			int iRespLen = httpClient.GetRawResponseContentLength();
			CCryptAesWrapper::GunzipBufToBuf(pResponse, iRespLen, &unzipBuf);
			size_t uUnzipLen = unzipBuf.Size();

			SCeairMERecvRawHeader recvHeader;
			memcpy_s(&recvHeader, sizeof(recvHeader), unzipBuf.GetBufPtr(), sizeof(recvHeader));
			CCalKey::printByteArray("recv serverKey", recvHeader.u8Type3Content, CEAIR_ME_SEVER_KEY_LEN);
			__PrintEncryptServerkey(&recvHeader);

			std::string strEncryptServerKey("");
			CCryptAesWrapper::EncodeBinBufToHexStr(recvHeader.u8Type3Content, sizeof(recvHeader.u8Type3Content), strEncryptServerKey);
			CCalKey::printStdString("strEncryptServerKey", strEncryptServerKey, TRUE);	

			std::string strKey((char*)AES_Key);
			std::string strIv((char*)AES_IV);
			std::string strDecryptServerKeyData("");
			CCryptAesWrapper::CBC_AESDecryptStr2(strKey, strIv, strEncryptServerKey, strDecryptServerKeyData);
			CCalKey::printStdString("strDecryptServerKeyData", strDecryptServerKeyData, TRUE);
			CCalKey::CalClientKeyAndServerKey(strDecryptServerKeyData, m_bOutLog);

			CGrapCeFlight::SetOutlogFlag(m_bOutLog);
			CGrapCeFlight::InitAesKeys(CCalKey::m_u8ClientKey, CCalKey::m_u8ClientKey+AES_KEY_BYTE_LEN, CCalKey::m_u8ClientKey+AES_KEY_BYTE_LEN+AES_IV_BYTE_LEN
				, CCalKey::m_u8ServerKey, CCalKey::m_u8ServerKey+AES_KEY_BYTE_LEN);

			bOk = TRUE;

			//std::string strDcode("PEK");
			//std::string strAcode("HFE");
			//std::string strFlightDate("20150130");
			//std::list<SCeairFlightInfo*> flightList;
			//flightList.clear();
			//BOOL bGet = CGrapCeFlight::GrapFlight(strDcode, strAcode, strFlightDate, flightList);
		}
		else
		{
			httpResponseContent = httpClient.GetResponseContent();
			strResp = CDataProcess::Unicode2Ansi(httpResponseContent.c_str());
		}
	}

	return bOk;
}

 void CCeairMobileE::__GetSessionId(std::string & str, const std::wstring & httpResponseHeader)
 {
	 //HTTP/1.1 200 OK
	 //Date: Wed, 31 Dec 2014 08:05:45 GMT
	 //Content-Length: 3797
	 //Content-Type: application/octet-stream
	 //Content-Encoding: gzip
	 //Server: Yaws/1.88 Yet Another Web Server
	 //Set-Cookie: _session_id=182ea20e998c324e2862cbf0886a6aee; path=/

	 
	 CString strHeader(httpResponseHeader.c_str());
	 CString strKey = _T("_session_id=");
	 int iSessionIdPos = strHeader.Find(strKey);
	 int iEndPos = -1;
	 CString strSession("");
	 if (-1 != iSessionIdPos)
	 {
		 iEndPos = strHeader.Find(';', iSessionIdPos);
		 if (-1 != iEndPos)
		 {
			 int iStartPos = iSessionIdPos + strKey.GetLength();
			 strSession = strHeader.Mid(iStartPos, iEndPos-iStartPos);
			 std::wstring wstrSession(strSession.GetBuffer(0));
			 str = CDataProcess::Unicode2Ansi(wstrSession.c_str());
		 }
	 }

 }

 void CCeairMobileE::__PrintEncryptServerkey(const SCeairMERecvRawHeader *pRecvHeader)
 {
	 TRACE(_T("\r\ntype1 id=0X%X,len=%02X %02X %02X %02X"), pRecvHeader->u8Type1
		 , pRecvHeader->uType1ContentBytes[0], pRecvHeader->uType1ContentBytes[1], pRecvHeader->uType1ContentBytes[2], pRecvHeader->uType1ContentBytes[3]);
	 TRACE(_T("\r\ntype2 id=0X%X,len=%02X %02X %02X %02X"), pRecvHeader->u8Type2
		 , pRecvHeader->uType2ContentBytes[0], pRecvHeader->uType2ContentBytes[1], pRecvHeader->uType2ContentBytes[2], pRecvHeader->uType2ContentBytes[3]);
	 TRACE(_T("\r\ntype2 id=0X%X,len=%02X %02X %02X %02X"), pRecvHeader->u8Type3
		 , pRecvHeader->uType3ContentBytes[0], pRecvHeader->uType3ContentBytes[1], pRecvHeader->uType3ContentBytes[2], pRecvHeader->uType3ContentBytes[3]);

	 TRACE(_T("\r\nserverkey data:\r\n"));
	 for (int i = 0; i < CEAIR_ME_SEVER_KEY_LEN; i++)
	 {
		 if (0 != i && 0 == (i %16))
		 {
			 TRACE(_T("\r\n"));
		 }
		 TRACE(_T("%02X "), pRecvHeader->u8Type3Content[i]);
	 }
	 TRACE(_T("\r\n"));
 }

 void CCeairMobileE::__DecrptServerKeyWithAES(BYTE * pu8ServerKey, int nServerKeyBytes)
 {
	 TRACE(_T("Block size     : %d"),  AES::BLOCKSIZE );
	 TRACE(_T("Min key length : %d"),  AES::MIN_KEYLENGTH);
	 TRACE(_T("Max key length : %d"), AES::MAX_KEYLENGTH);
	 //CBC_Mode<AES>::Decryption modeCbc(pu8ServerKey, 16, pu8ServerKey);

	 const BYTE plain[] = {	// "Now is the time for all " without tailing 0
		 0x4e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
		 0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
		 0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20};
		 unsigned char en[] =
		 {
			 0X1C, 0X46, 0X30, 0X98, 0X75, 0X8F, 0X65, 0X68, 0X99, 0XB9, 0XE4, 0X27, 0X5C, 0XE7, 0XDC, 0XA8, 
			 0X81, 0XE9, 0X49, 0XD7, 0XFE, 0X8C, 0X83, 0X12, 0X61, 0X5B, 0X2F, 0X66, 0X0B, 0X94, 0XDF, 0X99, 
			 0X40, 0XC2, 0X43, 0X00, 0X31, 0XB1, 0X98, 0X21, 0XCD, 0X98, 0XF3, 0X3A, 0X90, 0X0E, 0X2A, 0XC1, 
			 0XAB, 0X36, 0X3A, 0X9A, 0XF4, 0X9C, 0XF7, 0X4E, 0XE2, 0XA7, 0X16, 0X95, 0X62, 0X1D, 0XF1, 0X56, 
			 0XEA, 0X43, 0X66, 0X06, 0X11, 0X1F, 0X7B, 0XC1, 0X90, 0XD5, 0X40, 0XEC, 0XC9, 0X73, 0X0B, 0XA9, 
			 0XA4, 0X73, 0XD4, 0XC8, 0X19, 0X91, 0XEF, 0X2F, 0X6E, 0X1B, 0XFF, 0X85, 0X34, 0X2C, 0XB2, 0XB2, 
			 0X47, 0XF2, 0X39, 0X51, 0XB6, 0XA3, 0XCA, 0XA1, 0X0A, 0X2E, 0X06, 0X14, 0XDA, 0X94, 0X4A, 0XA8, 0
		 };
		 const unsigned char key[] = 
		 {
			 0X76, 0X5D, 0XD5, 0XC3, 0XD9, 0XDF, 0X44, 0X21, 0XAE, 0XD1, 0XFE, 0XAA, 0XDA, 0XBC, 0X69, 0X12, 0XF0, 0X6B, 0X96, 0XE1, 0X37, 0XD2, 0XDD, 0X2C, 0X0E, 0X7D, 0XE0, 0X92, 0XE6, 0X6A, 0X6C, 0X54, 0
		 };
		 const unsigned char iv[] = {0X5B, 0XCA, 0XB3, 0XC4, 0X9A, 0X1D, 0X1B, 0X01, 0X5E, 0XF7, 0X48, 0X71, 0XA1, 0X2C, 0XCF, 0X24, 0};

	 BYTE de[0X70] = {0};
	 std::string strKey((char*)key);
	 std::string strIv((char*)iv);
	 //std::string strEn(en);

	 std::string msg = "1C463098758F656899B9E4275CE7DCA881E949D7FE8C8312615B2F660B94DF9940C2430031B19821CD98F33A900E2AC1AB363A9AF49CF74EE2A71695621DF156EA436606111F7BC190D540ECC9730BA9A473D4C81991EF2F6E1BFF85342CB2B247F23951B6A3CAA10A2E0614DA944AA8";
	int iLen = msg.length();

	unsigned char enCryptMsg[CEAIR_ME_SEVER_KEY_LEN*2+1] = {0};
	unsigned char content3[] = 
	{
		0X1C, 0X46, 0X30, 0X98, 0X75, 0X8F, 0X65, 0X68, 0X99, 0XB9, 0XE4, 0X27, 0X5C, 0XE7, 0XDC, 0XA8, 
		0X81, 0XE9, 0X49, 0XD7, 0XFE, 0X8C, 0X83, 0X12, 0X61, 0X5B, 0X2F, 0X66, 0X0B, 0X94, 0XDF, 0X99, 
		0X40, 0XC2, 0X43, 0X00, 0X31, 0XB1, 0X98, 0X21, 0XCD, 0X98, 0XF3, 0X3A, 0X90, 0X0E, 0X2A, 0XC1, 
		0XAB, 0X36, 0X3A, 0X9A, 0XF4, 0X9C, 0XF7, 0X4E, 0XE2, 0XA7, 0X16, 0X95, 0X62, 0X1D, 0XF1, 0X56, 
		0XEA, 0X43, 0X66, 0X06, 0X11, 0X1F, 0X7B, 0XC1, 0X90, 0XD5, 0X40, 0XEC, 0XC9, 0X73, 0X0B, 0XA9, 
		0XA4, 0X73, 0XD4, 0XC8, 0X19, 0X91, 0XEF, 0X2F, 0X6E, 0X1B, 0XFF, 0X85, 0X34, 0X2C, 0XB2, 0XB2, 
		0X47, 0XF2, 0X39, 0X51, 0XB6, 0XA3, 0XCA, 0XA1, 0X0A, 0X2E, 0X06, 0X14, 0XDA, 0X94, 0X4A, 0XA8
	};
	CCalKey::HexByteToTwoChar(enCryptMsg, CEAIR_ME_SEVER_KEY_LEN*2+1, (unsigned char*)content3, CEAIR_ME_SEVER_KEY_LEN);
	char* pArray = (char *)enCryptMsg;
	TRACE("cryptMsg:%s", pArray);

	//std::string strEncprtMsg("");
	//CBC_AESEncryptStr(strKey, strIv, msg, strEncprtMsg);
	const char* pStr = msg.c_str();
	int iLength = strlen(pStr);
	std::string strMsg = CCryptAesWrapper::CBC_AESDecryptStr(strKey, strIv, msg.c_str());
	 CBC_Mode<AES>::Decryption modeD(en, 16, de);
	 //CBC_Mode<AES>::Encryption modeE(plain, 16, plain);
	 
 }

 BOOL CCeairMobileE::GetCeairMobileEFlight(BOOL bChangeProxyIp, const CStringA & strDCode, const CStringA & strACode, const CStringA & strFlightStratDate, std::list<SCeairFlightInfo*> & flightList)
 {
	 BOOL bGet = CGrapCeFlight::GrapFlight(bChangeProxyIp, strDCode, strACode, strFlightStratDate, flightList);
	 return bGet;
 }