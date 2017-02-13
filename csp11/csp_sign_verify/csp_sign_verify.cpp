// CSP_sign_verify.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "fun.h"


BYTE *pbKeyBlob;    //保存密钥blob缓冲区指针

bool CSP_sign(BYTE *pbSignature, DWORD *pdwSigLen)
{
	//申请hProv
	HCRYPTPROV hProv = NULL;
	DWORD dwErr = 0;
	
	if (!CryptAcquireContext(
		&hProv, 
		_T("3fa0f121-8140-4782-b5b4-6d19d4b353e3"),
		_T("FEITIAN ePassNG RSA Cryptographic Service Provider"),
		PROV_RSA_FULL,
		0))
	{
		printf("CryptAcquireContext failed:%X\n", GetLastError());
		return false;
	}
	BYTE  pbCertContainerName[10][40] = {0};  //容器名称
	DWORD  dwCertContainerNameLen = 40;     //容器名称长度
	DWORD  dwCertNumber = 0;  //容器数目
#if 0
	if(CryptGetProvParam(
		hProv, PP_ENUMCONTAINERS,
		pbCertContainerName[dwCertNumber],
		&dwCertContainerNameLen,
		CRYPT_FIRST))
	{
		if (dwCertContainerNameLen != 0)
			dwCertNumber ++;
		//枚举其它容器，最后一个参数为0
		//"3fa0f121-8140-4782-b5b4-6d19d4b353e3"
		//"698D363C-1FF8-4AAE-872B-D7C428777B07"
		while(CryptGetProvParam(
			hProv, PP_ENUMCONTAINERS,
			pbCertContainerName[dwCertNumber],
			&dwCertContainerNameLen, 0))
		{
			if(dwCertContainerNameLen != 0)
				dwCertNumber++;
		}
	}
#endif 
	//输入pin CryptSetProvParam不管什么情况下都会返回FALSE?(只不过getlasterror为0罢了）
#if 1
	BYTE *pbData = (BYTE*)"123456";
	CryptSetProvParam(
		hProv, PP_SIGNATURE_PIN, (BYTE*)pbData, 0);
	if(GetLastError() == 0)
		puts("验证Pin码成功");
	else
	{
		puts("验证Pin码失败");
		return false;
	}
#endif
	//怎么清队pin码缓存，即每次都要输入pin
	//698D363C-1FF8-4AAE-872B-D7C428777B07
	//3fa0f121-8140-4782-b5b4-6d19d4b353e3
	//创建离散对象
	HCRYPTHASH hHash = NULL;
	if (!CryptCreateHash(
		hProv, 
		CALG_SHA1,
		NULL,
		0,
		&hHash))
	{
		puts("CryptCreateHash error");
		return false;
	}
	//计算数据摘要
	char text[256] = {0};
	puts("input data:");
	scanf("%s", text);
	DWORD len = strlen(text);
	if (!CryptHashData(
		hHash,
		(const BYTE*)text,
		len, 0))
	{
		puts("CryptHashData error");
		CryptDestroyHash(hHash);
		return false;
	}

	printByte((BYTE*)text, len);
	//进行签名
	
	if(!CryptSignHash( 
		hHash, 
		AT_SIGNATURE,
		NULL,
		0,
		pbSignature, 
		pdwSigLen
		))
	{
		//NTE_NO_KEY
		printf("CryptSignHash failed:%x\n",GetLastError());
		return false;
	}
	//print signature data
	printByte(pbSignature, *pdwSigLen);

	if(hHash)
		CryptDestroyHash(hHash);
	return true;
}

bool 
CSP_verify(BYTE *pbSignature, DWORD *pdwSigLen)
{
	//先导入证书
 	PCCERT_CONTEXT pCert = NULL;
#if 1
	if(!(pCert = ImportCert(L"FEITIAN ePassNG RSA Cryptographic Service Provider", _T("签名"))))
	{
		puts("importCert failed");
		return false;
	}
#endif
#if 0
	//把证书导出来
	FILE *fp = NULL;
	fp = fopen("cert.cer", "wb");
	int num = fwrite(pCert->pbCertEncoded, 1, pCert->cbCertEncoded, fp);
	printf("%d\n", num);
	fclose(fp);
#endif
#if 0
	BYTE bBuf[2048] = {0};
	FILE *fp2 = NULL;
	fp2 = fopen("cert.cer", "rb");
	int num2 =fread(bBuf, 1, 2048, fp2);
	printf("%d\n", num2);
	fclose(fp2);
	pCert =
	CertCreateCertificateContext(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING, bBuf, num2); 

	union
	{
		BYTE byteBuf[1024];
		CRYPT_KEY_PROV_INFO kpi;
	};
	memset(byteBuf, 0, 1024);
	DWORD dwLen = 1024;
	//导入证书应该没有问题。但是不能使用以下的函数。
	if(!CertGetCertificateContextProperty(pCert, CERT_KEY_PROV_INFO_PROP_ID, byteBuf, &dwLen))
	{
		puts("can't Get CertificateContext Property");
		return false;
	}
	if(wcscmp(kpi.pwszProvName, L"FEITIAN ePassNG RSA Cryptographic Service Provider") != 0)
		;
#endif


	//申请临时的一个CSP
	HCRYPTPROV hProv = NULL;
	if (!CryptAcquireContext(
		&hProv, 
		_T("CSP_sing_verify"),
		NULL,
		PROV_RSA_FULL,
		0))
	{
		if(CryptAcquireContext(
			&hProv, 
			_T("CSP_sing_verify"),
			NULL, 
			PROV_RSA_FULL, 
			CRYPT_NEWKEYSET)) 
		{
			printf("A new key container has been created.\n");
		}
		else
		{
			printf("Could not create a new key container.\n");
			return false;
		}

	}

	HCRYPTHASH hHash = NULL;
	if (!CryptCreateHash(
		hProv, 
		CALG_SHA1,
		NULL,
		0,
		&hHash))
	{
		puts("CryptCreateHash error");
		return false;
	}
	//计算数据摘要
	char text[256] = {0};
	puts("input data:");
	scanf("%s", text);
	DWORD len = strlen(text);
	if (!CryptHashData(
		hHash,
		(const BYTE*)text,
		len, 0))
	{
		puts("CryptHashData error");
		CryptDestroyHash(hHash);
		return false;
	}
	
	HCRYPTKEY hPubKey = NULL;

	if(!CryptImportPublicKeyInfo(hProv, pCert->dwCertEncodingType, &pCert->pCertInfo->SubjectPublicKeyInfo, &hPubKey))      
	{      
		printf("CryptImportPublicKeyInfo error:%x.\n",GetLastError());  
		return false;  
	}  
		
	if(!CryptVerifySignature(hHash, pbSignature, *pdwSigLen, 
		hPubKey, NULL, 0))
	{
		//NTE_BAD_SIGNATURE
		printf("CryptVerifySignature failed.%x\n",GetLastError());
		return false;
	}
	
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BYTE pbSignature[1024] = {0};
	DWORD dwSigLen = 1024;

#if 0
	if(!CSP_sign(pbSignature, &dwSigLen))
	{
		puts("CSP_sign failed");
		return -1;
	}else
	{
		//CSP比较特殊，签名的数据字节序不同。要反过来
		BYTE bTemp = 0;
		for (int i =0; i <dwSigLen/2; i++)
		{
			bTemp = pbSignature[i];
			pbSignature[i] = pbSignature[dwSigLen-1-i];
			pbSignature[dwSigLen-1-i] = bTemp;
		}
		//将签名数据写入本地文件中（工程文件/log/signature.log）

		FILE *fp = NULL;
		fp = fopen("./log/signature.log", "w");
		int numwritten = fwrite(pbSignature, sizeof(BYTE), dwSigLen, fp);
		printf("written %d bytes\n", numwritten);

		//将公钥写到本地文件中
 		PCCERT_CONTEXT pCert = NULL;
 		pCert = ImportCert("test20151202003", _T("签名"));

		CERT_PUBLIC_KEY_INFO PubKey = pCert->pCertInfo->SubjectPublicKeyInfo;
		CRYPT_BIT_BLOB PublicKey = PubKey.PublicKey;
		BYTE* pbData = PublicKey.pbData;
		DWORD cbData = PublicKey.cbData;
		DWORD cUnuseBits = PublicKey.cUnusedBits;

		fp = NULL;
		fp = fopen("./log/publickey.log", "w");
		numwritten = fwrite(pbData, sizeof(BYTE), cbData - cUnuseBits, fp);
		printf("written %d bytes\n", numwritten);
		fclose(fp);
	}
#elif 1
	if(!CSP_sign(pbSignature, &dwSigLen))
	{
		puts("CSP_sin failed");
		return -1;
	}else
	{
		puts("CSP_sin success");
		if (!CSP_verify(pbSignature, &dwSigLen))
		{
			puts("CSP_verify failed");
		}
		else
			puts("CSP_verify success");
			
	}
#endif
	/////////////////////////////////////
	system("pause");
	return 0;
}