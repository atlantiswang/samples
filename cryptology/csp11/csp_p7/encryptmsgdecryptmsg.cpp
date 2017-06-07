#include "stdafx.h"
#include "../CSP_sign_verify/fun.h"

bool 
MyEncryptMessage(const char* szData,
				 BYTE *szEncryptData, DWORD &dwEncryptData)
{
	PCCERT_CONTEXT pCertArray[1];
	pCertArray[0] = ImportCert(L"FEITIAN ePassNG RSA Cryptographic Service Provider", _T("签名加密"));//从证书存储区导入

	CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm = {0};
	EncryptAlgorithm.pszObjId = szOID_RSA_RC4;//一会再填。

	CRYPT_ENCRYPT_MESSAGE_PARA EncryptParam = {0};


	EncryptParam.cbSize = sizeof(EncryptParam);
	EncryptParam.dwMsgEncodingType = X509_ASN_ENCODING|PKCS_7_ASN_ENCODING;
	EncryptParam.hCryptProv = NULL;
	EncryptParam.ContentEncryptionAlgorithm = EncryptAlgorithm;

	if (!CryptEncryptMessage(
		&EncryptParam, 
		1, pCertArray,
		(const BYTE*)szData, strlen(szData)+1,
		(BYTE*)szEncryptData, &dwEncryptData))
		return false;

	return true;
}

bool
MyDecryptMessageStep(BYTE *szEnCryptData, DWORD dwEnCryptData)
{
	HCRYPTMSG hMsg = NULL;
	hMsg = CryptMsgOpenToDecode(
		X509_ASN_ENCODING|PKCS_7_ASN_ENCODING,
		CMSG_CRYPT_RELEASE_CONTEXT_FLAG, 0, NULL, NULL, NULL);
	if(!hMsg)
	{
		puts("CryptMsgOpenToDecode failed");
		return 0;
	}
	if (!CryptMsgUpdate(hMsg, (const BYTE*)szEnCryptData, dwEnCryptData, TRUE))
	{
		puts("CryptMsgUpdate failed");
		return 0;
	}
	// 	if(!CryptMsgGetParam())
	// 	{
	// 		puts("CryptMsgGetParam failed");
	// 		return 0;
	// 	}
	HCRYPTPROV hProv = NULL;
	if (!CryptAcquireContext(&hProv, _T("698D363C-1FF8-4AAE-872B-D7C428777B07"), 
		_T("FEITIAN ePassNG RSA Cryptographic Service Provider"),PROV_RSA_FULL, 0))
	{
		printf("CryptAcquireContext failed:%x\n", GetLastError());
		return 0;
	}
	CMSG_CTRL_DECRYPT_PARA dp = {sizeof(CMSG_CTRL_DECRYPT_PARA), hProv, AT_KEYEXCHANGE, 0};
	if(!CryptMsgControl(hMsg, CMSG_CRYPT_RELEASE_CONTEXT_FLAG, CMSG_CTRL_DECRYPT, &dp))
	{
		puts("CryptMsgCtrol failed");
		return 0;
	}
	if(!CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, 0,&dwEnCryptData))
	{
		puts("CryptMsgGetParam failed");
		return 0;
	}
	char szDeCryptData[128] = {0};
	if(!CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, szDeCryptData,&dwEnCryptData))
	{
		puts("CryptMsgGetParam failed");
		return 0;
	}
	printf("%s\n", szDeCryptData);

	return 1;
}

//////////////////////////////////////////////////////////////////////////
bool
MyEncryptMessageStep(const char* szData,
					 BYTE *szEncryptData, DWORD &dwEncryptData)
{
	PCCERT_CONTEXT pCertContext = ImportCert(L"FEITIAN ePassNG RSA Cryptographic Service Provider", _T("签名加密"));
	PCERT_INFO RecipCertArray[1];
	RecipCertArray[0] = pCertContext->pCertInfo;

	CRYPT_ALGORITHM_IDENTIFIER ContentEncryptAlgorithm = {0};
	ContentEncryptAlgorithm.pszObjId = szOID_RSA_RC4;

	CMSG_ENVELOPED_ENCODE_INFO EnvelopedEncodeInfo = {0};
	EnvelopedEncodeInfo.cbSize = sizeof(CMSG_ENVELOPED_ENCODE_INFO);
	EnvelopedEncodeInfo.ContentEncryptionAlgorithm = ContentEncryptAlgorithm;
	EnvelopedEncodeInfo.cRecipients = 1;
	EnvelopedEncodeInfo.hCryptProv = NULL;
	EnvelopedEncodeInfo.pvEncryptionAuxInfo = NULL;
	EnvelopedEncodeInfo.rgpRecipients = RecipCertArray;

	DWORD cbEncodedBlob;
	if (!(cbEncodedBlob = CryptMsgCalculateEncodedLength(
		PKCS_7_ASN_ENCODING|X509_ASN_ENCODING,
		0, CMSG_ENVELOPED,
		&EnvelopedEncodeInfo,
		NULL, strlen(szData)+1)))
	{
		printf("CryptMsgCalculateEncodedLength failed\n");
		return 0;
	}
	HCRYPTMSG hMsg = NULL;
	if(!(hMsg = CryptMsgOpenToEncode(
		PKCS_7_ASN_ENCODING|X509_ASN_ENCODING,
		0, CMSG_ENVELOPED, &EnvelopedEncodeInfo, NULL, NULL)))
	{
		printf("CryptMsgOpenToEncode failed\n");
		return 0;
	}
	if (!CryptMsgUpdate(hMsg, (const BYTE *)szData, strlen(szData)+1, TRUE))
	{
		printf("CryptMsgUpdate failed\n");
		return 0;
	}

	if (!CryptMsgGetParam(hMsg,
		CMSG_CONTENT_PARAM, 0, szEncryptData, &cbEncodedBlob))
	{
		printf("CryptMsgGetParam failed:%d\n",GetLastError());
		return 0;
	}
	CertFreeCertificateContext(pCertContext);
	if (hMsg)
		CryptMsgClose(hMsg);
	return 1;
}

bool
MyDecryptMessage(BYTE *szEnCryptData, DWORD dwEnCryptData)
{
	HCERTSTORE hCertStore = CertOpenSystemStore(NULL, _T("MY"));
	HCERTSTORE CertStoreArray[1] ={0};
	CertStoreArray[0] = hCertStore;

	CRYPT_DECRYPT_MESSAGE_PARA DecryptPara;
	memset(&DecryptPara, 0, sizeof(DecryptPara));
	DecryptPara.cbSize = sizeof(DecryptPara);
	DecryptPara.dwMsgAndCertEncodingType = X509_ASN_ENCODING|PKCS_7_ASN_ENCODING;
	DecryptPara.cCertStore = 1;
	DecryptPara.rghCertStore = CertStoreArray;

	char pbDecrypted[128] = {0};
	DWORD cbDecrypted = 128;

	if(!CryptDecryptMessage(
		&DecryptPara,
		szEnCryptData, dwEnCryptData,
		(BYTE *)pbDecrypted, &cbDecrypted, NULL))
	{
		printf("CryptDecryptMessage failed\n");
		return 0;
	}
	printf("%s\n", pbDecrypted);

	return 1;
}