#ifndef		ENCRYPTMSGDECRYPTMSG_H
#define		ENCRYPTMSGDECRYPTMSG_H

bool 
MyEncryptMessage(const char* szData,
				 BYTE *szEncryptData, DWORD &dwEncryptData);

bool
MyDecryptMessage(BYTE *szEnCryptData, DWORD dwEnCryptData);


bool
MyEncryptMessageStep(const char* szData,
					 BYTE *szEncryptData, DWORD &dwEncryptData);

bool
MyDecryptMessageStep(BYTE *szEnCryptData, DWORD dwEnCryptData);

#endif