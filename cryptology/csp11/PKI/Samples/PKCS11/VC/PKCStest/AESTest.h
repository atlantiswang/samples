#ifndef _AES_H_
#define _AES_H_

#include "BaseAll.h"
class AESTest : public CP11TestBase  
{
public:
	AESTest(char* dll_file_path);
	virtual ~AESTest();
	void Test(void);
private:
	void GenerateKey(void);
	void crypt_Single(void);
	void crypt_Update(void);
	
private:
	CK_OBJECT_HANDLE m_hKey;

};
#endif