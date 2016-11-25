// sslsocket.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <winnt.h>
#include "stdlib.h"
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

#pragma comment(lib, "ws2_32.lib")
#include "pthread.h"
#include "function.h"

#define MYIP "10.0.2.20"
#define MYPORT 8089
#define MFDSET(m, fd, fds) \
	do { if( (fd) >= 0 ) { FD_SET((fd),(fds)); m = m < (fd) ? (fd) : (m) ; } } while (0)

static pthread_mutex_t *lock_cs;
static long *lock_count;

static pthread_mutex_t *transf_lock_cs;
static long *transf_lock_count;


pthread_t transf_pthreads_thread_id(void)
{
	pthread_t ret;
	ret = pthread_self();
	return(ret);
}

void  transf_client_locking_callback(int mode, int type, const char *file, int line)
{
	if (mode & CRYPTO_LOCK)
	{
		pthread_mutex_lock(&(transf_lock_cs[type]));
		transf_lock_count[type]++;
	}
	else
	{
		pthread_mutex_unlock(&(transf_lock_cs[type]));
	}

}

void  * tcp_forwardlistenthread(void * pParam)
{
	SSL_CTX *ctx = (SSL_CTX *)pParam;
	SSL *ssl = NULL;
	ssl = SSL_new(ctx);
	if (ssl == NULL) exit(-1);
	SOCKET socket1 = socket(AF_INET, SOCK_STREAM, 0);
	if (socket1 < 0) exit(-1);
	struct sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = inet_addr(MYIP);
	service.sin_port = htons(MYPORT);
	if (connect (socket1, (struct sockaddr*)&service, sizeof(service)) == -1) exit(-1);
	SSL_set_fd(ssl, socket1);
	int sslResult = SSL_connect(ssl);
	if (!SSL_is_init_finished(ssl)) exit(-1);

	char buff[1024] = {0};
	scanf("%s", buff);
	SSL_write(ssl, buff, 1024);

	fd_set fds_bak,fds;
	FD_ZERO(&fds_bak);
	int m = 0;
	MFDSET(m, socket1, &fds_bak);
	while(true)
	{
		fds = fds_bak;
		int ret = select(m+1, &fds, NULL, NULL, NULL);
		if (ret == 0) 
		{
			puts("time out");
			goto _exit;
		}
		if (ret < 0)
		{
			puts("getlasterr");
			goto _exit;
		}
		if (socket1 >0 && FD_ISSET(socket1, &fds))
		{
			SSL_read(ssl, buff, 1024);
			puts(buff);
			scanf("%s", buff);
			SSL_write(ssl, buff, strlen(buff)+1);
		}
	}
	getchar();
_exit:
	closesocket(socket1);
	SSL_shutdown(ssl);
	SSL_free(ssl);
}

int verify_callback_server(int ok, X509_STORE_CTX *ctx)
{
	printf("verify_callback_server \n");
	return ok;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData = {0};
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SSLeay_add_all_algorithms();
	pthread_t pid;
	
	ERR_load_BIO_strings();
	SSL_library_init(); 
	SSL_load_error_strings();

	SSL *ssl = NULL;
	SSL_CTX *ctx = NULL;
	//这里要注意是client
	ctx = SSL_CTX_new(TLSv1_client_method());
	if (ctx == NULL)
	{
		printf("ssl ctx new eer\n");
		exit(-1);
	}

	transf_lock_cs = (pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
	transf_lock_count = (long *)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(long));
	for (int i = 0; i < CRYPTO_num_locks(); i++)
	{
		transf_lock_count[i] = 0;
		pthread_mutex_init(&(transf_lock_cs[i]), NULL);
	}
	CRYPTO_set_id_callback((unsigned long(*)())transf_pthreads_thread_id);
	CRYPTO_set_locking_callback(transf_client_locking_callback);
	pthread_create(&pid, NULL, tcp_forwardlistenthread, ctx);

	pthread_join(pid, NULL);
	system("pause");
	getchar();
	SSL_CTX_free(ctx);
	WSACleanup();
	return 0;
}

