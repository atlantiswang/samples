#ifndef SIGNVERIFY_H
#define SIGNVERIFY_H

bool
MySignMessage(char *, DWORD& , BYTE *);

bool
MyVerifyMessageSignature(BYTE *, DWORD);

#endif