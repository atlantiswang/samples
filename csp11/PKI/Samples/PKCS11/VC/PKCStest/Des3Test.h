#ifndef _DES3TEST_H_
#define _DES3TEST_H_

#include "BaseAll.h"

class Des3Test : public CP11TestBase  
{
public:
	Des3Test(char* dll_file_path);
	virtual ~Des3Test();
	void Test(void);
private:
	void GenerateKey(void);
	void crypt_Single(void);
	void crypt_Update(void);
	
private:
	CK_OBJECT_HANDLE m_hKey;
};

#endif //_DES3TEST_H_
