#include "stdafx.h"
#include "fun.h"
#include "struct.h"
#include "SKFFun.h"
#include "OpenFun.h"

#define PIN_CODE "12345678"

int WriteToLog(char *path, BYTE* txt, ULONG len)
{
	FILE *fp;
	fp = fopen(path,"wb");
	if (fp == NULL)
		return 0;
	int i = fwrite(txt, sizeof(BYTE), len, fp);

	fclose(fp);
	return 1;
}

//读取公钥信息
int ReadInLog(char *path, BYTE* txt, ULONG len)
{
	FILE *fp;
	int nLen=0;
	fp = fopen(path,"rb");
	if (fp == NULL)
		return 0;

	nLen = fread(txt, sizeof(BYTE), len, fp);

	fclose(fp);
	return nLen;
}

//验证第三方的签名，正表示成功，0表示失败
int VerifyOther()
{
	char szDevName[100] ={0};
	ULONG pulSize = 100;
	if(SAR_OK != SKF_EnumDev(TRUE, szDevName, &pulSize))
		return 0;
	//connect device
	DEVHANDLE hDev;
	if(SAR_OK != SKF_ConnectDev(szDevName, &hDev))
		return 0;

	//read pbSignature
	BYTE *pbSignature = new BYTE[512];
	ULONG ulSignLen;
	ulSignLen = ReadInLog("../CSP_sign_verify/log/signature.log", pbSignature, 128);

	//verify
	PRSAPUBLICKEYBLOB pBlob = new RSAPUBLICKEYBLOB;
	ULONG pulBlobLen2 = sizeof(RSAPUBLICKEYBLOB);
	pBlob = OpenSSLToSKF();

	BYTE pbHashData[1024] = {0};
	ULONG pulHashLen = 1024;
	BYTE pbData[1024] = {0};
	puts("input origin data:");
	scanf("%s", pbData);
	ULONG ulDataLen = strlen((const char*)pbData);
	//计算摘要
	HANDLE hHash;
	if (SAR_OK != SKF_DigestInit(hDev, SGD_SHA1, NULL, NULL, 0, &hHash))
		return 0;
	if(SAR_OK != SKF_Digest(hHash, pbData, ulDataLen, pbHashData, &pulHashLen))
		return 0;
	//添加15个字节, 做为PKCS1的填充。
	//0x30 0x21 0x30 0x09 0x06 0x05 0x2B 0x0E 0x03 0x02 0x1A 0x05 0x00 0x04 0x14
	BYTE fif[128] = {48,33,48,9,6,5,43,14,3,2,26,5,0,4,20};
	strncpy((char*)fif+15, (char *)pbHashData, 20);
	pulHashLen += 15;
	//verify
	ULONG nRet = SKF_RSAVerify(hDev, pBlob, fif, pulHashLen, pbSignature, ulSignLen);
	if(SAR_OK != nRet)
	{
		printf("%08X\n",nRet);
		return 0;
	}

	return 1;
}
//正表示成功，0表示失败
int SKF_Sign(BYTE **pbSignature, ULONG *ppulSignLen)
{
	//enum device
	char szDevName[100] ={0};
	ULONG pulSize = 100;
	if(SAR_OK != SKF_EnumDev(TRUE, szDevName, &pulSize))
		return 0;
	//connect device
	DEVHANDLE hDev;
	if(SAR_OK != SKF_ConnectDev(szDevName, &hDev))
		return 0;
	//enum application
	char szAppName[100] ={0};
	pulSize = 100;
	if(SAR_OK != SKF_EnumApplication(hDev, szAppName, &pulSize))
		return 0;
	//open application
	HAPPLICATION phApplication;
	if(SAR_OK != SKF_OpenApplication(hDev, szAppName, &phApplication))
		return 0;
	//enum container
	char szContainerName[1024] = {0};
	pulSize = 1024;
	if(SAR_OK != SKF_EnumContainer(phApplication, szContainerName, &pulSize))
		return 0;
	//open container
	HCONTAINER phContainer;
	if(SAR_OK != SKF_OpenContainer(phApplication, szContainerName, &phContainer))
		return 0;

	//输入PIN进行用户登录
	ULONG pulRetryCount;
	if(SAR_OK != SKF_VerifyPIN(phApplication, USER_TYPE, (LPSTR)PIN_CODE, &pulRetryCount))
		return 0;
	//sign
	/*先获取签名数据长度*/
	BYTE pbHashData[1024] = {0};
	ULONG pulHashLen = 1024;
	BYTE pbData[1024] = {0};
	puts("input sign data:");
	scanf("%s", pbData);
	ULONG ulDataLen = strlen((const char*)pbData);
	//计算摘要
	HANDLE hHash;
	if(SAR_OK != SKF_DigestInit(hDev, SGD_SHA1, NULL, NULL, 0, &hHash))
		return 0;
	if(SAR_OK != SKF_Digest(hHash, pbData, ulDataLen, pbHashData, &pulHashLen))
		return 0;
	//摘要转化+15字节
	//0x30 0x21 0x30 0x09 0x06 0x05 0x2B 0x0E 0x03 0x02 0x1A 0x05 0x00 0x04 0x14
	BYTE fif[128] = {48,33,48,9,6,5,43,14,3,2,26,5,0,4,20};
	strncpy((char*)fif+15, (char *)pbHashData, 20);
	pulHashLen += 15;
	//计算签名长度
	if(SAR_OK != SKF_RSASignData(phContainer, fif, pulHashLen, NULL, ppulSignLen))
		return 0;
	/*再计算签名*/
	*pbSignature = new BYTE[*ppulSignLen];
	if(SAR_OK != SKF_RSASignData(phContainer, fif, pulHashLen, *pbSignature, ppulSignLen))
		return 0;

	WriteToLog("../CSP_sign_verify/log/SKF/skf.log", *pbSignature, *ppulSignLen);

	if(SAR_OK != SKF_DisConnectDev(hDev))
		return 0;

	return 1;
}

int SKF_Verify(BYTE *pbSignature, ULONG pulSignLen)
{
	//enum device
	char szDevName[100] ={0};
	ULONG pulSize = 100;
	if(SAR_OK != SKF_EnumDev(TRUE, szDevName, &pulSize))
		return 0;
	//connect device
	DEVHANDLE hDev;
	if(SAR_OK != SKF_ConnectDev(szDevName, &hDev))
		return 0;
	//enum application
	char szAppName[100] ={0};
	pulSize = 100;
	if(SAR_OK != SKF_EnumApplication(hDev, szAppName, &pulSize))
		return 0;
	//open application
	HAPPLICATION phApplication;
	if(SAR_OK != SKF_OpenApplication(hDev, szAppName, &phApplication))
		return 0;
	//enum container
	char szContainerName[100] = {0};
	pulSize = 100;
	if(SAR_OK != SKF_EnumContainer(phApplication, szContainerName, &pulSize))
		return 0;
	//open container
	HCONTAINER phContainer;
	if(SAR_OK != SKF_OpenContainer(phApplication, szContainerName, &phContainer))
		return 0;

	/*验证PIN码*/
	ULONG pulRetryCount;
	if(SAR_OK != SKF_VerifyPIN(phApplication, USER_TYPE, (LPSTR)PIN_CODE, &pulRetryCount))
 		return 0;
	/*先计算出公钥*/
	PRSAPUBLICKEYBLOB pBlob = new RSAPUBLICKEYBLOB;
	ULONG pulBlobLen = sizeof(RSAPUBLICKEYBLOB);
	int n = SKF_ExportPublicKey(phContainer, TRUE, (BYTE *)pBlob, &pulBlobLen);
	if (SAR_OK != n)
	{	
		printf("%08X\n",n);
		return 0;
	}
	/*再做验证*/
	/*先获取原始数据*/
#ifdef SKFVERIFY
	BYTE pbHashData[1024] = {0};
	ULONG pulHashLen = 1024;
	BYTE pbData[1024] = {0};
	puts("input origin data:");
	scanf("%s", pbData);
	ULONG ulDataLen = strlen((const char*)pbData);
	//计算摘要
	HANDLE hHash;
	if (SAR_OK != SKF_DigestInit(hDev, SGD_SHA1, NULL, NULL, 0, &hHash))
		return 0;
	if(SAR_OK != SKF_Digest(hHash, pbData, ulDataLen, pbHashData, &pulHashLen))
		return 0;
	//添加15个字节
	//0x30 0x21 0x30 0x09 0x06 0x05 0x2B 0x0E 0x03 0x02 0x1A 0x05 0x00 0x04 0x14
	BYTE fif[128] = {48,33,48,9,6,5,43,14,3,2,26,5,0,4,20};
	strncpy((char*)fif+15, (char *)pbHashData, 20);
	pulHashLen += 15;
	//verify
	ULONG nRet = SKF_RSAVerify(hDev, pBlob, fif, pulHashLen, pbSignature, pulSignLen);
	if(SAR_OK != nRet)
	{
		printf("%08X\n",nRet);
		return 0;
	}
#else
	//OpenSSL方式的验证
	//下面这个函数会将公钥写进log文件里
	EVP_PKEY *pk = SKFToOpenSSL(pBlob);
	unsigned char data[1024] = {0};
	puts("input origin data:");
	scanf("%s", data);
	unsigned int data_cb = strlen((const char*)data);
	if(0 != OpenSSL_Verify(pk, 
		data, data_cb, 
		(unsigned char* )pbSignature, (unsigned int) pulSignLen))
	{
		puts("verify others failed");
		return 0;
	}
#endif

	return 1;
}