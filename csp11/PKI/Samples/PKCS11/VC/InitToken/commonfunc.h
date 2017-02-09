#include "StdAfx.h"
#include <Windows.h>

int Utf8StringToAppString(const char * utf8Str_in, int iInLength, char* appStr_out);
int AppStringToUtf8String(const char * appStr_in, int iInLength, char* utf8Str_out);
int Utf8AnsiConvert(const char * Str_in, int iInLength, int iInType/*CP_UTF8,CP_ACP*/, char* Str_out);
bool UTF8BytesToANSI(char * pArray, int iLength);
CK_RV RunC_InitToken(
					 CK_SLOT_ID			slotID,		// ID of the token's slot
					 CK_CHAR_PTR		pPin,		// the SO's initial PIN
					 CK_ULONG			ulPinLen,	// length in bytes of the PIN
					 CK_CHAR_PTR		pLabel		// 32-byte token label (blank padded)
					 );
CK_RV RunC_InitPIN(
				   CK_SESSION_HANDLE	hSession,	// the session's handle
				   CK_CHAR_PTR			pPin,		// the normal user's PIN
				   CK_ULONG				ulPinLen	// length in bytes of the PIN
				   );
CK_RV RunC_SetPIN(
				  CK_SESSION_HANDLE		hSession,	// the session's handle
				  CK_CHAR_PTR			pOldPin,	// the old PIN
				  CK_ULONG				ulOldLen,	// length of the old PIN
				  CK_CHAR_PTR			pNewPin,	// the new PIN
				  CK_ULONG				ulNewLen	// length of the new PIN)
				  );
CK_RV RunC_Login(
				 CK_SESSION_HANDLE		hSession,	// the session's handle
				 CK_USER_TYPE			userType,	// the user type
				 CK_CHAR_PTR			pPin,		// the user's PIN
				 CK_ULONG				ulPinLen	// the length of the PIN)
				);