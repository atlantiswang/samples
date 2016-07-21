#pragma once

#include "stdafx.h"

//宏开关，设置验证方式：VERIFYOTHER（验证其它接口的签名，此项设置后SKFVERIFY无效），SKFVERIFY(在VERIFYOTHER没有定义时有效，
//若定义SKFVERIFY就是以SKF的方式验签，如果没有定义，就是以OpenSSL方式验签）

//#define VERIFYOTHER
#define SKFVERIFY

#define MAX_RSA_MODULUS_LEN 256 //为算法模数的最大长度
#define MAX_RSA_EXPONENT_LEN 4 //为算法指数的最大长度

#define ECC_MAX_XCOORDINATE_BITS_LEN 512
#define ECC_MAX_YCOORDINATE_BITS_LEN 512

#define ADMIN_TYPE 0
#define USER_TYPE  1

#define SGD_SM3		0x00000001
#define SGD_SHA1	0x00000002
#define SGD_SHA256	0x00000004

typedef HANDLE DEVHANDLE;
typedef HANDLE HAPPLICATION;
typedef HANDLE HCONTAINER;

typedef UINT8 BYTE;

typedef struct Struct_Version{
	BYTE major;
	BYTE minor;
}VERSION;

typedef struct Struct_DEVINFO{
	VERSION		Version;
	CHAR		Manufacturer[64];
	CHAR		Issuer[64];
	CHAR		Label[32];
	CHAR		SerialNumber[32];
	VERSION		HWVersion;
	VERSION		FirmwareVersion;
	ULONG		AlgSymCap;
	ULONG		AlgAsymCap;
	ULONG		AlgHashCap;
	ULONG		DevAuthAlgId;
	ULONG		TotalSpace;
	ULONG		FreeSpace;
	BYTE  		Reserved[64];
}DEVINFO,*PDEVINFO;

typedef struct Struct_ECCPUBLICKEYBLOB{
	ULONG	BitLen;
	BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];
}ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;

typedef struct Struct_RSAPUBLICKEYBLOB{
	ULONG	AlgID;
	ULONG	BitLen;
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];
}RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;
/* 设备管理 7.1.2 - 7.1.12 共计11个函数 */
typedef ULONG (__stdcall* FN_SKF_WaitForDevEvent)(LPSTR szDevName, ULONG *pulDevNameLen, ULONG *pulEvent);
typedef ULONG (__stdcall* FN_SKF_CancelWaitForDevEvent)();
typedef ULONG (__stdcall* FN_SKF_EnumDev)(BOOL bPresent, LPSTR szNameList, ULONG *pulSize); 
typedef ULONG (__stdcall* FN_SKF_ConnectDev)(LPSTR szName, DEVHANDLE *phDev);
typedef ULONG (__stdcall* FN_SKF_DisConnectDev)(DEVHANDLE hDev);
typedef ULONG (__stdcall* FN_SKF_GetDevState)(LPSTR szDevName , ULONG *pulDevState); 
typedef ULONG (__stdcall* FN_SKF_SetLabel)(DEVHANDLE hDev, LPSTR szLabel); 
typedef ULONG (__stdcall* FN_SKF_GetDevInfo)(DEVHANDLE hDev, DEVINFO *pDevInfo); 
typedef ULONG (__stdcall* FN_SKF_LockDev)(DEVHANDLE hDev, ULONG ulTimeOut);
typedef ULONG (__stdcall* FN_SKF_UnlockDev)(DEVHANDLE hDev);
typedef ULONG (__stdcall* FN_SKF_Transmit)(DEVHANDLE hDev, BYTE* pbCommand, ULONG ulCommandLen,BYTE* pbData, ULONG* pulDataLen);
/*应用管理*/
typedef ULONG (__stdcall* FN_SKF_OpenApplication)(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);
typedef ULONG (__stdcall* FN_SKF_EnumApplication)(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize);
/*容器管理*/
typedef ULONG (__stdcall* FN_SKF_OpenContainer)(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);
typedef ULONG (__stdcall* FN_SKF_CloseContainer)(HCONTAINER hContainer);
typedef ULONG (__stdcall* FN_SKF_EnumContainer)(HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize); 
typedef ULONG (__stdcall* FN_SKF_ImportCertificate)(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbCert, ULONG ulCertLen);
typedef ULONG (__stdcall* FN_SKF_GetContainerType)(HCONTAINER hContainer, ULONG *pulContainerType);
typedef ULONG (__stdcall* FN_SKF_CreateContainer)(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer);
typedef ULONG (__stdcall* FN_SKF_DeleteContainer)(HAPPLICATION hApplication, LPSTR szContainerName); 
/*密码服务*/
typedef ULONG (__stdcall* FN_SKF_RSASignData)(HCONTAINER hContainer, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG *pulSignLen);
typedef ULONG (__stdcall* FN_SKF_RSAVerify)(DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG ulDataLen, BYTE *pbSignature, ULONG ulSignLen); 
typedef ULONG (__stdcall* FN_SKF_GenRSAKeyPair)(HCONTAINER hContainer, ULONG ulBitsLen , RSAPUBLICKEYBLOB *pBlob);
typedef ULONG (__stdcall* FN_SKF_VerifyPIN) (HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount);
typedef ULONG (__stdcall* FN_SKF_ExportPublicKey)(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen);
typedef ULONG (__stdcall* FN_SKF_ExtRSAPubKeyOperation)(DEVHANDLE hDev, RSAPUBLICKEYBLOB* pRSAPubKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen);
/*摘要计算*/
typedef ULONG (__stdcall* FN_SKF_Digest)(HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen); 
typedef ULONG (__stdcall* FN_SKF_DigestInit)(DEVHANDLE hDev, ULONG ulAlgId, ECCPUBLICKEYBLOB* pPubKey, unsigned char* pucID, ULONG ulIDLen, HANDLE* phHash);
typedef ULONG (__stdcall* FN_SKF_DigestUpdate)(HANDLE hHash, BYTE *pbHash, BYTE *pbData, ULONG ulDataLen); //?
typedef ULONG (__stdcall* FN_SKF_DigestFinal)(HANDLE hHash, BYTE *pHashData, ULONG *pulHashLen);
typedef ULONG (__stdcall* FN_SKF_ExportCertificate)(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen);

#define SAR_OK	0x00000000
#define SAR_Fail	0x0A000001
#define SAR_UnknownErr	0x0A000002
#define SAR_NotSupportYetErr	0x0A000003
#define SAR_FileErr	0x0A000004
#define SAR_InvalidHandleErr	0x0A000005
#define SAR_InvalidParamErr	0x0A000006
#define SAR_ReadFileErr	0x0A000007
#define SAR_WriteFileErr	0x0A000008
#define SAR_NameLenErr	0x0A000009
#define SAR_KeyUsageErr	0x0A00000A
#define SAR_ModulusLenErr	0x0A00000B
#define SAR_NotInitializeErr	0x0A00000C
#define SAR_ObjErr	0x0A00000D
#define SAR_MemoryErr	0x0A00000E
#define SAR_TimeoutErr	0x0A00000F
#define SAR_IndataLenErr	0x0A000010
#define SAR_IndataErr	0x0A000011
#define SAR_GenRandErr	0x0A000012
#define SAR_HashObjErr	0x0A000013
#define SAR_HashErr	0x0A000014
#define SAR_GenRsaKeyErr	0x0A000015
#define SAR_RsaModulusLenErr	0x0A000016
#define SAR_CspImprtPubKeyErr	0x0A000017
#define SAR_RsaEncErr	0x0A000018
#define SAR_RsaDecErr	0x0A000019
#define SAR_HashNotEqualErr	0x0A00001A
#define SAR_KeyNotFountErr	0x0A00001B
#define SAR_CertNotFountErr	0x0A00001C
#define SAR_NotExportErr	0x0A00001D
#define SAR_DecryptPadErr	0x0A00001E
#define SAR_MacLenErr	0x0A00001F
#define SAR_BUFFER_TOO_SMALL	0x0A000020
#define SAR_KeyInfoTypeErr	0x0A000021
#define sar_not_eventerr	0x0A000022
#define SAR_DEVICE_REMOVED	0x0A000023
#define SAR_PIN_INCORRECT	0x0A000024
#define SAR_PIN_LOCKED	0x0A000025
#define SAR_PIN_INVALID	0x0A000026
#define SAR_PIN_LEN_RANGE	0x0A000027
#define SAR_USER_ALREADY_LOGGED_IN	0x0A000028
#define SAR_USER_PIN_NOT_INITIALIZED	0x0A000029
#define SAR_USER_TYPE_INVALID	0x0A00002A
#define SAR_APPLICATION_NAME_INVALID	0x0A00002B
#define SAR_APPLICATION_EXISTS	0x0A00002C
#define SAR_USER_NOT_LOGGED_IN	0x0A00002D
#define SAR_APPLICATION_NOT_EXISTS	0x0A00002E
#define SAR_FILE_ALREADY_EXIST	0x0A00002F
#define SAR_NO_ROOM	0x0A000030
#define SAR_FILE_NOT_EXIST	0x0A000031
#define SAR_REACH_MAX_CONTAINER_COUNT	0x0A000032

#define DLL_GET_ADDRESS_ERROR 0xA000033