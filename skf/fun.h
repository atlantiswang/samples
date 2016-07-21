#pragma once
#include "struct.h"

ULONG SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize);
ULONG SKF_ConnectDev(LPSTR szName, DEVHANDLE *phDev);
ULONG SKF_DisConnectDev(DEVHANDLE hDev);
ULONG SKF_EnumApplication(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize);
ULONG SKF_OpenApplication(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);
ULONG SKF_OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);
ULONG SKF_CloseContainer(HCONTAINER hContainer);
ULONG SKF_EnumContainer(HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize); 
ULONG SKF_GetContainerType(HCONTAINER hContainer, ULONG *pulContainerType);
ULONG SKF_CreateContainer(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer);
ULONG SKF_DeleteContainer(HAPPLICATION hApplication, LPSTR szContainerName); 

ULONG SKF_RSASignData(HCONTAINER hContainer, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG *pulSignLen);
ULONG SKF_RSAVerify(DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG ulSignLen); 
ULONG SKF_GenRSAKeyPair(HCONTAINER hContainer, ULONG ulBitsLen , RSAPUBLICKEYBLOB *pBlob);
ULONG SKF_ExportPublicKey(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen);
ULONG SKF_ImportCertificate(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbCert, ULONG ulCertLen);
ULONG SKF_ExtRSAPubKeyOperation(DEVHANDLE hDev, RSAPUBLICKEYBLOB* pRSAPubKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen);

ULONG SKF_VerifyPIN(HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount);

ULONG SKF_Digest(HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen); 
ULONG SKF_DigestInit(DEVHANDLE hDev, ULONG ulAlgId, ECCPUBLICKEYBLOB* pPubKey, unsigned char* pucID, ULONG ulIDLen, HANDLE* phHash);
ULONG SKF_DigestUpdate(HANDLE hHash, BYTE *pbHash, BYTE *pbData, ULONG ulDataLen); 
ULONG SKF_DigestFinal(HANDLE hHash, BYTE *pHashData, ULONG *pulHashLen);
/* 获取证书 */
ULONG SKF_ExportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen);