#pragma once
#include "struct.h"

int SKF_Sign(BYTE **pbSignature, ULONG *ppulSignLen);
int SKF_Verify(BYTE *pbSignature, ULONG pulSignLen);
int WriteToLog(char *path, BYTE* pbSignature, ULONG pulSignLen);
int ReadInLog(char *path, BYTE* txt, ULONG len);

int VerifyOther();