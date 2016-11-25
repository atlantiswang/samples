#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/bio.h>
#include <openssl/lhash.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/ossl_typ.h>
#include "function.h"

bool verify_init(SSL_CTX *ctx)
{
	if (SSL_CTX_use_certificate_file(ctx, "D:/test/solution/console/sslsocket/bin/server_bak.crt", SSL_FILETYPE_PEM) <=0 )
	{
		ERR_print_errors_fp(stderr);
		exit(3);
	}
	if (SSL_CTX_use_PrivateKey_file(ctx, "D:/test/solution/console/sslsocket/bin/server_nosecure_bak.key", SSL_FILETYPE_PEM) <=0 )
	{
		ERR_print_errors_fp(stderr);
		exit(3);
	}
	if (!SSL_CTX_check_private_key(ctx))
	{
		fprintf(stderr, "Private key does not match the certificate public key\n");
		exit(5);
	}
	return true;
}

