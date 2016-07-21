#pragma once

#include "openssl/bio.h"
#include "openssl/asn1.h"
#include "openssl/x509v3.h"
#include "openssl/err.h"
#include "openssl/pem.h"


#include "struct.h"


EVP_PKEY *SKFToOpenSSL(PRSAPUBLICKEYBLOB pSKFKey);
PRSAPUBLICKEYBLOB OpenSSLToSKF();
int OpenSSL_Verify(EVP_PKEY *pPubKey, 
				   unsigned char *data, int data_cb, 
				   unsigned char* sign, unsigned int sign_cb);
