
#include "baseall.h"

CP11TestBase::CP11TestBase(char *libFilePath) :
	m_hDll(NULL),
	m_pSlotList(NULL_PTR)
{
	memset(m_libFileName, 0, MAX_PATH);
	memcpy(m_libFileName, libFilePath, lstrlen(libFilePath));
	memset(m_ucPin, 0, 32);

	m_hStdErr = GetStdHandle(STD_ERROR_HANDLE);
	m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

CP11TestBase::~CP11TestBase()
{
	if(m_pSlotList != NULL_PTR)
	{
		free(m_pSlotList);
		m_pSlotList = NULL_PTR;
	}
	if(m_hDll != NULL_PTR)
	{
		FreeLibrary(m_hDll);
		m_hDll = NULL;
	}
}
CK_RV CP11TestBase::Initialize(void)
{
	CK_RV rv = CKR_OK;

	printf("\nLoad PKCS#11 Library!\n");
	m_hDll = LoadLibrary(m_libFileName);
	if(m_hDll == NULL)
	{
		printf("    ERROR: LoadLibrary(%s) failed. [SysErrCode: 0x%08X]\n",
			m_libFileName, GetLastError());
		return CKR_GENERAL_ERROR;
	}

	//Get the list of the PKCS#11 function entries.
	CK_C_GetFunctionList pC_GetFunctionList = (CK_C_GetFunctionList)
			GetProcAddress(m_hDll, "C_GetFunctionList");
	if(pC_GetFunctionList == NULL)
	{
		printf("    ERROR: Can not locate PKCS#11 function list! [SysErrCode: 0x%08X]\n", GetLastError());
		Finalize();
		return CKR_GENERAL_ERROR;
	}

	//Get PKCS#11 function list.
	rv = pC_GetFunctionList(&m_p11);
	if(!_CheckRV("Get PKCS#11 function list", rv))
	{
		Finalize();
		return rv;
	}

	rv = m_p11->C_Initialize(NULL_PTR);
	if(!_CheckRV("C_Initialize()", rv))
	{
		Finalize();
		return rv;
	}

	// Get the number of slots with a token attached.
	unsigned long ulCount;
	rv = m_p11->C_GetSlotList(TRUE, NULL_PTR, &ulCount);
	if(!_CheckRV("C_GetSlotList(TRUE, NULL)", rv))
	{
		Finalize();
		return rv;
	}

	if(ulCount <= 0)
	{
		printf("    WARNING: No slot with token attached.\n");
		Finalize();
		return CKR_TOKEN_NOT_PRESENT;
	}

	// Allocate memory buffer for the slot list.
	m_pSlotList = (CK_SLOT_ID_PTR) malloc(ulCount * sizeof(CK_SLOT_ID));
	if(!m_pSlotList)
	{
		printf("    ERROR: Not enough memory!\n");
		Finalize();
		return CKR_HOST_MEMORY;
	}
	else
	{
		printf("There are %d slot%s attached to USB port.\n", ulCount, ulCount > 1 ? "s" :"");
	}

	// Okay, we have the buffer allocated. Let's get the slot list.
	//cout << "Get the slots information." << endl;
	rv = m_p11->C_GetSlotList(TRUE, m_pSlotList, &ulCount);
	if(!_CheckRV("C_GetSlotList(TRUE, buffer)", rv))
	{
		Finalize();
		return rv;
	}

	// Open a session to communicate with the token.
	rv = m_p11->C_OpenSession(m_pSlotList[0],
		 CKF_RW_SESSION | CKF_SERIAL_SESSION,
		 NULL_PTR, NULL_PTR, &m_hSession);
	if(!_CheckRV("C_OpenSession()", rv))
	{
		Finalize();
		return rv;
	}

	printf("\nPlease enter your User-PIN: ");
	scanf("%s", m_ucPin);
	rv = m_p11->C_Login(m_hSession, CKU_USER, (unsigned char*)m_ucPin, lstrlen(m_ucPin)); 
	if(!_CheckRV("C_Login(CKU_USER)", rv))
	{
		Finalize();
		return rv;
	} 
	return rv;
}

CK_RV CP11TestBase::Finalize(void)
{
	printf("\nFinalize the PKCS#11's library.\n");

	CK_RV rv = CKR_OK;
	if(m_hDll)
	{
		if(m_p11)
		{
			if(m_hSession)
			{
				rv = m_p11->C_CloseSession(m_hSession);
				_CheckRV("C_CloseSession()", rv);
			}

			rv = m_p11->C_Finalize(0);
			_CheckRV("C_Finalize()", rv);
			m_p11 = NULL_PTR;
		}

		FreeLibrary(m_hDll);
		m_hDll = NULL;
	}

	return CKR_OK;
}

bool CP11TestBase::_CheckRV(char *pInfo, CK_RV rv)
{
	printf("%s ... ", pInfo);

	if(rv == CKR_OK)
	{
		if(NULL != m_hStdOut)
			SetConsoleTextAttribute(m_hStdOut, FOREGROUND_INTENSITY|FOREGROUND_GREEN);

		printf("OK");

		if(NULL != m_hStdOut)
			SetConsoleTextAttribute(m_hStdOut, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);

		printf("\n");
		return true;
	}
	else
	{
		if(NULL != m_hStdErr)
			SetConsoleTextAttribute(m_hStdErr, FOREGROUND_INTENSITY|FOREGROUND_RED);

		printf("FAILED");

		if(NULL != m_hStdErr)
			SetConsoleTextAttribute(m_hStdErr, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);

		printf(" [ErrCode: 0x%08X]\n", rv);

		return false;
	}
}
