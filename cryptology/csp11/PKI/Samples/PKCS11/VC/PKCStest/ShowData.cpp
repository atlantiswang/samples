#include "common.h"

void ShowData(const char* pszMsg, unsigned char *pData, unsigned long ulDataLen)
{
	if(pData == NULL)
	{
		printf("%s: Nothing to show.\n", pszMsg);
		return ;
	}

	printf("%s (%d byte%s).\n", pszMsg, ulDataLen, ulDataLen > 1 ? "s" : "");

#if SHOW_DATA_BIN
	for(unsigned long i = 0; i < ulDataLen; ++i)
	{
		if(0 != i && 0 == i % 16)
		{
			printf("\n");
		}
		printf("%02X ", pData[i]);
	}
	printf("\n");
#endif
}