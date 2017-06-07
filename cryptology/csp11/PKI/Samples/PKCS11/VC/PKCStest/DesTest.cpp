
#include "common.h"
#include "DesTest.h"

DesTest::DesTest(char* dll_file_path):CP11TestBase(dll_file_path)
{
	m_hKey = 0;
}

DesTest::~DesTest()
{
}

void DesTest::Test()
{
	if(CKR_OK != Initialize())
		return;
	GenerateKey();
	if(m_hKey == 0)
	{
		Finalize();
		return ;
	}
	crypt_Single();
	crypt_Update();
	Finalize();
}

void DesTest::GenerateKey()
{
	CK_OBJECT_CLASS oClass = CKO_SECRET_KEY;
	CK_KEY_TYPE keyType = CKK_DES; 
	CK_BBOOL bTrue = true;
	CK_BBOOL bFalse = false;
	CK_ULONG ulLen = 8;
	CK_MECHANISM mechanism = {CKM_DES_KEY_GEN, NULL_PTR, 0};
	CK_ATTRIBUTE Destem[] = {
		{CKA_CLASS, &oClass, sizeof(CK_OBJECT_CLASS)},
		{CKA_KEY_TYPE, &keyType, sizeof(CK_KEY_TYPE)},
		{CKA_TOKEN, &bFalse, sizeof(CK_BBOOL)},
		{CKA_PRIVATE, &bTrue, sizeof(CK_BBOOL)},
		{CKA_ENCRYPT, &bTrue, sizeof(CK_BBOOL)},
		{CKA_DECRYPT, &bTrue, sizeof(CK_BBOOL)},
		{CKA_VALUE_LEN, &ulLen, sizeof(CK_ULONG)}, 
	};
	CK_ULONG ulCount = 7;
	CK_RV rv =  m_p11->C_GenerateKey(m_hSession, &mechanism, Destem, ulCount, &m_hKey); 
	_CheckRV("Generate DES key", rv);
}

void DesTest::crypt_Single()
{
	const CK_ULONG DATA_LENGTH = 1024*3;
	CK_BYTE bIn[DATA_LENGTH] = {0}, bTemp[DATA_LENGTH] = {0}, bOut[DATA_LENGTH] = {0};
	CK_ULONG ulIn = 0, ulOut = 0, ulTemp = 0;
	CK_ULONG Mechanism[3] = {CKM_DES_CBC, CKM_DES_ECB, CKM_DES_CBC_PAD};
	CK_BYTE_PTR bHint[3] = {
		(CK_BYTE_PTR)"CKM_DES_CBC: ",\
		(CK_BYTE_PTR)"CKM_DES_ECB: ",
		(CK_BYTE_PTR)"CKM_DES_CBC_PAD: "
	};

	for(int i = 0; i < 3; ++i)
	{
		ulIn = 1000;
		if(i == 2)
			ulIn = 1000;
		for(CK_ULONG i0 = 0; i0 < ulIn; ++i0)
			bIn[i0] = (CK_BYTE)i0;

		printf("\nDES: C_Encrypt()/C_Decrypt() %s\n", bHint[i]);

		//ecnrypt init:
		CK_BYTE iv[8] = {'u','s','b','t','o','k','e','n'};
		CK_MECHANISM ckMechanism = {Mechanism[i], iv, 8};

		CK_RV rv =  m_p11->C_EncryptInit(m_hSession, &ckMechanism, m_hKey);
		if(!_CheckRV("C_EncryptInit()", rv))
			break;
		rv =  m_p11->C_Encrypt(m_hSession, bIn, ulIn, NULL, &ulTemp);
		if(CKR_OK == rv)
			rv =  m_p11->C_Encrypt(m_hSession, bIn, ulIn, bTemp, &ulTemp);
		if(!_CheckRV("C_Encrypt()", rv))
			break;

		ShowData("Data to be encrypted: ", bIn, ulIn);
		ShowData("Data encrypted: ", bTemp, ulTemp);

		rv =  m_p11->C_DecryptInit(m_hSession, &ckMechanism, m_hKey);
		_CheckRV("C_DecryptInit()", rv);

		rv =  m_p11->C_Decrypt(m_hSession, bTemp, ulTemp, NULL, &ulOut);
		if(CKR_OK == rv)
			rv =  m_p11->C_Decrypt(m_hSession, bTemp, ulTemp, bOut, &ulOut);
		_CheckRV("C_Decrypt()", rv);

		ShowData("Data decrypted: ", bOut, ulOut);

		if(0 == memcmp(bIn, bOut, ulOut))
			_CheckRV("Check data", CKR_OK);
		else
			_CheckRV("Check data", CKR_FUNCTION_FAILED);
	}
}

void DesTest::crypt_Update()
{
	const CK_ULONG DATA_LENGTH = 1024*3;
	CK_BYTE bIn[DATA_LENGTH] = {0}, bTemp[DATA_LENGTH] = {0}, bOut[DATA_LENGTH] = {0};
	CK_ULONG ulIn = 0, ulOut = 0, ulTemp = 0;
	CK_ULONG Mechanism[3] = {CKM_DES_CBC, CKM_DES_ECB, CKM_DES_CBC_PAD};
	CK_BYTE_PTR bHint[3] = {
		(CK_BYTE_PTR)"CKM_DES_CBC: ",
		(CK_BYTE_PTR)"CKM_DES_ECB: ",
		(CK_BYTE_PTR)"CKM_DES_CBC_PAD: "
	};

	for(int i = 0; i < 3; ++i)
	{
		ulIn = 1000;
		if(i == 2)
		{//CKM_RC2_CBC_PAD
			ulIn = 1000;
		}
		for(CK_ULONG i0 = 0; i0 < ulIn; ++i0)
			bIn[i0] = (CK_BYTE)i0;

		printf("\nDES: C_EncryptUpdate()/C_DecryptUpdate(): %s\n", bHint[i]);

		//ecnrypt init:
		CK_BYTE iv[8] = {'u','s','b','t','o','k','e','n'};
		CK_MECHANISM ckMechanism = {Mechanism[i], iv, sizeof(iv)};

		CK_RV rv =  m_p11->C_EncryptInit(m_hSession, &ckMechanism, m_hKey); 
		if(!_CheckRV("C_EncryptInit()", rv))
			break;
		
		CK_ULONG ulEncrypted = 0;

		const CK_ULONG ulEnc1stPice = 33;
		rv =  m_p11->C_EncryptUpdate(m_hSession, bIn, ulEnc1stPice, NULL, &ulTemp);	//get buffer size.
		if(CKR_OK == rv)
			rv =  m_p11->C_EncryptUpdate(m_hSession, bIn, ulEnc1stPice, bTemp, &ulTemp);
		if(!_CheckRV("C_EncryptUpdate(1)", rv))
			break;

		ulEncrypted+=ulTemp;
		ulTemp = 0;

		//encrypt:
		rv =  m_p11->C_EncryptUpdate(m_hSession,  &(bIn[ulEnc1stPice]), ulIn-ulEnc1stPice, NULL, &ulTemp);
		if(CKR_OK == rv)
			rv =  m_p11->C_EncryptUpdate(m_hSession, &(bIn[ulEnc1stPice]), ulIn-ulEnc1stPice, &(bTemp[ulEncrypted]), &ulTemp);
		if(!_CheckRV("C_EncryptUpdate(2)", rv))
			break;

		ulEncrypted+=ulTemp;
		ulTemp = DATA_LENGTH - ulEncrypted;

		rv = m_p11->C_EncryptFinal(m_hSession, &(bTemp[ulEncrypted]), &ulTemp);
		if(!_CheckRV("C_EncryptFinal()", rv))
			break;

		ulEncrypted+=ulTemp;
		ulTemp = 0;

		ShowData("Data to be encrypted: ", bIn, ulIn);
		ShowData("Data encrypted: ", bTemp, ulEncrypted);

		rv =  m_p11->C_DecryptInit(m_hSession, &ckMechanism, m_hKey);
		if(!_CheckRV("C_DecryptInit()", rv))
			break;

		//Get buffer size:
		CK_ULONG ulDecrypt = 0;
		const CK_ULONG ulDec1stPice = 11;
		rv =  m_p11->C_DecryptUpdate(m_hSession, bTemp, ulDec1stPice, NULL, &ulOut);
		if(CKR_OK == rv)
			rv =  m_p11->C_DecryptUpdate(m_hSession, bTemp, ulDec1stPice, bOut, &ulOut);
		if(!_CheckRV("C_DecryptUpdate(1)", rv))
			break;

		ulDecrypt +=ulOut;
		ulOut = 0;

		//Get decrypted data:
		rv =  m_p11->C_DecryptUpdate(m_hSession, &(bTemp[ulDec1stPice]), ulEncrypted-ulDec1stPice, NULL, &ulOut);
		if(CKR_OK == rv)
			rv =  m_p11->C_DecryptUpdate(m_hSession, &(bTemp[ulDec1stPice]), ulEncrypted-ulDec1stPice, &(bOut[ulDecrypt]), &ulOut);
		if(!_CheckRV("C_DecryptUpdate(2)", rv))
			break;

		ulDecrypt +=ulOut;
		ulOut = DATA_LENGTH - ulDecrypt;

		rv = m_p11->C_DecryptFinal(m_hSession, &(bOut[ulDecrypt]), &ulOut);
		if(!_CheckRV("C_DecryptFinal()", rv))
			break;

		ulDecrypt +=ulOut;

		ShowData("Data decrypted: ", bOut, ulDecrypt);
		
		if(0 == memcmp(bIn, bOut, ulDecrypt))
			_CheckRV("Check data", CKR_OK);
		else
			_CheckRV("Check data", CKR_FUNCTION_FAILED);
	}
}
