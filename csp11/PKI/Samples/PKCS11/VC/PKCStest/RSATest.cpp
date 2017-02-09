
#include "common.h"
#include "RSATest.h"

RSATest::RSATest(char* dll_file_path):CP11TestBase(dll_file_path)
{
}

RSATest::~RSATest()
{
}

void RSATest::Test(void)
{
	if(CKR_OK != Initialize())
		return;

	RsaKeyGenerationTest();

	Finalize();
}

void RSATest::RsaKeyGenerationTest(void)
{
	CK_RV rv = CKR_OK;
	CK_BBOOL bTrue = TRUE;
	CK_ULONG ulModulusBits = MODULUS_BIT_LENGTH;
	CK_BYTE subject[] = "Sample RSA Key Pair";
	CK_ULONG keyType = CKK_RSA;

	CK_OBJECT_HANDLE hPubKey = NULL_PTR;
	CK_OBJECT_CLASS pubClass = CKO_PUBLIC_KEY;
	CK_ATTRIBUTE pubTemplate[] =
	{ 
		{CKA_CLASS,			&pubClass,		sizeof(pubClass)},
		{CKA_KEY_TYPE,		&keyType,		sizeof(keyType)},
		{CKA_SUBJECT,		subject,		sizeof(subject)},
		{CKA_MODULUS_BITS,	&ulModulusBits, sizeof(ulModulusBits)},
		{CKA_ENCRYPT,		&bTrue,			sizeof(bTrue)},
		{CKA_TOKEN,			&bTrue,			sizeof(bTrue)},
		{CKA_WRAP,			&bTrue,			sizeof(bTrue)},
	};	

	CK_OBJECT_HANDLE hPriKey	= NULL_PTR;
	CK_OBJECT_CLASS priClass	= CKO_PRIVATE_KEY;
	CK_ATTRIBUTE priTemplate[]	= {
		{CKA_CLASS,			&priClass,	sizeof(priClass)},
		{CKA_KEY_TYPE,		&keyType,	sizeof(keyType)},
		{CKA_SUBJECT,		subject,	sizeof(subject)},
		{CKA_DECRYPT,		&bTrue,		sizeof(bTrue)},
		{CKA_PRIVATE,		&bTrue,		sizeof(bTrue)},
		{CKA_SENSITIVE,		&bTrue,		sizeof(bTrue)},
		{CKA_TOKEN,			&bTrue,		sizeof(bTrue)},
		{CKA_EXTRACTABLE,	&bTrue,		sizeof(bTrue)},
		{CKA_UNWRAP,		&bTrue,		sizeof(bTrue)},
	};
    CK_MECHANISM keyGenMechanism = {CKM_RSA_PKCS_KEY_PAIR_GEN, NULL_PTR, 0};
	CK_MECHANISM ckMechanism = {CKM_RSA_PKCS, NULL_PTR, 0};
	CK_BYTE pbMsg[] = "UsbToken RunRsaKeyGenerationTest...";
	CK_ULONG ulMsgLen = lstrlen((char *)pbMsg);
	CK_BYTE bSignatureBuffer[MODULUS_BIT_LENGTH] = {0};
	CK_ULONG ulSignatureLen = 0;
	CK_BYTE_PTR pbCipherBuffer = NULL;
	CK_ULONG ulCipherLen = 0;
	CK_BYTE_PTR pbRestoredMsg = NULL;
	CK_ULONG ulRestoredMsgLen = 0;

	rv =  m_p11->C_GenerateKeyPair(m_hSession, &keyGenMechanism,
							   pubTemplate, countof(pubTemplate),
							   priTemplate, countof(priTemplate),
							   &hPubKey, &hPriKey);
	if(!_CheckRV("C_GenerateKeyPair()", rv))
		return;

    // Try Sign and Verify operations with the key pair.
	// Sign a message. 
	ShowData("The message to be signed is: ", pbMsg, ulMsgLen);

	ulSignatureLen = sizeof(bSignatureBuffer);

	rv =  m_p11->C_SignInit(m_hSession, &ckMechanism, hPriKey);
	if(!_CheckRV("C_SignInit()", rv))
		return;

	rv =  m_p11->C_Sign(m_hSession, pbMsg, ulMsgLen, bSignatureBuffer, &ulSignatureLen);
	if(!_CheckRV("C_Sign()", rv))
		return;

	ShowData("Signature is: ", bSignatureBuffer, ulSignatureLen);

	// Verify the previously signed message.
	rv =  m_p11->C_VerifyInit(m_hSession, &ckMechanism, hPubKey);
	if(!_CheckRV("C_VerifyInit()", rv))
		return;
		
	rv =  m_p11->C_Verify(m_hSession, pbMsg, ulMsgLen, bSignatureBuffer, ulSignatureLen);
	if(!_CheckRV("C_Verify()", rv))
		return;

	// Encrypt a message. 
	ShowData("Message to be encrypt is: ", pbMsg, ulMsgLen);

	rv =  m_p11->C_EncryptInit(m_hSession, &ckMechanism, hPubKey);
	if(!_CheckRV("C_EncryptInit()", rv))
		return;

	rv =  m_p11->C_Encrypt(m_hSession, pbMsg, ulMsgLen, NULL_PTR, &ulCipherLen);
	if(!_CheckRV("C_Encrypt(1)", rv))
		return;

	pbCipherBuffer = (CK_BYTE_PTR)malloc(ulCipherLen);
	if (! pbCipherBuffer)
	{
		_CheckRV("Allocate buffer for encrypted data", CKR_HOST_MEMORY);
		return;
	}

	memset(pbCipherBuffer, 0, ulCipherLen);
	rv =  m_p11->C_Encrypt(m_hSession, pbMsg, ulMsgLen, pbCipherBuffer, &ulCipherLen);
	if(!_CheckRV("C_Encrypt(2)", rv))
	{
		free(pbCipherBuffer);
		return;
	}

	ShowData("Data encrypted: ", pbCipherBuffer, ulCipherLen);

	rv =  m_p11->C_DecryptInit(m_hSession, &ckMechanism, hPriKey);
	if(!_CheckRV("C_DecryptInit()", rv))
	{
		free(pbCipherBuffer);
		return;
	}

	rv =  m_p11->C_Decrypt(m_hSession, pbCipherBuffer, ulCipherLen, NULL_PTR, &ulRestoredMsgLen);
	if(!_CheckRV("C_Decrypt(1)", rv))
	{
		free(pbCipherBuffer);
		return;
	}

	pbRestoredMsg = (CK_BYTE_PTR)malloc(ulRestoredMsgLen + 1);
	if (! pbRestoredMsg)
	{
		_CheckRV("Allocate buffer for decrypted data", CKR_HOST_MEMORY);
		free(pbCipherBuffer);
		return;
	}

	memset(pbRestoredMsg, 0, ulRestoredMsgLen + 1);
	
	rv =  m_p11->C_Decrypt(m_hSession, pbCipherBuffer, ulCipherLen, 
			pbRestoredMsg, &ulRestoredMsgLen);
	if(!_CheckRV("C_Decrypt(2)", rv))
	{
		free(pbCipherBuffer);
		free(pbRestoredMsg);
		return;
	}

	ShowData("The message decrypted is: ", pbRestoredMsg, ulRestoredMsgLen);

	if(0 == memcmp(pbMsg, pbRestoredMsg, ulRestoredMsgLen))
		_CheckRV("Check data", CKR_OK);
	else
		_CheckRV("Check data", CKR_FUNCTION_FAILED);

	free(pbCipherBuffer);
	free(pbRestoredMsg);

	// Remove the RSA key pair from the UsbToken.

	rv =  m_p11->C_DestroyObject(m_hSession, hPubKey);
	_CheckRV("C_DestroyObject(public key)", rv);

	rv =  m_p11->C_DestroyObject(m_hSession, hPriKey);
	_CheckRV("C_DestroyObject(private key)", rv);

	rv = m_p11->C_Logout(m_hSession);
	_CheckRV("C_Logout()", rv);

}
