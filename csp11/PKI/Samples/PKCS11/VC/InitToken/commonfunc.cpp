#include "commonfunc.h"

int Utf8StringToAppString(const char * utf8Str_in, int iInLength, char* appStr_out)
{
	int ret = 0;
	try
	{
		ret = Utf8AnsiConvert(utf8Str_in, iInLength, CP_UTF8, appStr_out);
	}
	catch (...)
	{
		ret = -1;
	}
	return ret;
}

int AppStringToUtf8String(const char * appStr_in, int iInLength, char* utf8Str_out)
{
	int ret = 0;
	try
	{
		ret = Utf8AnsiConvert(appStr_in, iInLength, CP_ACP, utf8Str_out);
	}
	catch (...)
	{
		ret = -1;
	}
	return ret;
}

int Utf8AnsiConvert(const char * Str_in, int iInLength, int iInType/*CP_UTF8,CP_ACP*/, char* Str_out)
{

	if(NULL == Str_in || (iInLength <1 && iInLength != -1))
		return -1; //input param invaild
	if(iInType != CP_ACP && iInType != CP_UTF8)
		return -1;

	int TYPE_IN = 0, TYPE_OUT = 0;
	if(CP_ACP == iInType)
	{
		TYPE_IN = CP_ACP;
		TYPE_OUT = CP_UTF8;
	}
	else
	{
		TYPE_IN = CP_UTF8;
		TYPE_OUT = CP_ACP;
	}

	//UTF8 to UNICODE
	
	int iUnicodeLen = 0;
	WCHAR *pwcharUnicode = NULL;
	iUnicodeLen = MultiByteToWideChar(TYPE_IN, 0, Str_in, iInLength, NULL, 0);
	if(iUnicodeLen < 1)
		return -1;
	pwcharUnicode = new WCHAR[iUnicodeLen+1];
	memset(pwcharUnicode, 0x00, sizeof(WCHAR)*(iUnicodeLen+1));
	if(iUnicodeLen != MultiByteToWideChar(TYPE_IN, 0, Str_in, iInLength, pwcharUnicode, iUnicodeLen))
	{
		if(pwcharUnicode != NULL)
		{
			delete [] pwcharUnicode;
			pwcharUnicode = NULL;
		}
		return -1;
	}

	//UNICODE to ANSI
	int iAnsiLen = 0;
	char *pszAnsi = NULL;
	
	iAnsiLen = WideCharToMultiByte(TYPE_OUT, 0, pwcharUnicode, iUnicodeLen, NULL, 0, NULL,FALSE);
	if(iAnsiLen < 1)
	{
		if(pwcharUnicode != NULL)
		{
			delete [] pwcharUnicode;
			pwcharUnicode = NULL;
		}
		return -1;
	}
	if(NULL == Str_out)//为了二次调用
	{
		if(pwcharUnicode != NULL)
		{
			delete [] pwcharUnicode;
			pwcharUnicode = NULL;
		}
		return iAnsiLen;
	}

	pszAnsi = new char[iAnsiLen+1];
	memset(pszAnsi, 0x00, iAnsiLen+1);
	if(iAnsiLen != WideCharToMultiByte(TYPE_OUT, 0, pwcharUnicode, iUnicodeLen, pszAnsi, iAnsiLen, NULL,FALSE))
	{
		if(pwcharUnicode != NULL)
		{
			delete [] pwcharUnicode;
			pwcharUnicode = NULL;
		}
		if(pszAnsi != NULL)
		{
			delete[] pszAnsi;
			pszAnsi = NULL;
		}
		return -1;
	}

	memcpy(Str_out, pszAnsi, iAnsiLen);
	if(pwcharUnicode != NULL)
	{
		delete [] pwcharUnicode;
		pwcharUnicode = NULL;
	}
	if(pszAnsi != NULL)
	{
		delete[] pszAnsi;
		pszAnsi = NULL;
	}
	return iAnsiLen;

}

CK_RV RunC_InitToken(
					 CK_SLOT_ID			slotID,		// ID of the token's slot
					 CK_CHAR_PTR		pPin,		// the SO's initial PIN
					 CK_ULONG			ulPinLen,	// length in bytes of the PIN
					 CK_CHAR_PTR		pLabel		// 32-byte token label (blank padded)
					 )
{
	//convert ANSI to UTF8
	CK_ULONG ulPinUtf8_length = 0;
	CK_ULONG ulLabelutf8_length = 0;
	char *pszPinUtf8 = NULL;
	char szUtf8TokenName[32];
	memset(szUtf8TokenName, 0x20/*blank*/, 32);

	if(ulPinLen > 0)
	{
		ulPinUtf8_length = AppStringToUtf8String((const char *)pPin,ulPinLen, NULL);
		if(ulPinUtf8_length > 0)
		{
			pszPinUtf8 = new char[ulPinUtf8_length+1];
			memset(pszPinUtf8, 0x00, ulPinUtf8_length+1);
			AppStringToUtf8String((const char *)pPin,ulPinLen,  pszPinUtf8);	
		}
	}
	if(pLabel != NULL)
	{
		CK_ULONG ulLabelutf8_length = AppStringToUtf8String((const char *)pLabel,strlen((const char *)pLabel), NULL);
		if(ulLabelutf8_length > 32)
		{
			return CKR_DATA_LEN_RANGE;
		}
		if(ulLabelutf8_length > 0)
		{
			char * pBuff = new char[ulLabelutf8_length+1];
			memset(pBuff, 0x00, ulLabelutf8_length+1);
			AppStringToUtf8String((const char *)pLabel, strlen((const char *)pLabel), pBuff);	
			memcpy(szUtf8TokenName, pBuff, ulLabelutf8_length);
			if(pBuff != NULL)
			{
				delete[] pBuff;
				pBuff = NULL;
			}
		}
	}
	//end convert
	CK_RV rv = C_InitToken(slotID, (unsigned char *)pszPinUtf8, ulPinUtf8_length, (unsigned char *)szUtf8TokenName);

	if(pszPinUtf8 != NULL)
	{
		delete[] pszPinUtf8;
		pszPinUtf8 = NULL;
	}
	return rv;
}

CK_RV RunC_InitPIN(
				   CK_SESSION_HANDLE	hSession,	// the session's handle
				   CK_CHAR_PTR			pPin,		// the normal user's PIN
				   CK_ULONG				ulPinLen	// length in bytes of the PIN
				   )
{
	//convert ANSI to UTF8
	CK_ULONG ulPinUtf8_length = 0;
	char *pszPinUtf8 = NULL;
	
	if(ulPinLen > 0)
	{
		ulPinUtf8_length = AppStringToUtf8String((const char *)pPin,ulPinLen, NULL);
		if(ulPinUtf8_length > 0)
		{
			pszPinUtf8 = new char[ulPinUtf8_length+1];
			memset(pszPinUtf8, 0x00, ulPinUtf8_length+1);
			AppStringToUtf8String((const char *)pPin,ulPinLen,  pszPinUtf8);	
		}
	}
	//end convert
	CK_RV rv = C_InitPIN(hSession, (unsigned char *)pszPinUtf8, ulPinUtf8_length);
	
	if(pszPinUtf8 != NULL)
	{
		delete[] pszPinUtf8;
		pszPinUtf8 = NULL;
	}
	return rv;
	return CKR_OK;
}

CK_RV RunC_SetPIN(
				  CK_SESSION_HANDLE		hSession,	// the session's handle
				  CK_CHAR_PTR			pOldPin,	// the old PIN
				  CK_ULONG				ulOldLen,	// length of the old PIN
				  CK_CHAR_PTR			pNewPin,	// the new PIN
				  CK_ULONG				ulNewLen	// length of the new PIN)
				  )
{
	//convert ANSI to UTF8
	CK_ULONG ulOldPinUtf8_length = 0;
	char *pszOldPinUtf8 = NULL;	
	if(ulOldLen > 0)
	{
		ulOldPinUtf8_length = AppStringToUtf8String((const char *)pOldPin,ulOldLen, NULL);
		if(ulOldPinUtf8_length > 0)
		{
			pszOldPinUtf8 = new char[ulOldPinUtf8_length+1];
			memset(pszOldPinUtf8, 0x00, ulOldPinUtf8_length+1);
			AppStringToUtf8String((const char *)pOldPin,ulOldLen,  pszOldPinUtf8);	
		}
	}
	CK_ULONG ulNewPinUtf8_length = 0;
	char *pszNewPinUtf8 = NULL;	
	if(ulNewLen > 0)
	{
		ulNewPinUtf8_length = AppStringToUtf8String((const char *)pNewPin,ulNewLen, NULL);
		if(ulNewPinUtf8_length > 0)
		{
			pszNewPinUtf8 = new char[ulNewPinUtf8_length+1];
			memset(pszNewPinUtf8, 0x00, ulNewPinUtf8_length+1);
			AppStringToUtf8String((const char *)pNewPin,ulNewLen,  pszNewPinUtf8);	
		}
	}
	//end convert
	CK_RV rv = C_SetPIN(hSession, (unsigned char *)pszOldPinUtf8, ulOldPinUtf8_length, (unsigned char *)pszNewPinUtf8, ulNewPinUtf8_length);
	
	if(pszOldPinUtf8 != NULL)
	{
		delete[] pszOldPinUtf8;
		pszOldPinUtf8 = NULL;
	}
	if(pszNewPinUtf8 != NULL)
	{
		delete[] pszNewPinUtf8;
		pszNewPinUtf8 = NULL;
	}
	return rv;
}

CK_RV RunC_Login(
				 CK_SESSION_HANDLE	hSession,	// the session's handle
				 CK_USER_TYPE		userType,	// the user type
				 CK_CHAR_PTR			pPin,	// the user's PIN
				 CK_ULONG			ulPinLen	// the length of the PIN)
				)
{
	//convert ANSI to UTF8
	CK_ULONG ulPinUtf8_length = 0;
	char *pszPinUtf8 = NULL;
	
	if(ulPinLen > 0)
	{
		ulPinUtf8_length = AppStringToUtf8String((const char *)pPin,ulPinLen, NULL);
		if(ulPinUtf8_length > 0)
		{
			pszPinUtf8 = new char[ulPinUtf8_length+1];
			memset(pszPinUtf8, 0x00, ulPinUtf8_length+1);
			AppStringToUtf8String((const char *)pPin,ulPinLen,  pszPinUtf8);	
		}
	}
	//end convert
	CK_RV rv = C_Login(hSession, userType, (unsigned char *)pszPinUtf8, ulPinUtf8_length);
	if (CKR_USER_ALREADY_LOGGED_IN == rv)
		rv = CKR_OK;
	
	if(pszPinUtf8 != NULL)
	{
		delete[] pszPinUtf8;
		pszPinUtf8 = NULL;
	}
	return rv;
}

bool UTF8BytesToANSI(char * pArray, int iLength)
{
	int i = 0;
	
	for(i = iLength-1; i >= 0; --i)
	{
		if(' ' != pArray[i])
			break;
	}
	//convert UTF8 to ANSI
	{
		int ansi_length = 0;
		ansi_length = Utf8StringToAppString(pArray, i+1, NULL);
		if(ansi_length > 0)
		{
			char * pBuff = new char[ansi_length+1];
			memset(pBuff, 0x00, ansi_length+1);
			Utf8StringToAppString(pArray, i+1, pBuff);
			strcpy(pArray,pBuff);
			if(pBuff != NULL)
			{
				delete[] pBuff;
				pBuff = NULL;
			}	
		}
		else
		{
			strcpy(pArray, "");
		}
	}
	return true;
}