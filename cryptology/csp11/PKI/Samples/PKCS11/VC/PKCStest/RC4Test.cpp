
#include "common.h"
#include "RC4Test.h"

RC4Test::RC4Test(char* dll_file_path):CP11TestBase(dll_file_path)
{
	m_hKey = 0;
}

RC4Test::~RC4Test()
{
	m_hKey = 0;
}

void RC4Test::Test()
{
	if(CKR_OK != Initialize())
		return;
	
	GenerateKey();
	if(m_hKey == 0)
	{
		Finalize();
		return ;
	}
	crypt_single();
	crypt_Update();
	Finalize();
}

void RC4Test::GenerateKey()
{
	CK_OBJECT_CLASS oClass = CKO_SECRET_KEY;
	CK_KEY_TYPE keyType = CKK_RC4; 
	CK_BBOOL bTrue = true;
	CK_BBOOL bFalse = false;
	CK_ULONG ulLen = 16;
	CK_ATTRIBUTE rc4tem[] = {
		{CKA_CLASS, &oClass, sizeof(CK_OBJECT_CLASS)},
		{CKA_KEY_TYPE, &keyType, sizeof(CK_KEY_TYPE)},
		{CKA_TOKEN, &bFalse, sizeof(CK_BBOOL)},
		{CKA_PRIVATE, &bTrue, sizeof(CK_BBOOL)},
		{CKA_ENCRYPT, &bTrue, sizeof(CK_BBOOL)},
		{CKA_DECRYPT, &bTrue, sizeof(CK_BBOOL)},
		{CKA_VALUE_LEN, &ulLen, sizeof(CK_ULONG)}, 
	};
	CK_ULONG ulCount = 7;
	CK_MECHANISM mechanism = {CKM_RC4_KEY_GEN, NULL, 0};

	CK_RV rv =  m_p11->C_GenerateKey(m_hSession, &mechanism, rc4tem, ulCount, &m_hKey); 
	_CheckRV("Generate RC4 key", rv);
}

void RC4Test::crypt_single()
{
	const CK_ULONG DATA_LENGTH = 1024;
	CK_BYTE bIn[DATA_LENGTH] = {0}, bTemp[DATA_LENGTH] = {0}, bOut[DATA_LENGTH] = {0};
	CK_ULONG ulIn = 0, ulOut = 0, ulTemp = 0;
	CK_ULONG Mechanism = {CKM_RC4};
	CK_BYTE_PTR bHint[] = {(CK_BYTE_PTR)"CKM_RC4: "};

	printf("\nRC4: C_Encrypt()/C_Decrypt(): %s\n", bHint[0]);

	ulIn = 256;
	for(CK_ULONG i0 = 0;i0<ulIn;i0++)
		bIn[i0] = (CK_BYTE)i0;

	//ecnrypt init:
	CK_MECHANISM ckMechanism = {Mechanism, NULL, 0};
	CK_RV rv =  m_p11->C_EncryptInit(m_hSession, &ckMechanism, m_hKey); 
	if(!_CheckRV("C_EncryptInit()", rv))
		return;
	
	ulTemp = 0;
	rv =  m_p11->C_Encrypt(m_hSession, bIn, ulIn, NULL, &ulTemp);
	if(CKR_OK == rv)
		rv =  m_p11->C_Encrypt(m_hSession, bIn, ulIn, bTemp, &ulTemp);
	if(!_CheckRV("C_Encrypt()", rv))
		return;

	ShowData("Data to be encrypted: ", bIn, ulIn);
	ShowData("Data encrypted: ", bTemp, ulTemp);

	rv =  m_p11->C_DecryptInit(m_hSession, &ckMechanism, m_hKey);
	if(!_CheckRV("C_DecryptInit()", rv))
		return;

	ulOut = 0;
	rv =  m_p11->C_Decrypt(m_hSession, bTemp, ulTemp, NULL, &ulOut);
	if(CKR_OK == rv)
		rv =  m_p11->C_Decrypt(m_hSession, bTemp, ulTemp, bOut, &ulOut);
	if(!_CheckRV("C_Decrypt()", rv))
		return;

	ShowData("Data decrypted: ", bOut, ulOut);
	
	if(0 == memcmp(bIn, bOut, ulOut))
		_CheckRV("Check data", CKR_OK);
	else
		_CheckRV("Check data", CKR_FUNCTION_FAILED);
}

void RC4Test::crypt_Update()
{
	const CK_ULONG DATA_LENGTH = 1024;
	CK_BYTE bIn[DATA_LENGTH] = {0}, bTemp[DATA_LENGTH] = {0}, bOut[DATA_LENGTH] = {0};
	CK_ULONG ulIn = 0, ulOut = 0, ulTemp = 0;
	CK_BYTE_PTR bHint[] = {(CK_BYTE_PTR)"CKM_RC4 "};

	printf("\nRC4: C_EncryptUpdate()/C_DecryptUpdate(): %s\n", bHint[0]);

	ulIn = 257;
	for(register CK_ULONG i0 = 0;i0<ulIn;i0++)
		bIn[i0] = (CK_BYTE)i0;

	//ecnrypt init:
	CK_MECHANISM ckMechanism = {CKM_RC4, NULL, 0};

	CK_RV rv =  m_p11->C_EncryptInit(m_hSession, &ckMechanism, m_hKey); 
	if(!_CheckRV("C_EncryptInit()", rv))
		return;
		
	CK_ULONG ulEncrypted = 0;

	const CK_ULONG ulEnc1stPice = 33;
	rv =  m_p11->C_EncryptUpdate(m_hSession, bIn, ulEnc1stPice, NULL, &ulTemp);
	if(CKR_OK == rv)
		rv =  m_p11->C_EncryptUpdate(m_hSession, bIn, ulEnc1stPice, bTemp, &ulTemp);
	if(!_CheckRV("C_EncryptUpdate(1)", rv))
		return;

	ulEncrypted+=ulTemp;
	ulTemp = 0;

	rv =  m_p11->C_EncryptUpdate(m_hSession, bIn, ulIn-ulEnc1stPice, NULL, &ulTemp);
	if(CKR_OK == rv)
		rv =  m_p11->C_EncryptUpdate(m_hSession, &(bIn[ulEnc1stPice]), ulIn-ulEnc1stPice, &(bTemp[ulEncrypted]), &ulTemp);
	if(!_CheckRV("C_EncryptUpdate(2)", rv))
		return;

	ulEncrypted+=ulTemp;
	ulTemp = DATA_LENGTH - ulEncrypted;

	rv = m_p11->C_EncryptFinal(m_hSession, &(bTemp[ulEncrypted]), &ulTemp);
	if(!_CheckRV("C_EncryptFinal()", rv))
		return;

	ulEncrypted+=ulTemp;
	ulTemp = 0;

	ShowData("Data to be encrypted: ", bIn, ulIn);
	ShowData("Data encrypted: ", bTemp, ulEncrypted);

	rv =  m_p11->C_DecryptInit(m_hSession, &ckMechanism, m_hKey);
	if(!_CheckRV("C_DecryptInit()", rv))
		return;

	CK_ULONG ulDecrypt = 0;
	const CK_ULONG ulDec1stPice = 11;
	rv =  m_p11->C_DecryptUpdate(m_hSession, bTemp, ulDec1stPice, NULL, &ulOut);
	if(CKR_OK == rv)
		rv =  m_p11->C_DecryptUpdate(m_hSession, bTemp, ulDec1stPice, bOut, &ulOut);
	if(!_CheckRV("C_DecryptUpdate(1)", rv))
		return;

	ulDecrypt +=ulOut;
	ulOut = 0;
	rv =  m_p11->C_DecryptUpdate(m_hSession, bTemp, ulEncrypted-ulDec1stPice, NULL, &ulOut);
	if(CKR_OK == rv)
		rv =  m_p11->C_DecryptUpdate(m_hSession, &(bTemp[ulDec1stPice]), ulEncrypted-ulDec1stPice, &(bOut[ulDecrypt]), &ulOut);
	if(!_CheckRV("C_DecryptUpdate(2)", rv))
		return;

	ulDecrypt +=ulOut;
	ulOut = DATA_LENGTH - ulDecrypt;
	rv = m_p11->C_DecryptFinal(m_hSession, &(bOut[ulDecrypt]), &ulOut);
	if(!_CheckRV("C_DecryptFinal()", rv))
		return;

	ulDecrypt += ulOut;

	ShowData("Data decrypted: ", bOut, ulDecrypt);
	
	if(0 == memcmp(bIn, bOut, ulDecrypt))
		_CheckRV("Check data", CKR_OK);
	else
		_CheckRV("Check data", CKR_FUNCTION_FAILED);
}
