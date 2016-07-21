// CSP_cert.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <WinCrypt.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HCERTSTORE hStore = NULL;
	if (!(hStore = CertOpenSystemStore(NULL, _T("MY"))))
	{
		printf("CertOpenSystemStore failed %d\n", GetLastError());
		goto EndError;
	}
	PCCERT_CONTEXT pCertContext = NULL;

	do 
	{
		union{
		CRYPT_KEY_PROV_INFO keyProvInfo;
		BYTE byteBuff[1024];
		};
		DWORD dwLen = 1024;
		pCertContext = CertEnumCertificatesInStore(hStore, pCertContext);

		if(!pCertContext)
		{
			puts("Cert over");
			goto EndError;
		}
		if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, &keyProvInfo, &dwLen))
		{
			printf("CertGetCertificateContextProperty failed %X\n", GetLastError());
			continue;
		}
		wprintf(_T("%s\r\n%s\r\n\r\n"), keyProvInfo.pwszContainerName, keyProvInfo.pwszProvName);
	} while (pCertContext);
	//////////////////////////////////////////////////////////////////////////
EndError:
	if (pCertContext) CertFreeCertificateContext(pCertContext);
	if (hStore) CertCloseStore(hStore, 0);
	return 0;
}

