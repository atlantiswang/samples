
#ifndef __GENERIC_H__
#define __GENERIC_H__

#include <string>
using namespace std;

#define CONTAINER "CSPKeyTest"

//RETURN VALUE:
#define CSP_FUNC_FAILED		1
#define CSP_OK				0

//PARAM:
#define NO_HASH				0
#define LAST_DATA			TRUE

void ShowData(unsigned char * pData, unsigned long ulDataLen);

void BeginAction(const string& strOperation);
void ActionFailed(DWORD dwLastError);
void ActionSuccess(void);

void GetProvParam(void);

class HCRYPTPROV_Holder
{
public:
	HCRYPTPROV_Holder(HCRYPTPROV hProv) : m_hProv(hProv)
	{
	}

	~HCRYPTPROV_Holder()
	{
		if(NULL != m_hProv)
		{
			BeginAction("CryptReleaseContext()");
			if(!CryptReleaseContext(m_hProv, 0))
			{
				ActionFailed(GetLastError());
			}
			else
			{
				ActionSuccess();
			}
		}
	}

protected:
	HCRYPTPROV m_hProv;
};

#endif // __GENERIC_H__
