#include "stdafx.h"
#include "../CSP_sign_verify/fun.h"

bool
MySignMessage(char *data, DWORD &dwLen, BYTE *SignedBlob)
{
	PCCERT_CONTEXT pCertContext = ImportCert(L"FEITIAN ePassNG RSA Cryptographic Service Provider", _T("签名"));
	if (pCertContext ==NULL)
	{
		puts("ImportCert failed");
		return 0;
	}

	CRYPT_SIGN_MESSAGE_PARA SignPara;
	memset(&SignPara, 0, sizeof(SignPara));
	SignPara.cbSize = sizeof(SignPara);
	SignPara.dwMsgEncodingType = X509_ASN_ENCODING|PKCS_7_ASN_ENCODING;
	SignPara.pSigningCert = pCertContext;
	SignPara.HashAlgorithm.pszObjId = szOID_RSA_SHA1RSA;
	SignPara.HashAlgorithm.Parameters.cbData = 0;
	SignPara.cMsgCert = 1;
	SignPara.rgpMsgCert = &pCertContext;

	SignPara.cAuthAttr = 0;
	SignPara.dwInnerContentType = 0;
	SignPara.cMsgCrl = 0;
	SignPara.cUnauthAttr = 0;
	SignPara.dwFlags = 0;
	SignPara.pvHashAuxInfo = NULL;
	SignPara.rgAuthAttr = NULL;

	//SignPara.HashEncryptionAlgorithm.pszObjId = szOID_RSA_RSA;
	//SignPara.HashEncryptionAlgorithm.Parameters.cbData = strlen(data)+1;
	//SignPara.HashEncryptionAlgorithm.Parameters.pbData = (BYTE*)data;
	//SignPara.pvHashEncryptionAuxInfo = NULL;

	const BYTE* rgpbToBesigned[1];
	rgpbToBesigned[0] = (BYTE*)data;

	DWORD rgcbToBesigned[1];
	rgcbToBesigned[0] = strlen(data) +1;

	if(!CryptSignMessage(&SignPara, 
		TRUE,//表示没有明文
		NULL, rgpbToBesigned, rgcbToBesigned, SignedBlob, &dwLen))
	{
		printf("CryptSignMessage failed:%d\n",GetLastError());
		return 0;
	}
}
//
//BOOL WINAPI CryptVerifyMessageSignature(
//										__in          PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara,
//										__in          DWORD dwSignerIndex,
//										__in          const BYTE* pbSignedBlob,
//										__in          DWORD cbSignedBlob,
//										__out         BYTE* pbDecoded,
//										__in_out      DWORD* pcbDecoded,
//										__out_opt     PCCERT_CONTEXT* ppSignerCert
//										);


bool
MyVerifyMessageSignature(BYTE *pbSignature, DWORD dwLen)
{
	CRYPT_VERIFY_MESSAGE_PARA VerifyPara;
	VerifyPara.cbSize = sizeof(VerifyPara);
	VerifyPara.dwMsgAndCertEncodingType = X509_ASN_ENCODING|PKCS_7_ASN_ENCODING;
	VerifyPara.hCryptProv = NULL;
	VerifyPara.pfnGetSignerCertificate = NULL;
	VerifyPara.pvGetArg = NULL;

	DWORD dwSignerIndex = 0;

	if(!CryptVerifyMessageSignature(
		&VerifyPara,
		dwSignerIndex,
		pbSignature,
		dwLen,
		NULL,
		NULL,
		NULL))
	{
		printf("CryptVerifyMessage failed\n");
		return 0;
	}

	return 1;
}
