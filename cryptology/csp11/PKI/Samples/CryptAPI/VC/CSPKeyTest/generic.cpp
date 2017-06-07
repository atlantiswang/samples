#include "StdAfx.h"
#include "generic.h"

void ShowData(unsigned char * pData, unsigned long ulDataLen)
{
	if(pData == NULL)
	{
		cout << "Data to be showed is NULL!" << endl;
		return;
	}
	else
	{
		cout << "Data (" << ulDataLen << " bytes) in HEX:";
		cout.setf(std::ios::uppercase);
		cout << std::setfill('0') << std::setw(2);
		for(unsigned long i = 0; i < ulDataLen; ++i)
		{
			if(0 == i % 16)
				cout << endl;

			cout << std::setw(2) << hex << (DWORD)pData[i] << ' ';
		}
	}

	cout << dec << endl;

	return ;
}

void BeginAction(const string& strOperation)
{
	cout << strOperation.c_str();
}

#ifndef NERR_BASE
#	define NERR_BASE		2100
#	define MAX_NERR			NERR_BASE + 899
#endif

void ActionFailed(DWORD dwLastError)
{
	cout.setf(std::ios::uppercase);
	cout<< "......[FAILED]." << endl
		<< "    [0x" << std::setfill('0') << std::setw(8) << hex
		<< dwLastError << "] "
		<< dec
		<< endl;

//	DWORD dwLastError = GetLastError();
	HMODULE hModule = NULL; // default to system source
	LPSTR MessageBuffer = NULL;
	DWORD dwBufferLength = 0;

	DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_FROM_SYSTEM ;

	if(dwLastError >= NERR_BASE && dwLastError <= MAX_NERR)
	{
		hModule = LoadLibraryEx("netmsg.dll", NULL, LOAD_LIBRARY_AS_DATAFILE);

		if(hModule != NULL)
		{
			dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
		}
	}

	if(dwBufferLength = FormatMessageA(dwFormatFlags, hModule,
		dwLastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR) &MessageBuffer, 0, NULL))
	{
		cout.setf(std::ios::uppercase);
		//cout<< "ERROR: " << strInfo << endl
		cout<< "......[FAILED]." << endl
			<< "    [0x" << std::setfill('0') << std::setw(8) << hex
			<< dwLastError << "] "
			<< MessageBuffer << dec
			<< endl;

		LocalFree(MessageBuffer);
	}

	if(hModule != NULL)
	{
		FreeLibrary(hModule);
	}
}

void ActionSuccess(void)
{
	cout << "......[OK]" << endl;
}

void GetProvParam(void)
{
	HCRYPTPROV hCryptProv = NULL;
	cout << endl << "Test CSP: " << CSP_NAME << endl << endl;

	BeginAction("CryptAcquireContext()");
	if(!CryptAcquireContext(&hCryptProv,
				NULL,
				CSP_NAME,
				PROV_RSA_FULL,
				CRYPT_VERIFYCONTEXT))
	{
		ActionFailed(GetLastError());
		return;
	}
	else
	{
		ActionSuccess();
	}

	// Hold the handle and release when this function return.
	HCRYPTPROV_Holder holder(hCryptProv);

	//Enum algs those CSP support:
	DWORD i = 0;
	CHAR szName[100] = {0}; // Often allocated dynamically
	BYTE pbData[1000] = {0}; // Often allocated dynamically
	DWORD cbData = 0;
	DWORD dwFlags = 0;
	CHAR *pszAlgType = NULL;
	
	// Enumerate the supported algorithms.
	cout<< "  ALG_ID     KeyLen   Type            Name" << endl
		<< "----------------------------------------------------------------" << endl;

	for(i=0 ; ; ++i) 
	{
		// Set the CRYPT_FIRST flag the first time through the loop.
		if(i == 0) 
		{
			dwFlags = CRYPT_FIRST;
		} 
		else 
		{
			dwFlags = 0;
		}
		
		// Retrieve information about an algorithm.
		cbData = 1000;
		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, pbData, &cbData, dwFlags)) 
		{
			DWORD dwLastErr = GetLastError();
			if(ERROR_NO_MORE_ITEMS == dwLastErr)
			{
				// Exit the loop.
				break;
			}
			else 
			{
				;
				return;
			}
		}
		// Extract algorithm information from the 'pbData' buffer.
		PROV_ENUMALGS* pEnum = (PROV_ENUMALGS*)pbData;
		
		// Determine the algorithm type.
		switch(GET_ALG_CLASS(pEnum->aiAlgid)) 
		{
		case ALG_CLASS_DATA_ENCRYPT: pszAlgType = "Encrypt     ";
			break;
		case ALG_CLASS_HASH: pszAlgType = "Hash        ";
			break;
		case ALG_CLASS_KEY_EXCHANGE: pszAlgType = "Exchange    ";
			break;
		case ALG_CLASS_SIGNATURE: pszAlgType = "Signature   ";
			break;
		default: pszAlgType = "Unknown     ";
		}
		
		// Print information about the algorithm.  
//		printf("Algid:%8.8xh, Bits:%-4d, Type:%s, NameLen:%-2d, Name:%s\n",
//			aiAlgid, dwBits, pszAlgType, dwNameLen, szName
//			);

//		cout<< "ALG_ID: " << std::setfill('0') << std::setw(8) << hex << pEnum->aiAlgid
//			<< "KeyLen: " << std::setfill(' ') << std::setw(4) << dec << pEnum->dwBitLen
//			<< "Type  : " << pszAlgType
//			<< "Name  : " << pEnum->szName
//			<< endl;
		cout<< "  "
			<< std::setfill('0') << std::setw(8) << hex << pEnum->aiAlgid
			<< "    "
			<< std::setfill(' ') << std::setw(4) << dec << pEnum->dwBitLen
			<< "    "
			<< pszAlgType
			<< "    "
			<< pEnum->szName
			<< endl;
	}

	//ActionSuccess();

}













