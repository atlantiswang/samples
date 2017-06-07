#ifndef _COMMON_H_
#define _COMMON_H_

#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include <pkcs11/cryptoki_ext.h>
#define MODULUS_BIT_LENGTH  1024 // Could be 512/1024

#define	countof(a)			(sizeof(a) / sizeof(CK_ATTRIBUTE))

void ShowTitle(void);

// If you want to show data in hex-string, please set SHOW_DATA_BIN to 1.
#define SHOW_DATA_BIN 1
void ShowData(const char* pszMsg, unsigned char *pData, unsigned long ulDataLen);

#endif // _COMMON_H_
