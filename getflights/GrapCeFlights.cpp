
#include "stdafx.h"
#include "GrapCeFlights.h"
#include "strconv.h"
#include "util.h"

#include "dll.h"
#include "CCryptAesWrapper.h"
#include "CalKey.h"
#include "common/WinHttpClient.h"
#include "./tinyxml/tinyxml.h"
#include "./tinyxml/tinystr.h"
#include "DataProcess.h"


BYTE CGrapCeFlight::m_u8AesEncryptKey[AES_KEY_BYTE_LEN+1] = {0};
BYTE CGrapCeFlight::m_u8AesEncryptIV[AES_IV_BYTE_LEN+1] = {0};
BYTE CGrapCeFlight::m_u8XempEncryptKey[AES_XEMP_KEY_BYTE_LEN+1] = {0};
BYTE CGrapCeFlight::m_u8AesDecryptKey[AES_KEY_BYTE_LEN+1] = {0};
BYTE CGrapCeFlight::m_u8AesDecryptIV[AES_IV_BYTE_LEN+1] = {0};
BYTE CGrapCeFlight::m_u8SessionId[SESSIONID_MAX_CHAR+1] = {0};
BOOL CGrapCeFlight::m_bOutLog = FALSE;

CGrapCeFlight::CGrapCeFlight()
{

}

CGrapCeFlight::~CGrapCeFlight()
{

}

void CGrapCeFlight::SetSessionId(const std::string & strSessionId)
{
	int iCopyCharNum = strSessionId.length();
	ASSERT((iCopyCharNum+1) < SESSIONID_MAX_CHAR);
	memcpy_s(m_u8SessionId, SESSIONID_MAX_CHAR, strSessionId.c_str(), iCopyCharNum);
	m_u8SessionId[iCopyCharNum] = '\0';
}
void CGrapCeFlight::InitAesKeys(BYTE * pu8AesEncryptKey, BYTE * pu8AesEncryptIV, BYTE * pu8XempEncryptKey, BYTE * pu8AesDecryptKey, BYTE * pu8AesDecryptIV)
{
	memcpy_s(m_u8AesEncryptKey, AES_KEY_BYTE_LEN, pu8AesEncryptKey, AES_KEY_BYTE_LEN);
	m_u8AesEncryptKey[AES_KEY_BYTE_LEN] = '\0';
	CCalKey::printByteArray("m_u8AesEncryptKey[]", m_u8AesEncryptKey, AES_KEY_BYTE_LEN);

	memcpy_s(m_u8AesEncryptIV, AES_IV_BYTE_LEN, pu8AesEncryptIV, AES_IV_BYTE_LEN);
	m_u8AesEncryptIV[AES_IV_BYTE_LEN] = '\0';
	CCalKey::printByteArray("m_u8AesEncryptIV[]", m_u8AesEncryptIV, AES_IV_BYTE_LEN);

	memcpy_s(m_u8XempEncryptKey, AES_XEMP_KEY_BYTE_LEN, pu8XempEncryptKey, AES_XEMP_KEY_BYTE_LEN);
	m_u8XempEncryptKey[AES_XEMP_KEY_BYTE_LEN] = '\0';
	CCalKey::printByteArray("m_u8XempEncryptKey[]", m_u8XempEncryptKey, AES_XEMP_KEY_BYTE_LEN);

	memcpy_s(m_u8AesDecryptKey, AES_KEY_BYTE_LEN, pu8AesDecryptKey, AES_KEY_BYTE_LEN);
	m_u8AesDecryptKey[AES_KEY_BYTE_LEN] = '\0';
	CCalKey::printByteArray("m_u8AesDecryptKey[]", m_u8AesDecryptKey, AES_KEY_BYTE_LEN);

	memcpy_s(m_u8AesDecryptIV, AES_IV_BYTE_LEN, pu8AesDecryptIV, AES_IV_BYTE_LEN);
	m_u8AesDecryptIV[AES_IV_BYTE_LEN] = '\0';
	CCalKey::printByteArray("m_u8AesDecryptIV[]", m_u8AesDecryptIV, AES_IV_BYTE_LEN);
}
BOOL CGrapCeFlight::GrapFlight(BOOL bChangeProxyIp, const CStringA & straDCode, const CStringA & straACode, const CStringA & straFlightStratDate, std::list<SCeairFlightInfo*> & flightList)
{
	FILE *pStream = NULL;
	int  numwritten = 0;
	char *pFilePath = "ceairlog.log";
	char szHeadStr[] = "Header:";
	char szPostStr[]="PostStr:";
	char szResponseStr[] = "ResponsStr:";

	BOOL bGet = FALSE;
	CStringA straPostData;
	CStringA straStartDate = straFlightStratDate;
	straStartDate.Remove('-');

	CStringA straDeptCode;
	CStringA straArrCode;
	if (0 == straDCode.CompareNoCase("SHA") || 0 == straDCode.CompareNoCase("PVG") )
		straDeptCode = "SHA1";
	else if (0 == straDCode.CompareNoCase("BJS") || 0 == straDCode.CompareNoCase("PEK") || 0 == straDCode.CompareNoCase("NAY"))
		straDeptCode = "PEK1";
	else
		straDeptCode = straDCode;

	if (0 == straACode.CompareNoCase("SHA") || 0 == straACode.CompareNoCase("PVG") )
		straArrCode = "SHA1";
	else if (0 == straACode.CompareNoCase("BJS") || 0 == straACode.CompareNoCase("PEK") || 0 == straACode.CompareNoCase("NAY"))
		straArrCode = "PEK1";
	else
		straArrCode = straACode;

	//CStringA straDptCode = straDCode;
	//if (0 == straDptCode.CompareNoCase("SHA"))
	//	straDptCode = "PVG";
	//orgCode=SHA&dstCode=PEK&departDate=20141228&timeBucket=0&cabin=0&n=tms.do%3ftranCode%3dTM0002&flag=0&sortRule=1&tripType=1
	straPostData.Format("orgCode=%s&dstCode=%s&departDate=%s&timeBucket=0&cabin=0&n=tms.do%%3ftranCode%%3dTM0002&flag=0&sortRule=1&tripType=1"
		, /*straDCode*/straDeptCode, /*straACode*/straArrCode, straStartDate);
	strconv_t strConv;

	//1.转成utf-8
	const char* pUtf8Str = strConv.a2utf8(straPostData.GetBuffer(0));
	std::string strUtf8Post = pUtf8Str;
	CCalKey::printStdString("GrapFlight-utf8", strUtf8Post, TRUE);

	//2.AES 加密
	std::string strKey((char*)m_u8AesEncryptKey);
	std::string strIv((char*)m_u8AesEncryptIV);
	std::string strAesEncrypt("");
	CCryptAesWrapper::CBC_AESEncryptStr(strKey, strIv, strUtf8Post, strAesEncrypt);
	CCalKey::printStdString("strAesEncrypt", strAesEncrypt, TRUE);

	//3 base64编码
	std::string strPostBase64("");
	CCryptAesWrapper::Base64Encode(strAesEncrypt, false, false, strPostBase64);
	CCalKey::printStdString("strPostBase64", strPostBase64, TRUE);
	CCalKey::printStdString("strPostBase64", strPostBase64, FALSE);

	//for test
	//char* pSessionId = "b5cd4f15f3c3b2ea683e72523bd0db6e";
	//std::string strSessionId(pSessionId);
	//end for test
	std::string strSessionId((char*)m_u8SessionId);

	////4.计算 X-Emp-Signature
	int iHashBufBytes = 20;//CALG_SHA1:20, CALG_MD5:16
	BYTE szHashBuf[21] = {0};//含一个\0 
	SecureZeroMemory(szHashBuf, sizeof(szHashBuf));
	int nPosDataBase64BufLen = strPostBase64.length();
	CCalKey::encryptHMAC((BYTE*)strPostBase64.data(), nPosDataBase64BufLen, m_u8XempEncryptKey, AES_XEMP_KEY_BYTE_LEN, CALG_SHA1, szHashBuf, 20);
	CCalKey::printByteArray("hmacXmp", szHashBuf, 20);

	std::string strXempSignature("");
	CCryptAesWrapper::Base64Encode(szHashBuf, 20, false, false, strXempSignature);
	CCalKey::printStdString("strXempSignature", strXempSignature, false);

	wstring httpResponseContent(L"");
	CString strUrl = _T("http://mobile.ceair.com/app_s/run/ch_jpyd?app=ceair&o=i");
	WinHttpClient httpClient(strUrl.GetBuffer(0));
	httpClient.SetTimeouts(0, 120000U, 100000U, 100000U);
	if (bChangeProxyIp)
		CDataProcess::GetInstance()->ChangeProxy(httpClient);

	BOOL bOpenlog = FALSE;
	if (m_bOutLog)
	{
		if( fopen_s( &pStream, pFilePath, "a+b" ) == 0 )
		{
			bOpenlog = TRUE;
		}
	}

	wstring headers = L"Host: mobile.ceair.com";
	headers += L"\r\nAccept: text/vnd.wap.wml";
	headers += L"\r\nUser-Agent: LightPole/3.0.0/android1.5";
	headers += L"\r\nPragma: no-cache";
	headers += L"\r\nConnection: Keep-Alive";
	headers += L"\r\nProxy-Connection: Keep-Alive";
	headers += L"\r\nContent-Type: application/x-www-form-urlencoded";
	headers += L"\r\nAccept-Encoding: gzip";
	headers += L"\r\nContent-Length:";

	//std::string strDecryptServerKeyData("");
	wchar_t wszBuf[100] = L"";
	swprintf_s(wszBuf, L"%d", nPosDataBase64BufLen);
	headers += wszBuf;

	//_session_id
	headers += L"\r\nX-Emp-Cookie: _session_id=";//c93b931c5cb63b117831195798f6a302
	wstring wstrSessionId(L"");
	wstrSessionId = s2ws(strSessionId);
	swprintf_s(wszBuf, L"%s", wstrSessionId.c_str());
	headers += wszBuf;
	headers += L"\r\nCookie: _session_id=";//c93b931c5cb63b117831195798f6a302
	headers += wszBuf;
	//X-Emp-Signature
	headers += L"\r\nX-Emp-Signature:";// 6amh1DCPknMJcY0yzgnhdtp8Wtk=
	wstring wstrxemp(L"");
	wstrxemp = s2ws(strXempSignature);
	swprintf_s(wszBuf, L"%s", wstrxemp.c_str());
	headers += wszBuf;

	httpClient.SetAdditionalDataToSend((BYTE *)strPostBase64.c_str(), nPosDataBase64BufLen);
	httpClient.SetAdditionalRequestHeaders(headers);

	if (bOpenlog)
	{
		//write header
		numwritten = fwrite( szHeadStr, 1, strlen(szHeadStr), pStream );
		numwritten = fwrite( headers.c_str(), 1, headers.length(), pStream );
		//write post data
		numwritten = fwrite( szPostStr, 1, strlen(szPostStr), pStream );
		numwritten = fwrite( strPostBase64.c_str(), 1, nPosDataBase64BufLen, pStream );
	}

	httpClient.SendHttpRequest(L"POST");
	std::string strRecvXml("");
	std::string strErrMsg;
	CByteBuf unzipBuf;
	std::string strContentLab = "<content>";
	if (0 != httpClient.GetResponseStatusCode().compare(L"200"))
	{
		CString str;
		str.Format(_T("-----error code=%s\n"), httpClient.GetResponseStatusCode().c_str());
		OutputDebugString(str);
	}
	else
	{
		wstring httpResponseHeader = httpClient.GetResponseHeader();
		const BYTE* pResponse = httpClient.GetRawResponseContent();
		
		BOOL bHaveException = FALSE;
		if (pResponse[0] == 0x1f && pResponse[1] == 0x8b)
		{
			////1.gzip解压
			//strconv_t strConv;
			//int iRespLen = httpClient.GetRawResponseContentLength();
			//TRACE(_T("\r\r recv msg len:%d"), iRespLen);
			//CCryptAesWrapper::GunzipBufToBuf(pResponse, iRespLen, &unzipBuf);
			//size_t uUnzipLen = unzipBuf.Size();

			////2.base 64 解码
			//CByteBuf base64DecodeBuf;
			//unsigned int nUnzipBufLen = 0;
			//std::string strBase64Decode("");
			//bool bOk = CCryptAesWrapper::Base64DecodeBufToBuf(unzipBuf.GetBufPtr(), uUnzipLen, &base64DecodeBuf);

			////3.aes 解密
			//CByteBuf aesDecryptBuf(TRUE);
			//std::string strKey((char*)m_u8AesDecryptKey);
			//std::string strIv((char*)m_u8AesDecryptIV);
			//bOk = CCryptAesWrapper::CBC_AESDecryptBufToBuf(strKey, strIv, base64DecodeBuf.GetBufPtr(), base64DecodeBuf.Size(), &aesDecryptBuf);

			////4.utf8 -》 ascii
			//strconv_t strConvXml;
			////strRecvXml = strConvXml.utf82a((const char*)aesDecryptBuf.GetBufPtr());
			//strRecvXml = (const char*)aesDecryptBuf.GetBufPtr();
			//if (aesDecryptBuf.Size() > 200)
			//{
			//	bGet = __ParseCeairFlight(strRecvXml, flightList);
			//}

			//1.gzip解压
			int iRespLen = httpClient.GetRawResponseContentLength();

			if (bOpenlog)
			{
				numwritten = fwrite( szResponseStr, 1, strlen(szResponseStr), pStream );
				numwritten = fwrite( pResponse, 1, iRespLen, pStream );
			}

			if (bOpenlog && NULL != pStream)
			{
				fclose( pStream );
				pStream = NULL;
			}

			//TRACE(_T("\r\r recv msg len:%d"), iRespLen);
			//if(iRespLen > 100)
			//{
			//	CString strRespLogName;
			//	CTime t = CTime::GetCurrentTime();
			//	USES_CONVERSION;
			//	strRespLogName.Format(_T("D:\\log\\%02d%02d%02d_%s_%s_%s.log"), t.GetHour(), t.GetMinute(), t.GetSecond(), A2W(straDCode), A2W(straACode), A2W(straFlightStratDate));
			//	wstring wstrLogPath(strRespLogName.GetBuffer(0));
			//	httpClient.SaveResponseToFile(wstrLogPath);
			//}

			std::string strUnzip("");
			try
			{
				CCryptAesWrapper::GunzipBuf(pResponse, iRespLen, strUnzip);
			}
			catch (...)
			{
				goto GrapFlight_Ret;
			}
			
			size_t uUnzipLen = strUnzip.size();
			TRACE(_T("\r\n uUnzipLen=%d"),uUnzipLen);

			//2.base 64 解码
			std::string strBase64Decode("");
			CCryptAesWrapper::Base64Decode(strUnzip, strBase64Decode);

			if(strBase64Decode.size() > 200)
			{
				//3.aes 解密
				std::string strKey((char*)m_u8AesDecryptKey);
				std::string strIv((char*)m_u8AesDecryptIV);
				std::string strAesDecTxt("");
				//bOk = CCryptAesWrapper::CBC_AESDecryptBufToBuf(strKey, strIv, base64DecodeBuf.GetBufPtr(), base64DecodeBuf.Size(), &aesDecryptBuf);
				try
				{
					CCryptAesWrapper::CBC_AESDecryptStr2(strKey, strIv, strBase64Decode, strAesDecTxt, false);
				}
				catch (...)
				{
					bHaveException = TRUE;
					OutputDebugString(_T("CCryptAesWrapper::CBC_AESDecryptStr2 has exception."));
				}
				
				if (!bHaveException)
				{
					//4.utf8 -》 ascii
					strconv_t strConvXml;
					strRecvXml = strConvXml.utf82a(strAesDecTxt.c_str());
					basic_string <char>::size_type indexContentLab = strRecvXml.find(strContentLab);
					if ((strAesDecTxt.size() > 100) && (indexContentLab != string::npos ))
					{
						//xml文件是utf8的，不需要转成ascii可直接解析
						bGet = __ParseCeairFlight(strAesDecTxt, flightList);
						TRACE("\r\n ---------------------------------------------------get %s:%s->%s  X carbin ret=%d, flightCount=%d\r\n", straStartDate, straDCode, straACode, bGet, flightList.size());
					}
				}
			}
			else
			{
				//多数是系统忙，请重试
				//您选择的航程当天无东航航班或已售完，请重新选择其它日期，谢谢！
				bGet = FALSE;
			}

		}
		else
		{
			httpResponseContent = httpClient.GetResponseContent();
			//strResp = CDataProcess::Unicode2Ansi(httpResponseContent.c_str());
		}
	}

GrapFlight_Ret:
	if (bOpenlog && NULL != pStream)
	{
		fclose( pStream );
		pStream = NULL;
	}

	return bGet;
}

BOOL CGrapCeFlight::__ParseCeairFlight(const std::string & strXml, std::list<SCeairFlightInfo*> & flightList)
{
	BOOL bGet = FALSE;
	TiXmlDocument doc;
	TiXmlElement* pRoot = NULL;

	TiXmlNode* pNode = NULL;
	TiXmlElement* pElement = NULL;
	const char* pBuf = NULL;
	const char* pCabinStr = "X";
	const char* pMoreSeatNumStr = "A";
	int	nMoreSeatNum = 9;

	//<?xml version="1.0" encoding="UTF-8" ?> 
	//<content>
	//<head>
	//</head>
	//</body>
	//<flightList>
	//<flightItem orgterminal="--" dstterminal="T2" istop="" filghtno="MU5582" orgdate="20150127" dstdate="20150127" flighttime="20:30~22:20" orgcode="WEH" dstcode="SHA" airplanestyle="320" cabincode="X" seatnumber="5" price="250" points="" otherparams="&a=b&c=d" discount="超值" islingyanornot="0" meal="8" codesharedesc="" cabinclass="经济舱" cabininfo1="WEH,SHA,MU5582,20150127,X,320,250,0,0,0,0,0,0,0,0,超值,2030,2220,,--,T2,XB2M,,,331,0,,,G,8882F65103CFA8E16DFE23DC7D503268,5,B2M15002,不得退改签/B2M15002,0.0-0.0-0.0-null-0.0-0.0-null-0-0-0-0-0-null-0.0-0.0-null-0-0-0-0-0-null-0.0-0.0-null-0-0-0-0-0-MU5582,8,,20150127,,不得签转、更改、退票。,MU,0,0,0,,8" cabininfo2="" /> 
	//</flightList>
	//</body>
	//</content>

	doc.Parse(strXml.c_str(), 0, TIXML_ENCODING_UTF8);
	if ( doc.Error() )
	{
		TRACE("\r\n Error in parse strXml %s: %s\n", doc.Value(), doc.ErrorDesc() );
	}
	TiXmlHandle docHandle(&doc);

	pRoot = doc.RootElement();
	TiXmlNode*  pRootNode = pRoot;
	TiXmlHandle rootHandle(pRootNode);
	pBuf = rootHandle.ToElement()->Value();//"content"

	CStringA straTmp;
	flightList.clear();
	pElement = docHandle.Child("content", 0).Child("body", 0).Child("flightList", 0).Child("flightItem", 0).ToElement();
	if (NULL == pElement)
		goto ParseCeairFlight_Ret;

	//解析舱位
	for(TiXmlNode*  pNode = pElement; pNode;   pNode = pNode->NextSibling("flightItem"))
	{
		pElement = pNode->ToElement();
		if (NULL != pElement)
		{
			pBuf = pElement->Attribute("cabincode");
			bGet = TRUE;
			if (NULL != pBuf)
			{
				if (0 == strcmp(pCabinStr, pBuf))
				{
					SCeairFlightInfo * pCeairFlightInfo = new SCeairFlightInfo;

					pBuf = pElement->Attribute("orgcode");
					straTmp.Format("%s", pBuf);
					straTmp = straTmp.Trim();
					pCeairFlightInfo->straFromCityCode = straTmp;

					pBuf = pElement->Attribute("dstcode");
					straTmp.Format("%s", pBuf);
					straTmp = straTmp.Trim();
					pCeairFlightInfo->straToCityCode = straTmp;

					pBuf = pElement->Attribute("filghtno");
					straTmp.Format("%s", pBuf);
					straTmp = straTmp.Trim();
					pCeairFlightInfo->straFlightNo = straTmp.Mid(2);
					pCeairFlightInfo->straCompany = straTmp.Left(2);

					pBuf = pElement->Attribute("orgdate");
					straTmp.Format("%s", pBuf);
					straTmp = straTmp.Trim();
					pCeairFlightInfo->straFromDate = straTmp.Left(4) + "-" + straTmp.Mid(4, 2) + "-" + straTmp.Right(2);

					pBuf = pElement->Attribute("seatnumber");
					if (0 == strcmp(pMoreSeatNumStr, pBuf))
					{
						pCeairFlightInfo->nRemainSeat = 9;
					}
					else
					{
						pCeairFlightInfo->nRemainSeat = atoi(pBuf);
					}
					//价格
					pBuf = pElement->Attribute("price");
					pCeairFlightInfo->nPrice = atoi(pBuf);

					flightList.push_back(pCeairFlightInfo);
					TRACE("\r\n %s|%s|%s|%s|seat:%d", pCeairFlightInfo->straFromCityCode, pCeairFlightInfo->straToCityCode, pCeairFlightInfo->straFlightNo
						, pCeairFlightInfo->straFromDate, pCeairFlightInfo->nRemainSeat);
				}
			}
		}
	}

ParseCeairFlight_Ret:

	return bGet;
}

//void CGrapCeFlight::__WriteHttpResponse(const CStringA & straFileName, const BYTE* pBuf, int nBufBytes)
//{
//	FILE * file;
//	int nNumwritten = 0;
//	char szFilePath[100] = {0};
//	sprintf_s(szFilePath, 100, "%s", straFileName);
//	if( 0 == fopen_s( &file, szFilePath, "a+b" ) )
//	{
//		nNumwritten = fwrite(pBuf, 1, nBufBytes, file);
//		fclose( file );
//	}
//}