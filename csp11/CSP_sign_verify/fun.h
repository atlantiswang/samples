#pragma once

#include "stdafx.h"

PCCERT_CONTEXT
ImportCert(wchar_t *, TCHAR *);

void
printByte(BYTE *pbData, DWORD dwLen);