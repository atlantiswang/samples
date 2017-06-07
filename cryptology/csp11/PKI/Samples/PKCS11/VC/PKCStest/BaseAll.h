#ifndef _BASSALL_H_
#define _BASSALL_H_

#include <windows.h>
#include <stdio.h>

#include <pkcs11/cryptoki_ext.h>

class CP11TestBase
{
public:
	CP11TestBase(char *libFilePath);
	virtual ~CP11TestBase();

	CK_RV Finalize(void);
	CK_RV Initialize(void);

protected:
	bool _CheckRV(char *pInfo, CK_RV rv);

protected:
	CK_SESSION_HANDLE m_hSession;
	CK_FUNCTION_LIST_PTR m_p11;
	char m_ucPin[1024];

	CK_SLOT_ID_PTR m_pSlotList;
	HMODULE m_hDll;
	char m_libFileName[MAX_PATH];

	HANDLE m_hStdErr;
	HANDLE m_hStdOut;
};

#endif // _BASSALL_H_

