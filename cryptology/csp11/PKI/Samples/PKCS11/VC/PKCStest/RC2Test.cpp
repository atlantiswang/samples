
#include "common.h"
#include "RC2Test.h"

RC2Test::RC2Test(char* dll_file_path):CP11TestBase(dll_file_path)
{
	m_hKey = 0;
}
RC2Test::~RC2Test()
{
}
void RC2Test::Test()
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

void RC2Test::GenerateKey()
{
	CK_OBJECT_CLASS oClass = CKO_SECRET_KEY;
	CK_KEY_TYPE keyType = CKK_RC2; 
	CK_BBOOL bTrue = true;
	CK_BBOOL bFalse = false;
	CK_ULONG ulLen = 16;//bytes:1~128
	CK_MECHANISM mechanism = {CKM_RC2_KEY_GEN, NULL_PTR, 0};
	CK_ATTRIBUTE rc2tem[] = {
		{CKA_CLASS, &oClass, sizeof(CK_OBJECT_CLASS)},
		{CKA_KEY_TYPE, &keyType, sizeof(CK_KEY_TYPE)},
		{CKA_TOKEN, &bFalse, sizeof(CK_BBOOL)},
		{CKA_PRIVATE, &bTrue, sizeof(CK_BBOOL)},
		{CKA_ENCRYPT, &bTrue, sizeof(CK_BBOOL)},
		{CKA_DECRYPT, &bTrue, sizeof(CK_BBOOL)},
		{CKA_VALUE_LEN, &ulLen, sizeof(CK_ULONG)}, 
	};
	CK_ULONG ulCount = 7;
	CK_RV rv =  m_p11->C_GenerateKey(m_hSession, &mechanism, rc2tem, ulCount, &m_hKey); 
	_CheckRV("Generate RC2 key", rv);
}

void RC2Test::crypt_Single()
{
	const CK_ULONG DATA_LENGTH = 1024;
	CK_BYTE bIn[DATA_LENGTH] = {0}, bTemp[DATA_LENGTH] = {0}, bOut[DATA_LENGTH] = {0};
	CK_ULONG ulIn = 0, ulOut = 0, ulTemp = 0;
	CK_ULONG Mechanism[3] = {CKM_RC2_CBC, CKM_RC2_ECB, CKM_RC2_CBC_PAD};
	CK_BYTE_PTR bHint[3] = {
		(CK_BYTE_PTR)"CKM_RC2_CBC: ",
		(CK_BYTE_PTR)"CKM_RC2_ECB: ",
		(CK_BYTE_PTR)"CKM_RC2_CBC_PAD: "
	};

	for(int i = 0; i < 3; ++i)
	{
		ulIn = 256;
		if(i==2)
			ulIn = 337;
		for(register CK_ULONG i0 = 0;i0<ulIn;i0++)
			bIn[i0] = (CK_BYTE)i0;
		
		
		printf("\nRC2: C_Encrypt()/C_Decrypt(): %s\n", bHint[i]);

		//ecnrypt init:
		CK_BYTE iv[8] = {'u','s','b','t','o','k','e','n'};
		CK_RC2_CBC_PARAMS Param;
		memcpy(Param.iv, iv, sizeof(iv));
		Param.ulEffectiveBits = 16*8;
		CK_MECHANISM ckMechanism = {Mechanism[i], &Param, sizeof(CK_RC2_CBC_PARAMS)};

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
		if(!_CheckRV("C_DecryptInit()", rv))
			break;

		rv =  m_p11->C_Decrypt(m_hSession, bTemp, ulTemp, NULL, &ulOut);
		if(CKR_OK == rv)
			rv =  m_p11->C_Decrypt(m_hSession, bTemp, ulTemp, bOut, &ulOut);
		if(!_CheckRV("C_Decrypt()", rv))
			break;

		ShowData("Data decrypted: ", bOut, ulOut);

		if(0 == memcmp(bIn, bOut, ulOut))
			_CheckRV("Check data", CKR_OK);
		else
			_CheckRV("Check data", CKR_FUNCTION_FAILED);
	}
}

void RC2Test::crypt_Update()
{
	const CK_ULONG DATA_LENGTH = 1024;
	CK_BYTE bIn[DATA_LENGTH] = {0}, bTemp[DATA_LENGTH] = {0}, bOut[DATA_LENGTH] = {0};
	CK_ULONG ulIn = 0, ulOut = 0, ulTemp = 0;
	CK_ULONG Mechanism[3] = {CKM_RC2_CBC, CKM_RC2_ECB, CKM_RC2_CBC_PAD};
	CK_BYTE_PTR bHint[3] = {
		(CK_BYTE_PTR)"CKM_RC2_CBC: ",
		(CK_BYTE_PTR)"CKM_RC2_ECB: ",
		(CK_BYTE_PTR)"CKM_RC2_CBC_PAD: "
	};

	for(int i = 0; i < 3; ++i)
	{
		ulIn = 256;
		if(i == 2)
		{//CKM_RC2_CBC_PAD
			ulIn = 253;
		}

		for(CK_ULONG i0 = 0; i0 < ulIn; ++i0)
			bIn[i0] = (CK_BYTE)i0;

		printf("\nRC2: C_EncryptUpdate()/C_DecryptUpdate(): %s\n", bHint[i]);

		//ecnrypt init:
		CK_BYTE iv[8] = {'u','s','b','t','o','k','e','n'};
		CK_RC2_CBC_PARAMS Param;
		memcpy(Param.iv, iv, sizeof(iv));
		Param.ulEffectiveBits = 16*8;
		CK_MECHANISM ckMechanism = {Mechanism[i], &Param, sizeof(CK_RC2_CBC_PARAMS)};

		CK_RV rv =  m_p11->C_EncryptInit(m_hSession, &ckMechanism, m_hKey); 
		if(!_CheckRV("C_EncryptInit()", rv))
			break;
		
		CK_ULONG ulEncrypted = 0;
		const CK_ULONG ulEnc1stPice = 33;

		rv = m_p11->C_EncryptUpdate(m_hSession, bIn, ulEnc1stPice, NULL, &ulTemp);
		if(CKR_OK == rv)
			rv = m_p11->C_EncryptUpdate(m_hSession, bIn, ulEnc1stPice, bTemp, &ulTemp);

		if(!_CheckRV("C_EncryptUpdate(1)", rv))
			break;

		ulEncrypted+=ulTemp;
		ulTemp = 0;

		rv = m_p11->C_EncryptUpdate(m_hSession,  &(bIn[ulEnc1stPice]), ulIn-ulEnc1stPice, NULL, &ulTemp);
		if(CKR_OK == rv)
			rv = m_p11->C_EncryptUpdate(m_hSession, &(bIn[ulEnc1stPice]), ulIn-ulEnc1stPice, &(bTemp[ulEncrypted]), &ulTemp);
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
		ulOut = DATA_LENGTH-ulDecrypt;

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
