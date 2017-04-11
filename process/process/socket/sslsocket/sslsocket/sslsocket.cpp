// sslsocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

void* thread_main(void *param)
{
	int err;
	SSL *ssl = (SSL*)param;
	SOCKET s1 = SSL_get_fd(ssl);
	err = SSL_accept(ssl);
	if (err < 0 )
	{
		puts("ssl accept err");
		goto _exit;
	}
	fd_set rady_fds,fds;
	FD_ZERO(&rady_fds);
	int m = 0;
	MFDSET(m, s1, &rady_fds);
	while(true)
	{
		fds = rady_fds;
		int ret = select(m+1, &fds, NULL, NULL, NULL);
		if (ret == 0)
		{
			puts("time out");
			goto _exit;
		}
		if(ret < 0)
		{
			puts("getlasterror");
			goto _exit;
		}
		if (s1 > 0 && FD_ISSET(s1, &fds))
		{
			char buff[1024] = {0};
			SSL_read(ssl, buff, 1024);
			puts(buff);
			scanf("%s", buff);
			SSL_write(ssl, buff, strlen(buff)+1);
		}
	}
_exit:
	closesocket(s1);
	SSL_shutdown(ssl);
	SSL_free(ssl);
	return NULL;
}

pthread_t pthreads_thread_id(void)
{
	pthread_t ret;
	ret = pthread_self();
	return(ret);
}

void  pthreads_locking_callback(int mode, int type, const char *file, int line)
{
	if (mode & CRYPTO_LOCK)
	{
		pthread_mutex_lock(&(lock_cs[type]));
		lock_count[type]++;
	}
	else
	{
		pthread_mutex_unlock(&(lock_cs[type]));
	}

}


int verify_callback_server(int ok, X509_STORE_CTX *ctx)
{
	printf("verify_callback_server \n");
	return ok;
}
unsigned long a = 4;
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData = {0};
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SSLeay_add_all_algorithms();
	SSL_load_error_strings();
	SSL_library_init(); 


	SSL_CTX *ctx;
	SSL *ssl = NULL;
	const SSL_METHOD *meth;
	meth = TLSv1_server_method();
	ctx = SSL_CTX_new(meth);
	if (!ctx)
	{
		ERR_print_errors_fp(stderr);
	}
	verify_init(ctx);

	static int s_server_verify = SSL_VERIFY_PEER  | SSL_VERIFY_CLIENT_ONCE;
	SSL_CTX_set_verify(ctx, s_server_verify, verify_callback_server);

	SOCKET fd,acceptSocket;
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == -1) exit(-1);
	SOCKADDR_IN svrAddr = {0};
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_addr.s_addr = ADDR_ANY;
	svrAddr.sin_port = htons(MYPORT);
	if(SOCKET_ERROR == bind(fd, (const sockaddr*)&svrAddr, sizeof(svrAddr))) exit(-1);
	if (SOCKET_ERROR == listen(fd, SOMAXCONN)) exit(-1);

	lock_cs = (pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
	lock_count = (long *)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(long));

	for (int i = 0; i < CRYPTO_num_locks(); i++)
	{
		lock_count[i] = 0;
		pthread_mutex_init(&(lock_cs[i]), NULL);
	}

	CRYPTO_set_id_callback((unsigned long(*)())pthreads_thread_id);
	CRYPTO_set_locking_callback(pthreads_locking_callback);

	pthread_t pid;
	fd_set myset;
	int m = 0,err;
	while (true)
	{
		FD_ZERO(&myset);
		MFDSET(m ,fd, &myset);
		int ret = select(m + 1, &myset, NULL, NULL, NULL);
		if (ret == 0)
		{
			puts("time out");
		}
		if (ret < 0)
		{
			puts("getlasterror");
		}
		if (fd>0 && FD_ISSET(fd, &myset))
		{
			SOCKET acceptSocket = accept(fd, NULL, NULL);
			ssl = SSL_new(ctx);
			err = SSL_set_fd(ssl, acceptSocket);
			err = pthread_create(&pid, NULL, &thread_main, (void *)ssl);
			pthread_detach(pid);
		}
	}
	
	system("pause");
	getchar();
	SSL_CTX_free(ctx);
	closesocket(fd);
	WSACleanup();
	return 0;
}

