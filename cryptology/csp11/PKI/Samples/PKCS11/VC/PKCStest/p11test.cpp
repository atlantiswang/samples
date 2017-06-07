
#include "Common.h"
#include "RSATest.h"
#include "RC2Test.h"
#include "RC4Test.h"
#include "DesTest.h"
#include "Des3Test.h"
#include "AESTest.h"
#define  PKCS11_LIB_NAME "eps2003csp11.dll"

void ShowTitle(void)
{
	printf("[]==================================================[]\n");
	printf(" |             USB Token PKCS#11 Demo               |\n");				
	printf("[]==================================================[]\n");
}

int main(int argc, char* argv[])
{
	//char* strTestItem = NULL;
	int iTestItem = 0xFF;
	ShowTitle();

	bool bRunOneTime = false;
	for(;;)
	{
		if(1 == argc)
		{
			printf("\n\n\n");
			printf("===============================================\n\n");
			printf("1: DES   2: DES3   3: RC2   4:RC4   5:RSA   6:AES\n");
			printf("0: Exit\n");
			printf("-----------------------------------------------\n");
			printf("Please select a item to test: ");
			scanf("%d", &iTestItem);
		}
		else
		{
			bRunOneTime = true;
			if(0==lstrcmpi(argv[1], "-DES"))
				iTestItem = 1;
			else if(0==lstrcmpi(argv[1], "-DES3"))
				iTestItem = 2;
			else if(0==lstrcmpi(argv[1], "-RC2"))
				iTestItem = 3;
			else if(0==lstrcmpi(argv[1], "-RC4"))
				iTestItem = 4;
			else if(0==lstrcmpi(argv[1], "-RSA"))
				iTestItem = 5;
			else 
				iTestItem = 0;
		}

		switch(iTestItem)
		{
		case 1:
			{
				DesTest test(PKCS11_LIB_NAME);
				test.Test();
			}
			break;
		case 2:
			{
				Des3Test test(PKCS11_LIB_NAME);	
				test.Test();
			}
			break;
		case 3:
			{
				RC2Test test(PKCS11_LIB_NAME);
				test.Test();
			}
			break;
		case 4:
			{
				RC4Test test(PKCS11_LIB_NAME);
				test.Test();
			}
			break;
		case 5:
			{
				RSATest rsa(PKCS11_LIB_NAME);
				rsa.Test();
			}
			break;
		case 6:
			{
				AESTest test(PKCS11_LIB_NAME);
				test.Test();
			}
		break;
		case 0:
			return 0;
		default:
			break;
		}

		if(bRunOneTime)
			break;
	}

	printf("\n\nTest finished.\n\nPress any key to exit ...\n");
	getch();
	return 0;
}



