#include "stdafx.h"
#include "fun.h"

extern HINSTANCE hin;
//digest
ULONG SKF_Digest(HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen)
{
	FN_SKF_Digest pProc;
	pProc = (FN_SKF_Digest) GetProcAddress(hin, "SKF_Digest");
	if (NULL != pProc) 
	{
		ULONG uRet = (pProc) (hHash, pbData, ulDataLen, pbHashData, pulHashLen);
		if(SAR_OK != uRet)
		{
			puts("SKF_Digest error");
			return uRet;
		}
		else
		{
			puts("SKF_Digest success");
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_DigestInit(DEVHANDLE hDev, ULONG ulAlgId, ECCPUBLICKEYBLOB* pPubKey, unsigned char* pucID, ULONG ulIDLen, HANDLE* phHash)
{
	FN_SKF_DigestInit pProc;
	pProc = (FN_SKF_DigestInit) GetProcAddress(hin, "SKF_DigestInit");
	if (NULL != pProc) 
	{
		ULONG uRet = (pProc) (hDev, ulAlgId, pPubKey, pucID, ulIDLen, phHash);
		if(SAR_OK != uRet)
		{
			puts("SKF_DigestInit error");
			return uRet;
		}
		else
		{
			puts("SKF_DigestInit success");
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_DigestUpdate(HANDLE hHash, BYTE *pbHash, BYTE *pbData, ULONG ulDataLen)
{
	FN_SKF_DigestUpdate pProc;
	pProc = (FN_SKF_DigestUpdate) GetProcAddress(hin, "SKF_DigestUpdate");
	if (NULL != pProc) 
	{
		ULONG uRet = (pProc) (hHash, pbHash, pbData, ulDataLen);
		if(SAR_OK != uRet)
		{
			puts("SKF_DigestUpdate error");
			return uRet;
		}
		else
		{
			puts("SKF_DigestUpdate success");
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_DigestFinal(HANDLE hHash, BYTE *pHashData, ULONG *pulHashLen)
{
	FN_SKF_DigestFinal pProc;
	pProc = (FN_SKF_DigestFinal) GetProcAddress(hin, "SKF_DigestFinal");
	if (NULL != pProc) 
	{
		ULONG uRet = (pProc) (hHash, pHashData, pulHashLen);
		if(SAR_OK != uRet)
		{
			puts("SKF_DigestFinal error");
			return uRet;
		}
		else
		{
			puts("SKF_DigestFinal success");
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}


//这里文件里的每个函数建议一个一个封装，函数的返回值与SKF原函数一样
ULONG SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize)
{
	FN_SKF_EnumDev pProc;
	pProc = (FN_SKF_EnumDev) GetProcAddress(hin, "SKF_EnumDev");
	if (NULL != pProc) 
	{
		//enum device
		ULONG uRet = (pProc) (bPresent,(LPSTR)szNameList, pulSize);
		if(SAR_OK != uRet)
		{
			puts("SKF_EnumDev error");
			return uRet;
		}
		else
		{
			printf("%s,len=%u\n",szNameList, &pulSize);
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_ConnectDev(LPSTR szName, DEVHANDLE *phDev)
{
	FN_SKF_ConnectDev pProc;
	pProc = (FN_SKF_ConnectDev) GetProcAddress(hin, "SKF_ConnectDev");
	if (NULL != pProc)
	{
		//connect device
		ULONG uRet = (pProc) ((LPSTR)szName, phDev);
		if(SAR_OK != uRet)
		{
			puts("SKF_ConnectDev error");
			return uRet;
		}
		else
		{
			puts("SKF_ConnectDev success");
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_DisConnectDev(DEVHANDLE hDev)
{
	FN_SKF_DisConnectDev pProc;
	pProc = (FN_SKF_DisConnectDev) GetProcAddress(hin, "SKF_DisConnectDev");
	if (NULL != pProc)
	{
		//connect device
		ULONG uRet = (pProc) (hDev);
		if(SAR_OK != uRet)
		{
			puts("SKF_DisConnectDev error");
			return uRet;
		}
		else
		{
			puts("SKF_DisConnectDev success");
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_EnumApplication(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize)
{
	FN_SKF_EnumApplication pProc;
	pProc = (FN_SKF_EnumApplication) GetProcAddress(hin, "SKF_EnumApplication");
	if (NULL != pProc)
	{
		//enum application
		ULONG uRet = (pProc) (hDev, (LPSTR)szAppName, pulSize);
		if(SAR_OK != uRet) 
		{
			puts("SKF_EnumApplication error");
			return uRet;
		}
		else
		{
			printf("%s,len=%u\n",szAppName, &pulSize);
			return uRet;
		}
	}
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_OpenApplication(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication)
{
	FN_SKF_OpenApplication pProc;
	pProc = (FN_SKF_OpenApplication) GetProcAddress(hin, "SKF_OpenApplication");
	if (NULL != pProc)
	{
		//open application
		ULONG uRet = (pProc) (hDev, szAppName, phApplication);
		if (SAR_OK != uRet)
		{
			puts("SKF_OpenApplication error");
			return uRet;
		} 
		else
		{
			puts("SKF_OpenApplication success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer)
{
	FN_SKF_OpenContainer pProc;
	pProc = (FN_SKF_OpenContainer) GetProcAddress(hin, "SKF_OpenContainer");
	if (NULL != pProc)
	{
		//open Container
		ULONG uRet = (pProc) (hApplication, szContainerName, phContainer);
		if (SAR_OK != uRet)
		{
			puts("SKF_OpenContainer error");
			return uRet;
		} 
		else
		{
			puts("SKF_OpenContainer success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_CreateContainer(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer)
{
	FN_SKF_CreateContainer pProc;
	pProc = (FN_SKF_CreateContainer) GetProcAddress(hin, "SKF_CreateContainer");
	if (NULL != pProc)
	{
		ULONG uRet = (pProc) (hApplication, szContainerName, phContainer);
		if (SAR_OK != uRet)
		{
			puts("SKF_CreateContainer error");
			printf("%08X\n",uRet);
			return uRet;
		} 
		else
		{
			puts("SKF_CreateContainer success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_GetContainerType(HCONTAINER hContainer, ULONG *pulContainerType)
{
	FN_SKF_GetContainerType pProc;
	pProc = (FN_SKF_GetContainerType) GetProcAddress(hin, "SKF_GetContainerType");
	if (NULL != pProc)
	{
		//GetContianerType
		ULONG uRet = (pProc) (hContainer, pulContainerType);
		if (SAR_OK != uRet)
		{
			puts("SKF_GetContianerType error");
			return uRet;
		} 
		else
		{
			puts("SKF_GetContianerType success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_CloseContainer(HCONTAINER hContainer)
{
	FN_SKF_CloseContainer pProc;
	pProc = (FN_SKF_CloseContainer) GetProcAddress(hin, "SKF_CloseContainer");
	if (NULL != pProc)
	{
		//close Container
		ULONG uRet = (pProc) (hContainer);
		if (SAR_OK != uRet)
		{
			puts("SKF_CloseContainer error");
			return uRet;
		} 
		else
		{
			puts("SKF_CloseContainer success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_EnumContainer(HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize)
{
	FN_SKF_EnumContainer pProc;
	pProc = (FN_SKF_EnumContainer) GetProcAddress(hin, "SKF_EnumContainer");
	if (NULL != pProc)
	{
		//enum Container
		ULONG uRet = (pProc) (hApplication, szContainerName, pulSize);
		if (SAR_OK != uRet)
		{
			puts("SKF_EnumContainer error");
			return uRet;
		} 
		else
		{
			printf("%s,len=%u\n",szContainerName, &pulSize);
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_DeleteContainer(HAPPLICATION hApplication, LPSTR szContainerName)
{
	FN_SKF_DeleteContainer pProc;
	pProc = (FN_SKF_DeleteContainer) GetProcAddress(hin, "SKF_DeleteContainer");
	if (NULL != pProc)
	{
		ULONG uRet = (pProc) (hApplication, szContainerName);
		if (SAR_OK != uRet)
		{
			puts("SKF_DeleteContainer error");
			return uRet;
		} 
		else
		{
			puts("SKF_DeleteContainer success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_RSASignData(HCONTAINER hContainer, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG *pulSignLen)
{
	FN_SKF_RSASignData pProc;
	pProc = (FN_SKF_RSASignData) GetProcAddress(hin, "SKF_RSASignData");
	if (NULL != pProc)
	{
		//sign
		ULONG uRet = (pProc) (hContainer, pbData, ulDataLen, pbSignature, pulSignLen);
		if (SAR_OK != uRet)
		{
			puts("SKF_RSASignData error");
			printf("%08X\n",uRet);
			return uRet;
		} 
		else
		{
			if (pbSignature)
			{
				puts("SKF_RSASignData success");
			}
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}
ULONG SKF_RSAVerify(DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG ulSignLen)
{
	FN_SKF_RSAVerify pProc;
	pProc = (FN_SKF_RSAVerify) GetProcAddress(hin, "SKF_RSAVerify");
	if (NULL != pProc)
	{
		//verify
		ULONG uRet = (pProc) (hDev, pRSAPubKeyBlob, pbData, ulDataLen, pbSignature, ulSignLen);
		if (SAR_OK != uRet)
		{
			puts("SKF_RSAVerify error");
			return uRet;
		} 
		else
		{
			puts("SKF_RSAVerify success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_GenRSAKeyPair(HCONTAINER hContainer, ULONG ulBitsLen , RSAPUBLICKEYBLOB *pBlob)
{
	FN_SKF_GenRSAKeyPair pProc;
	pProc = (FN_SKF_GenRSAKeyPair) GetProcAddress(hin, "SKF_GenRSAKeyPair");
	if (NULL != pProc)
	{
		//生成RSA签名密钥对
		ULONG uRet = (pProc) (hContainer, ulBitsLen, pBlob);
		if (SAR_OK != uRet)
		{
			puts("SKF_GenRSAKeyPair error");
			return uRet;
		} 
		else
		{
			puts("SKF_GenRSAKeyPair success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_ExportPublicKey(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen)
{
	FN_SKF_ExportPublicKey pProc;
	pProc = (FN_SKF_ExportPublicKey) GetProcAddress(hin, "SKF_ExportPublicKey");
	if (NULL != pProc)
	{
		//导出公钥
		ULONG uRet = (pProc) (hContainer, bSignFlag, pbBlob, pulBlobLen);
		if (SAR_OK != uRet)
		{
			puts("SKF_ExportPublicKey error");
			return uRet;
		} 
		else
		{
			puts("SKF_ExportPublicKey success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}


ULONG SKF_VerifyPIN(HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount)
{
	FN_SKF_VerifyPIN pProc;
	pProc = (FN_SKF_VerifyPIN) GetProcAddress(hin, "SKF_VerifyPIN");
	if (NULL != pProc)
	{
		//校验PIN
		ULONG uRet = (pProc) (hApplication, ulPINType, szPIN, pulRetryCount);
		if (SAR_OK != uRet)
		{
			puts("SKF_VerifyPIN error");
			return uRet;
		} 
		else
		{
			puts("SKF_VerifyPIN success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_ImportCertificate(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbCert, ULONG ulCertLen)
{
	FN_SKF_ImportCertificate pProc;
	pProc = (FN_SKF_ImportCertificate) GetProcAddress(hin, "SKF_ImportCertificate");
	if (NULL != pProc)
	{
		//校验PIN
		ULONG uRet = (pProc) (hContainer, bSignFlag, pbCert, ulCertLen);
		if (SAR_OK != uRet)
		{
			puts("SKF_ImportCertificate error");
			return uRet;
		} 
		else
		{
			puts("SKF_ImportCertificate success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}

ULONG SKF_ExtRSAPubKeyOperation(DEVHANDLE hDev, RSAPUBLICKEYBLOB* pRSAPubKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen)
{
	FN_SKF_ExtRSAPubKeyOperation pProc;
	pProc = (FN_SKF_ExtRSAPubKeyOperation) GetProcAddress(hin, "SKF_ExtRSAPubKeyOperation");
	if (NULL != pProc)
	{
		ULONG uRet = (pProc) (hDev, pRSAPubKeyBlob, pbInput, ulInputLen, pbOutput, pulOutputLen);
		if (SAR_OK != uRet)
		{
			puts("SKF_ExtRSAPubKeyOperation error");
			return uRet;
		} 
		else
		{
			puts("SKF_ExtRSAPubKeyOperation success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}
ULONG SKF_ExportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen)
{
	FN_SKF_ExportCertificate pProc;
	pProc = (FN_SKF_ExportCertificate) GetProcAddress(hin, "SKF_ExportCertificate");
	if (NULL != pProc)
	{
		ULONG uRet = (pProc) (hContainer, bSignFlag, pbCert, pulCertLen);
		if (SAR_OK != uRet)
		{
			puts("SKF_ExportCertificate error");
			return uRet;
		} 
		else
		{
			puts("SKF_ExportCertificate success");
			return uRet;
		}
	} 
	else
	{
		puts("get address error");
		return (ULONG)DLL_GET_ADDRESS_ERROR;
	}
}