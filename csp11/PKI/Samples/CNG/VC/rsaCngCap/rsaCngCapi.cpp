#include "stdafx.h"
#include <ksp_ext.h>

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

#define KNOWN_DATA      "SignThis"
#define KNOWN_DATALEN   8


#define RtlGenRandom    SystemFunction036 

extern "C" BOOLEAN WINAPI RtlGenRandom(
                        OUT PVOID RandomBuffer,
                        IN  ULONG RandomBufferLength);

//utility for big-little endian conversion
BOOL ReverseBytes (
                   IN OUT   PBYTE   pbByte,
                   IN       DWORD   cbByte)
{
    DWORD dwCount = 0;
    BYTE  bTmp    = 0;

    for( dwCount=0; dwCount < cbByte/2; dwCount++)
    {
      bTmp = *(pbByte + dwCount);
      *(pbByte + dwCount) = *(pbByte + cbByte - dwCount -1);
      *(pbByte + cbByte - dwCount -1) = bTmp;
    }

    return TRUE;

}

void SignWithCapiVerifyWithCng(void)
{

    HCRYPTHASH                  hHash           = 0;
    HCRYPTKEY                   hKey            = 0;
    HCRYPTPROV                  hProv           = 0;
    PBYTE                       pbSignature     = NULL;
    DWORD                       cbSignature     = 0;
    PBYTE                       pbBlob          = NULL;
    DWORD                       cbBlob          = 0;
    BCRYPT_ALG_HANDLE           hAlgorithm      = NULL;
    NCRYPT_KEY_HANDLE           hTmpKey         = NULL;
    BCRYPT_HASH_HANDLE          hCngHash        = NULL;
    NTSTATUS                    Status          = STATUS_UNSUCCESSFUL;
    SECURITY_STATUS             secStatus       = ERROR_SUCCESS;
    DWORD                       cbData          = 0,
                                cbHash          = 0,
                                cbHashObject    = 0;
    PBYTE                       pbHashObject    = NULL;
    PBYTE                       pbHash          = NULL;
    BCRYPT_PKCS1_PADDING_INFO   PKCS1PaddingInfo= {0};
    NCRYPT_PROV_HANDLE          hProvider       = 0;
    
    //delete, ignore errors
    CryptAcquireContext(
                    &hProv,
                    L"test",
                    MS_STRONG_PROV,
                    PROV_RSA_FULL,
                    CRYPT_DELETEKEYSET);

    //acquire handle to a csp container
    if(!CryptAcquireContext(
                    &hProv,
                    L"test",
                    MS_STRONG_PROV,
                    PROV_RSA_FULL,
                    CRYPT_NEWKEYSET))
    {
        wprintf(L"**** Error 0x%x returned by CryptAcquireContext\n", GetLastError());
        goto Cleanup;
    }

    //generate a key
    if(!CryptGenKey(
                hProv,
                AT_SIGNATURE,
                0,
                &hKey))
    {
        wprintf(L"**** Error 0x%x returned by CryptGenKey\n", GetLastError());
        goto Cleanup;
    }

    //create and sign hash with CAPI API
    if(!CryptCreateHash(
		            hProv,
		            CALG_SHA1,
		            0,
                    0,
                    &hHash))
    {
        wprintf(L"**** Error 0x%x returned by CryptCreateHash\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptHashData(
		            hHash,
		            (PBYTE)KNOWN_DATA,
		            KNOWN_DATALEN,
                    0))
    {
        wprintf(L"**** Error 0x%x returned by CryptHashData\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptSignHash(
		            hHash,
		            AT_SIGNATURE, 
                    NULL,
                    0,
                    NULL,
                    &cbSignature))
    {
        wprintf(L"**** Error 0x%x returned by CryptSignHash\n", GetLastError());
        goto Cleanup;
    }


    pbSignature = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbSignature);
    if(NULL == pbSignature)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    if(!CryptSignHash(
		            hHash,
		            AT_SIGNATURE,
                    NULL,
                    0,
                    pbSignature,
                    &cbSignature))
    {
        wprintf(L"**** Error 0x%x returned by CryptSignHash\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptExportKey(
                    hKey,
                    0,
                    PUBLICKEYBLOB,
                    0,
                    NULL,
                    &cbBlob))
    {
        wprintf(L"**** Error 0x%x returned by CryptExportKey\n", GetLastError());
        goto Cleanup;
    }

 
    pbBlob = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbBlob);
    if(NULL == pbBlob)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    if(!CryptExportKey(
                    hKey,
                    0,
                    PUBLICKEYBLOB,
                    0,
                    pbBlob,
                    &cbBlob))
    {
        wprintf(L"**** Error 0x%x returned by CryptExportKey\n", GetLastError());
        goto Cleanup;
    }


    //verify with cng
    if(!NT_SUCCESS(Status =BCryptOpenAlgorithmProvider(
                                                    &hAlgorithm, 
                                                    BCRYPT_SHA1_ALGORITHM, 
                                                    NULL, 
                                                    0) ))
    {
        wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", Status);
        goto Cleanup;
    }


    if(!NT_SUCCESS(Status =BCryptGetProperty( 
                                            hAlgorithm, 
                                            BCRYPT_OBJECT_LENGTH,
                                            (PBYTE)&cbHashObject,
                                            sizeof(DWORD),
                                            &cbData, 
                                            0) ))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", Status);
        goto Cleanup;
    }

    pbHashObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHashObject); 
    if(NULL == pbHashObject)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    if(!NT_SUCCESS(Status = BCryptGetProperty( 
                                        hAlgorithm, 
                                        BCRYPT_HASH_LENGTH,
                                        (PBYTE)&cbHash,
                                        sizeof(DWORD),
                                        &cbData, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", Status);
        goto Cleanup;
    }


    pbHash = (PBYTE) HeapAlloc (GetProcessHeap (), 0, cbHash);
    if(NULL == pbHash)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

   
    if(!NT_SUCCESS(Status = BCryptCreateHash(
                                        hAlgorithm, 
                                        &hCngHash, 
                                        pbHashObject, 
                                        cbHashObject, 
                                        NULL, 
                                        0, 
                                        0) ))
    {
        wprintf(L"**** Error 0x%x returned by BCryptCreateHash\n", Status);
        goto Cleanup;
    }


    if(!NT_SUCCESS(Status = BCryptHashData(
                                    hCngHash,
		                            (PBYTE)KNOWN_DATA,
		                            KNOWN_DATALEN,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptHashData\n", Status);
        goto Cleanup;
    }

    //close the hash
    if(!NT_SUCCESS(Status = BCryptFinishHash(
                                        hCngHash, 
                                        pbHash, 
                                        cbHash, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptFinishHash\n", Status);
        goto Cleanup;
    }

    //reverse since CNG is big endian and CAPI is little endian
    ReverseBytes(pbSignature, cbSignature);

    if(FAILED(secStatus = NCryptOpenStorageProvider(
                                            &hProvider, 
                                            KSP_NAME, 
                                            0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptOpenStorageProvider\n", secStatus);
        goto Cleanup;
    }

    if(FAILED(secStatus = NCryptImportKey(
                                    hProvider,
                                    NULL,
                                    LEGACY_RSAPUBLIC_BLOB,
                                    NULL,
                                    &hTmpKey,
                                    pbBlob,
                                    cbBlob,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptImportKey\n", secStatus);
        goto Cleanup;
    }

    //specify PKCS padding
    PKCS1PaddingInfo.pszAlgId = NCRYPT_SHA1_ALGORITHM;

    if(FAILED(secStatus = NCryptVerifySignature(
                                        hTmpKey,
                                        &PKCS1PaddingInfo,
                                        pbHash,
                                        cbHash,
                                        pbSignature,
                                        cbSignature,
                                        NCRYPT_PAD_PKCS1_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptVerifySignature\n", secStatus);
        goto Cleanup;
    }

	wprintf(L"Success!\n");

Cleanup:

    if(hKey)
    {
        CryptDestroyKey(hKey);
    }

    if(hHash)   
    {
        CryptDestroyHash(hHash);
    }

    if(hProv)   
    {
        CryptReleaseContext(hProv, 0);
    }

    if (hCngHash)   
    {
        BCryptDestroyHash(hCngHash);   
    }

    if(hAlgorithm)  
    {
        BCryptCloseAlgorithmProvider(hAlgorithm,0);
    }

    if(hTmpKey)     
    {
        NCryptFreeObject(hTmpKey);
    }

    if(hProvider)   
    {
        NCryptFreeObject(hProvider);
    }

    //attempt to delete container
    CryptAcquireContext(
                    &hProv,
                    L"test",
                    MS_STRONG_PROV,
                    PROV_RSA_FULL,
                    CRYPT_DELETEKEYSET);

    if(pbHashObject)
    {
        HeapFree(GetProcessHeap(), 0, pbHashObject);
    }

    if(pbHash)
    {
        HeapFree(GetProcessHeap(), 0, pbHash);
    }

    if(pbSignature)
    {
        HeapFree(GetProcessHeap(), 0, pbSignature);
    }

    if(pbBlob)
    {
        HeapFree(GetProcessHeap(), 0, pbBlob);
    }
}

void SignWithCngVerifyWithCapi(void)
{
    NCRYPT_PROV_HANDLE          hProvider       = 0;
    NCRYPT_KEY_HANDLE           hKey            = 0;
    BCRYPT_ALG_HANDLE           hAlgorithm      = NULL;
    BCRYPT_HASH_HANDLE          hHash           = NULL;
    NTSTATUS                    Status          = STATUS_UNSUCCESSFUL;
    SECURITY_STATUS             secStatus       = ERROR_SUCCESS;
    DWORD                       cbHash          = 0,
                                cbData          = 0,
                                cbHashObject    = 0;
    PBYTE                       pbHashObject    = NULL;
    PBYTE                       pbHash          = NULL,
                                pbBlob          = NULL;
    PBYTE                       pbSignature     = NULL;
    DWORD                       cbSignature     = 0,
                                cbBlob          = 0;
    BCRYPT_PKCS1_PADDING_INFO   PKCS1PaddingInfo= {0};
    HCRYPTHASH                  hCapiHash       = 0;
    HCRYPTKEY                   hTmpKey         = 0;
    HCRYPTPROV                  hLocProv        = 0;


    if(FAILED(secStatus = NCryptOpenStorageProvider(
                                    &hProvider,
                                    KSP_NAME,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptOpenStorageProvider\n", secStatus);
        goto Cleanup;
    }

    if(FAILED(secStatus = NCryptCreatePersistedKey(
                                            hProvider,
                                            &hKey,
                                            NCRYPT_RSA_ALGORITHM,
                                            L"test",
                                            0,
                                            0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptCreatePersistedKey\n", secStatus);
        goto Cleanup;
    }


    if(FAILED(secStatus = NCryptFinalizeKey(hKey, 0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptFinalizeKey\n", secStatus);
        goto Cleanup;
    }

    //open alg provider handle
    if(!NT_SUCCESS(Status = BCryptOpenAlgorithmProvider(
                                                &hAlgorithm, 
                                                NCRYPT_SHA1_ALGORITHM, 
                                                NULL, 
                                                0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", Status);
        goto Cleanup;
    }


    if(!NT_SUCCESS(Status = BCryptGetProperty( 
                                        hAlgorithm, 
                                        BCRYPT_OBJECT_LENGTH,
                                        (PBYTE)&cbHashObject,
                                        sizeof(DWORD),
                                        &cbData, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", Status);
        goto Cleanup;
    }

    pbHashObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0,cbHashObject); 
    if(NULL == pbHashObject)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }


    //required size of hash?
    if(!NT_SUCCESS(Status = BCryptGetProperty( 
                                        hAlgorithm, 
                                        BCRYPT_HASH_LENGTH,
                                        (PBYTE)&cbHash,
                                        sizeof(DWORD),
                                        &cbData, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", Status);
        goto Cleanup;
    }

    pbHash = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHash); 
    if(NULL == pbHash)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    if(!NT_SUCCESS(Status = BCryptCreateHash(
                                    hAlgorithm, 
                                    &hHash, 
                                    pbHashObject, 
                                    cbHashObject, 
                                    NULL, 
                                    0, 
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptCreateHash\n", Status);
        goto Cleanup;
    }

    if(!NT_SUCCESS(Status = BCryptHashData(
                                        hHash,
                                        (PBYTE)KNOWN_DATA,
                                        KNOWN_DATALEN,
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptHashData\n", Status);
        goto Cleanup;
    }
  
    if(!NT_SUCCESS(Status = BCryptFinishHash(
                                        hHash, 
                                        pbHash, 
                                        cbHash, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptFinishHash\n", Status);
        goto Cleanup;
    }

    PKCS1PaddingInfo.pszAlgId = NCRYPT_SHA1_ALGORITHM;

    if(FAILED(secStatus = NCryptSignHash(
                                    hKey,
                                    &PKCS1PaddingInfo,
                                    pbHash,
                                    cbHash,
                                    NULL,
                                    0,
                                    &cbSignature,
                                    NCRYPT_PAD_PKCS1_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptSignHash\n", secStatus);
        goto Cleanup;
    }

    pbSignature = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbSignature); 
    if(NULL == pbSignature)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    if(FAILED(secStatus = NCryptSignHash(
                                    hKey,
                                    &PKCS1PaddingInfo,
                                    pbHash,
                                    cbHash,
                                    pbSignature,
                                    cbSignature,
                                    &cbSignature,
                                    NCRYPT_PAD_PKCS1_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptSignHash\n", secStatus);
        goto Cleanup;
    }
 

    if(FAILED(secStatus = NCryptExportKey(
                                    hKey,
                                    NULL,
                                    LEGACY_RSAPUBLIC_BLOB,
                                    NULL,
                                    NULL,
                                    0,
                                    &cbBlob,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptExportKey\n", secStatus);
        goto Cleanup;
    }
 

    pbBlob = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbBlob); 
    if(NULL == pbBlob)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }
  


    if(FAILED(secStatus = NCryptExportKey(
                                    hKey,
                                    NULL,
                                    LEGACY_RSAPUBLIC_BLOB,
                                    NULL,
                                    pbBlob,
                                    cbBlob,
                                    &cbBlob,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptExportKey\n", secStatus);
        goto Cleanup;
    }

    ReverseBytes(pbSignature, cbSignature);

    //temporarily import the key into a verify context container and decrypt
    if(!CryptAcquireContext(
                        &hLocProv,
                        NULL,
                        MS_ENH_RSA_AES_PROV,
                        PROV_RSA_AES,
                        CRYPT_VERIFYCONTEXT))
    {
        wprintf(L"**** Error 0x%x returned by CryptAcquireContext\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptImportKey(
                    hLocProv,
                    pbBlob,
                    cbBlob,
                    0,
                    0,
                    &hTmpKey))
    {
        wprintf(L"**** Error 0x%x returned by CryptImportKey\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptCreateHash(
		            hLocProv,
		            CALG_SHA1,
		            0,
                    0,
                    &hCapiHash))
    {
        wprintf(L"**** Error 0x%x returned by CryptCreateHash\n", GetLastError());
        goto Cleanup;
    }

   
    if(!CryptHashData(
		            hCapiHash,
		            (PBYTE)KNOWN_DATA,
		            KNOWN_DATALEN,
                    0))
    {
        wprintf(L"**** Error 0x%x returned by CryptHashData\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptVerifySignature(
                    hCapiHash, 
                    pbSignature, 
                    cbSignature, 
                    hTmpKey,
                    NULL, 
                    0))
    {
        wprintf(L"**** Error 0x%x returned by CryptVerifySignature\n", GetLastError());
        goto Cleanup;
    }

	wprintf(L"Success!\n");

Cleanup:

    if(hHash)       
    {
        BCryptDestroyHash(hHash);
    }

    if(hAlgorithm)  
    {
        BCryptCloseAlgorithmProvider(hAlgorithm,0);
    }

    if(hCapiHash)   
    {
        CryptDestroyHash(hCapiHash);
    }

    if(hTmpKey)     
    {
        CryptDestroyKey(hTmpKey);
    }

    if(hLocProv)    
    {
        CryptReleaseContext(hLocProv, 0);
    }

    if(hKey)        
    {
        NCryptDeleteKey(hKey, 0);
    }

    if(hProvider)   
    {
        NCryptFreeObject(hProvider);
    }

    if(pbHashObject)    
    {
        HeapFree(GetProcessHeap(), 0, pbHashObject);
    }

    if(pbHash)          
    {
        HeapFree(GetProcessHeap(), 0, pbHash);
    }

    if(pbSignature)     
    {
        HeapFree(GetProcessHeap(), 0, pbSignature);
    }

    if(pbBlob)          
    {
        HeapFree(GetProcessHeap(), 0, pbBlob);
    }


    return;
}


void EncryptWithCapiDecryptWithCng(void)
{
    HCRYPTKEY                   hKey            = 0;
    HCRYPTPROV                  hProv           = 0;
    PBYTE                       pbBlob          = NULL,
                                pbData          = NULL;
    DWORD                       cbBlob          = 0;
    NCRYPT_KEY_HANDLE           hTmpKey         = NULL;
    SECURITY_STATUS             secStatus       = ERROR_SUCCESS;
    DWORD                       cbData          = 0,
                                cbMsg           = 0,
                                cbResult        = 0;
    NCRYPT_PROV_HANDLE          hProvider       = 0;  

    if(!CryptAcquireContext(
                    &hProv,
                    L"test",
                    MS_STRONG_PROV,
                    PROV_RSA_FULL,
                    CRYPT_NEWKEYSET))
    {
        wprintf(L"**** Error 0x%x returned by CryptAcquireContext\n", GetLastError());
        goto Cleanup;
    }

    if(!CryptGenKey(
                hProv,
                AT_KEYEXCHANGE,
                CRYPT_EXPORTABLE,
                &hKey))
    {
        wprintf(L"**** Error 0x%x returned by CryptGenKey\n", GetLastError());
        goto Cleanup;
    }

    cbMsg = KNOWN_DATALEN;

    if(!CryptEncrypt(
                    hKey, 
                    0, 
                    TRUE, 
                    0, 
                    NULL, 
                    &cbMsg,
                    KNOWN_DATALEN))
    {
        wprintf(L"**** Error 0x%x returned by CryptEncrypt\n", GetLastError());
        goto Cleanup;
    }

    cbData = cbMsg;
    pbData = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbData);
    if(NULL == pbData)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    // Check to see if the allocated buffer is long enough
    if (cbData < KNOWN_DATALEN)
    {
        wprintf (L"*** KNOWN data length is longer than allocated data length\n");
        goto Cleanup;
    }

    //copy input data to buffer
    memcpy(pbData, (PBYTE) KNOWN_DATA, KNOWN_DATALEN);
    cbMsg = KNOWN_DATALEN;

    // Call CAPI1 to encrypt
    if(!CryptEncrypt(
                hKey,
                0,
                TRUE,
                0,
                pbData,
                &cbMsg,//size of data to be encrypted
                cbData))
    {
        wprintf(L"**** Error 0x%x returned by CryptEncrypt\n", GetLastError());
        goto Cleanup;
    }

    // Export the key from CAPI1: buffer length probe
    if(!CryptExportKey(
                    hKey,
                    0,
                    PRIVATEKEYBLOB,
                    0,
                    NULL,
                    &cbBlob))
    {
        wprintf(L"**** Error 0x%x returned by CryptExportKey\n", GetLastError());
        goto Cleanup;
    }

    // Allocate memory to export the key to
    pbBlob = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbBlob);
    if(NULL == pbBlob)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    // Export the key value to the allocated memory buffer
    if(!CryptExportKey(
                    hKey,
                    0,
                    PRIVATEKEYBLOB,
                    0,
                    pbBlob,
                    &cbBlob))
    {
        wprintf(L"**** Error 0x%x returned by CryptExportKey\n", GetLastError());
        goto Cleanup;
    }

    // CAPI1 returns the key bytes reversed.
    ReverseBytes(pbData, cbData);


    // Now it is time to import the exported CAPI1 key into CNG KSP ...
    // Open Microsoft KSP
    if(FAILED(secStatus = NCryptOpenStorageProvider(
                                            &hProvider, 
                                            KSP_NAME, 
                                            0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptOpenStorageProvider\n", secStatus);
        goto Cleanup;
    }


    // Set the property of this key: Legacy RSA private key blob
    if(FAILED(secStatus = NCryptImportKey(hProvider,
										NULL,
                                        LEGACY_RSAPRIVATE_BLOB,
										NULL,
										&hTmpKey,
                                        pbBlob,
                                        cbBlob,
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptImportKey\n", secStatus);
        goto Cleanup;
    }



    // Do in place decryption by providing the same pointers
    // to the input and output buffers (pbData, cbData) couple.
    if(FAILED(secStatus = NCryptDecrypt(
                                    hTmpKey,
                                    pbData,
                                    cbData,
                                    NULL,
                                    pbData,
                                    cbData,
                                    &cbResult,
                                    NCRYPT_PAD_PKCS1_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptDecrypt\n", secStatus);
        goto Cleanup;
    }

    if (0 != memcmp(pbData, (PBYTE)KNOWN_DATA, KNOWN_DATALEN)) 
    {
        wprintf(L"Expected decrypted text comparison failed");
        goto Cleanup;
    } 

	wprintf(L"Success!\n");

Cleanup:

    if(hKey)    
    {
        CryptDestroyKey(hKey);
    }

    if(hProv)   
    {
        CryptReleaseContext(hProv, 0);
    }

    if(pbBlob)   
    {
        HeapFree(GetProcessHeap(), 0, pbBlob);
    }

    if(pbData)   
    {
        HeapFree(GetProcessHeap(), 0, pbData);
    }

    if(hTmpKey)     
    {
        NCryptDeleteKey(hTmpKey, 0);
    }

    if(hProvider)  
    {
        NCryptFreeObject(hProvider);
    }

    //attempt to delete container
    CryptAcquireContext(
                    &hProv,
                    L"test",
                    MS_STRONG_PROV,
                    PROV_RSA_FULL,
                    CRYPT_DELETEKEYSET);
}


void EncryptWithMSCngDecryptWithESCng(void)
{
    NCRYPT_PROV_HANDLE          hProvider1       = 0;
	NCRYPT_PROV_HANDLE          hProvider2       = 0;
    NCRYPT_KEY_HANDLE           hKey            = 0;
    SECURITY_STATUS             secStatus       = ERROR_SUCCESS;
    DWORD                       cbOutput        = 0;
    PBYTE                       pbBlob          = NULL,
                                pbOutput        = NULL;
    DWORD                       cbBlob          = 0,
                                cbResult        = 0,
                                dwPolicy        = 0;
    HCRYPTKEY                   hTmpKey         = 0;


    if(FAILED(secStatus = NCryptOpenStorageProvider(
                                    &hProvider1,
                                    MS_KEY_STORAGE_PROVIDER,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptOpenStorageProvider\n", secStatus);
        goto Cleanup;
    }

	if(SUCCEEDED(secStatus = NCryptOpenKey(hProvider1, &hKey, L"test", 0, 0)))
	{
		NCryptDeleteKey(hKey, 0);
		hKey = 0;
	}

    if(FAILED(secStatus = NCryptCreatePersistedKey(
                                            hProvider1,
                                            &hKey,
                                            NCRYPT_RSA_ALGORITHM,
                                            L"test",
                                            0,
                                            0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptCreatePersistedKey\n", secStatus);
		goto Cleanup;
    }

    dwPolicy = NCRYPT_ALLOW_PLAINTEXT_EXPORT_FLAG;

    if(FAILED(secStatus = NCryptSetProperty(
                                    hKey, 
                                    NCRYPT_EXPORT_POLICY_PROPERTY,
                                    (PBYTE)&dwPolicy,
                                    sizeof(DWORD),
                                    NCRYPT_PERSIST_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptSetProperty\n", secStatus);
        goto Cleanup;
    }

            

    if(FAILED(secStatus = NCryptFinalizeKey(hKey, 0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptFinalizeKey\n", secStatus);
        goto Cleanup;
    }


    if(FAILED(secStatus = NCryptEncrypt(
                                    hKey,
                                    (PBYTE)KNOWN_DATA,
                                    KNOWN_DATALEN,
                                    NULL,
                                    NULL,
                                    0,
                                    &cbOutput,
                                    NCRYPT_PAD_PKCS1_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptEncrypt\n", secStatus);
        goto Cleanup;
    }

    pbOutput = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbOutput); 
    if(NULL == pbOutput)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }

    if(FAILED(secStatus = NCryptEncrypt(
                                    hKey,
                                    (PBYTE)KNOWN_DATA,
                                    KNOWN_DATALEN,
                                    NULL,
                                    pbOutput,
                                    cbOutput,
                                    &cbResult,
                                    NCRYPT_PAD_PKCS1_FLAG)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptSignHash\n", secStatus);
        goto Cleanup;
    }
 

    if(FAILED(secStatus = NCryptExportKey(
                                    hKey,
                                    NULL,
                                    BCRYPT_RSAFULLPRIVATE_BLOB,
                                    NULL,
                                    NULL,
                                    0,
                                    &cbBlob,
                                    0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptExportKey\n", secStatus);
        goto Cleanup;
    }
 

    pbBlob = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbBlob); 
    if(NULL == pbBlob)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;

    }
  


    if(FAILED(secStatus = NCryptExportKey(
								hKey,
								NULL,
								BCRYPT_RSAFULLPRIVATE_BLOB,
								NULL,
								pbBlob,
								cbBlob,
								&cbBlob,
								0)))
    {
        wprintf(L"**** Error 0x%x returned by NCryptExportKey\n", secStatus);
        goto Cleanup;
    }

    //temporarily import the key into a verify context container and decrypt
	if(FAILED(secStatus = NCryptOpenStorageProvider(
		&hProvider2,
		KSP_NAME,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by NCryptOpenStorageProvider\n", secStatus);
		goto Cleanup;
	}


	// Set the property of this key: Legacy RSA private key blob
	if(FAILED(secStatus = NCryptImportKey(hProvider2,
		NULL,
		BCRYPT_RSAFULLPRIVATE_BLOB,
		NULL,
		&hTmpKey,
		pbBlob,
		cbBlob,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by NCryptImportKey\n", secStatus);
		goto Cleanup;
	}



	// Do in place decryption by providing the same pointers
	// to the input and output buffers (pbData, cbData) couple.
	if(FAILED(secStatus = NCryptDecrypt(
		hTmpKey,
		pbOutput,
		cbOutput,
		NULL,
		pbOutput,
		cbOutput,
		&cbResult,
		NCRYPT_PAD_PKCS1_FLAG)))
	{
		wprintf(L"**** Error 0x%x returned by NCryptDecrypt\n", secStatus);
		goto Cleanup;
	}

    if (0 != memcmp(pbOutput, (PBYTE)KNOWN_DATA, KNOWN_DATALEN)) 
    {
        wprintf(L"Expected decrypted text comparison failed");
        goto Cleanup;
    } 

	wprintf(L"Success!\n");

Cleanup:

    if(hTmpKey)     
    {
        NCryptDeleteKey(hTmpKey, 0);
    }

    if(hProvider2)    
    {
        NCryptFreeObject(hProvider2);
    }

    if(hKey)        
    {
        NCryptDeleteKey(hKey, 0);
    }

    if(hProvider1)   
    {
        NCryptFreeObject(hProvider1);
    }

    if(pbOutput)    
    {
        HeapFree(GetProcessHeap(), 0, pbOutput);
    }

    if(pbBlob)      
    {
        HeapFree(GetProcessHeap(), 0, pbBlob);
    }


    return;
}

void __cdecl wmain( int argc, 
                   __in_ecount(argc) LPWSTR    *wargv) 
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(wargv);


    wprintf(L"1) EncryptWithMSCngDecryptWithESCng\n");
    EncryptWithMSCngDecryptWithESCng();
 
    wprintf(L"2) EncryptWithCapiDecryptWithCng\n");
    EncryptWithCapiDecryptWithCng();
 
    wprintf(L"3) SignWithCngVerifyWithCapi\n");
    SignWithCngVerifyWithCapi();

    wprintf(L"4) SignWithCapiVerifyWithCng\n");
    SignWithCapiVerifyWithCng();
}
