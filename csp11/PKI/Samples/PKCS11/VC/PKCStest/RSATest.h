#ifndef _RSA_H_
#define _RSA_H_

#include "BaseAll.h"

class RSATest : public CP11TestBase 
{
public:
	RSATest(char* dll_file_path);
	virtual ~RSATest();
	void Test(void);

protected:
	void RsaKeyGenerationTest(void);
};

#endif 
