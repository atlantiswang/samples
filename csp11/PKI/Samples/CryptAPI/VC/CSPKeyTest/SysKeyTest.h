
#ifndef _SYSKEYTEST_H_
#define _SYSKEYTEST_H_

#define TEST_RC2_ALG	 CALG_RC2
#define TEST_RC4_ALG	 CALG_RC4
#define TEST_DES_ALG	 CALG_DES
#define TEST_AES_ALG_128	 CALG_AES_128

class SysKeyTest  
{
public:
	SysKeyTest();
	virtual ~SysKeyTest();

	void TestKey(DWORD ulALG);
};

#endif // _SYSKEYTEST_H_
