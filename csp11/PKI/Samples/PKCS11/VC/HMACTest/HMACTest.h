#ifndef _HMACTEST_H_
#define _HMACTEST_H_

#define CHECK_OP(rvRet)														\
{																			\
	if(CKR_OK == (rvRet))													\
	{																		\
		cout<<"....[OK]."<<endl;											\
	}																		\
	else																	\
	{																		\
		cout<<"....[FAILED] Return Error Code = 0x" << hex << rvRet <<endl;	\
		return;																\
	}																		\
}

class HmacTest
{
public:
	HmacTest();
	~HmacTest();
	void Test();

private:
	CK_RV Init();
	
private:
	CK_SESSION_HANDLE m_hSession;
	CK_OBJECT_HANDLE m_hKey;
	CK_SLOT_ID_PTR pSlotList;
};

#endif //_HMACTEST_H_