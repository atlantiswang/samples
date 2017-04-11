#ifndef _RC4_H_
#define _RC4_H_

#include "BaseAll.h"

class RC4Test : public CP11TestBase  
{
public:
	void Test(void);
	RC4Test(char* dll_file_path);
	virtual ~RC4Test();

private:
	void GenerateKey(void);
	void crypt_single(void);
	void crypt_Update(void);
private:
	CK_OBJECT_HANDLE m_hKey;
};

#endif // _RC4_H_
