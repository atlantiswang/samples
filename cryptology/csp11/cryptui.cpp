// CryptUI.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "Cryptuiapi.h"
#pragma comment (lib,"Cryptui.lib")
#pragma comment (lib, "Crypt32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	HCERTSTORE       hCertStore = NULL;        
	PCCERT_CONTEXT   pCertContext = NULL;      
	TCHAR * pszStoreName = TEXT("MY");

	//--------------------------------------------------------------------
	//   Open a certificate store.
	if ( hCertStore = CertOpenSystemStore(
		NULL,
		pszStoreName))
	{
		fprintf(stderr,"The store has been opened.\n");
	}
	else
	{
		printf("Unable to open store.\n");
		goto EXIT_POINT;
	}
	//--------------------------------------------------------------------
	//  Display a list of the certificates in the store and 
	//  allow the user to select a certificate. 
	if(!(pCertContext = CryptUIDlgSelectCertificateFromStore(
		hCertStore,      // Open the store that contains the certificates to
		// display
		NULL,
		NULL,
		NULL,
		CRYPTUI_SELECT_LOCATION_COLUMN,
		0,
		NULL)))
	{
		printf("Select Certificate UI failed.\n" );
		goto EXIT_POINT;
	}
	BOOL temp;
	CRYPTUI_VIEWCERTIFICATE_STRUCT cuivc;
	memset(&cuivc, 0, sizeof(cuivc));
	cuivc.dwSize = sizeof(cuivc);  
	cuivc.hwndParent = NULL;  
	cuivc.dwFlags = CRYPTUI_DISABLE_ADDTOSTORE;  
	cuivc.pCertContext = pCertContext;  
	cuivc.szTitle = "hello";
	CryptUIDlgViewCertificate(&cuivc, &temp);

EXIT_POINT:
	if(pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
	}

	if(hCertStore)
	{
		if (!CertCloseStore(hCertStore,0))
		{
			printf("CertCloseStore failed.\n" );
			exit(1);
		}
	}
	////////////////////////////////////////
	puts("test success");
	getchar();
	return 0;
}

