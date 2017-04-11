// HMACTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HMACTest.h"

HmacTest::HmacTest() :
	pSlotList(NULL_PTR)
{
}

HmacTest::~HmacTest()
{	
	if(NULL_PTR != pSlotList)
	{
		delete[] pSlotList;
		pSlotList = NULL_PTR;
	}
	CK_RV rv = CKR_OK;
	if(m_hSession)
	{
		rv = C_CloseSession(m_hSession);
	}
	if(CKR_OK != rv)
	{
		cout << "....C_CloseSession failed! Return Error Code=0x" << hex << rv << endl;
	}
	rv = C_Finalize(0);
	if(CKR_OK != rv)
	{
		cout << "....C_Finalize failed! Return Error Code=0x" << hex << rv << endl;
	}
}

CK_RV HmacTest::Init()
{
	CK_RV rv = C_Initialize(NULL_PTR);
	if(CKR_OK != rv)
	{
		cout << "....C_Initialize failed! Return Error Code=0x" << hex << rv << endl;
		return rv;
	}
	cout << "Get the slots information..." << endl;
	CK_ULONG ulCount = 0;
	rv = C_GetSlotList(TRUE, NULL_PTR, &ulCount);
	if(CKR_OK != rv)
	{
		cout << "....C_GetSlotList failed! Return Error Code=0x" << hex << rv << endl;
		return rv;
	}
	if(ulCount <= 0)
	{
		cout << "....No slot with token attached." << endl;
		return rv;
	}
	cout << "Allocate memory for slots..." << endl;
	pSlotList = (CK_SLOT_ID_PTR)new CK_SLOT_ID[ulCount];
	if(!pSlotList)
	{
		cout << "....No slots!" << endl;
		return rv;
	}
	else
	{
		cout << "Get " << ulCount << " slot attached to USB port!" << endl;
	}
	cout << "Get the slots information." << endl;
	rv = C_GetSlotList(TRUE, pSlotList, &ulCount);
	if(CKR_OK != rv)
	{
		cout << "....C_GetSLotList failed! Return Error Code=0x" << hex << rv << endl;
		return rv;
	}
	unsigned char ucPin[32] = {0};
	cout << "Open a session to communicate with the UsbToken..." << endl;
	rv = C_OpenSession(pSlotList[0],
		CKF_RW_SESSION | CKF_SERIAL_SESSION,
		NULL_PTR, NULL_PTR, &m_hSession);
	if(CKR_OK != rv)
	{
		cout << "....C_OpenSession failed! Return Error Code=0x" << hex << rv << endl;
		return rv;
	}
	
	CK_TOKEN_INFO tokenInfo = {0};
	rv = C_GetTokenInfo(pSlotList[0], &tokenInfo);
	if (CKR_OK != rv)
	{
		cout << "....Can not get token info! Return Error Code=0x" <<hex << rv << endl;
		return rv;
	}	
	cout << "Input user-pin to login first:" << endl;
	cin >> ucPin;
	rv = C_Login(m_hSession, CKU_USER, ucPin,	strlen((char *) ucPin)); 	
	if(rv != CKR_OK)
	{
		cout << "....C_Login failed! Return Error Code=0x" << hex << rv << endl;
		return rv;
	} 
	cout << "...C_Login OK!" << endl; 
	return rv;
}

void HmacTest::Test()
{
	CK_RV rv = CKR_OK;
	if (CKR_OK != Init())
	{
		return;
	}
	do{
		cout<<"Generate generic secret key to test..."<<endl;
		CK_OBJECT_CLASS oClass = CKO_SECRET_KEY;
		CK_KEY_TYPE keyType = CKK_GENERIC_SECRET; 
		CK_BBOOL bTrue = true;
		CK_BBOOL bFalse = false;
		CK_ULONG ulLen = 64;
		CK_MECHANISM mechanism = {CKM_GENERIC_SECRET_KEY_GEN, NULL_PTR, 0};
		CK_ATTRIBUTE Generictem[] = {
			{CKA_CLASS, &oClass, sizeof(CK_OBJECT_CLASS)},
			{CKA_KEY_TYPE, &keyType, sizeof(CK_KEY_TYPE)},
			{CKA_TOKEN, &bFalse, sizeof(CK_BBOOL)},
			{CKA_PRIVATE, &bTrue, sizeof(CK_BBOOL)},
			{CKA_ENCRYPT, &bTrue, sizeof(CK_BBOOL)},
			{CKA_DECRYPT, &bTrue, sizeof(CK_BBOOL)},
			{CKA_VALUE_LEN, &ulLen, sizeof(CK_ULONG)},
		};
		CK_ULONG ulCount = sizeof(Generictem)/sizeof(CK_ATTRIBUTE);
		cout<<"generate generic secret key";
		rv = C_GenerateKey(m_hSession, &mechanism, Generictem, ulCount, &m_hKey); 
		CHECK_OP(rv)
	}while(0);

	CK_MECHANISM ckMechanism = {CKM_SHA_1_HMAC, NULL_PTR, 0};
	CK_BYTE pbMsg[] = "hmac-sha1 test...";
	CK_ULONG ulMsgLen = lstrlen((char *)pbMsg);
	CK_BYTE bSignatureBuffer[128] = {0};
	CK_ULONG ulSignatureLen = 0;
	cout<<"C_SignInit";
	rv = C_SignInit(m_hSession, &ckMechanism, m_hKey);
	CHECK_OP(rv)		
	cout<<"C_Sign[get buffer's size]";
	rv = C_Sign(m_hSession, pbMsg, ulMsgLen, NULL, &ulSignatureLen);
	CHECK_OP(rv)
	cout<<"Data Sign";
	rv = C_Sign(m_hSession, pbMsg, ulMsgLen, bSignatureBuffer, &ulSignatureLen);
	CHECK_OP(rv)

	cout<<"C_VerifyInit";
	rv = C_VerifyInit(m_hSession, &ckMechanism, m_hKey);
	CHECK_OP(rv)
	cout<<"Data Verify";
	rv = C_Verify(m_hSession, pbMsg, ulMsgLen, bSignatureBuffer, ulSignatureLen);
	CHECK_OP(rv)
}
