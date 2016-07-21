#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cstring>
#include "d:\\openssl\\include\\openssl\\bn.h"
//使用第三方库时运行时库要一致
#pragma comment (lib, "D:\\OpenSSL\\Lib\\libeay32.lib")
#pragma comment (lib, "D:\\OpenSSL\\Lib\\ssleay32.lib")
/*
 * p:3 q:11两个质数 n = 3*11 = 33

 * fai n = (p-1)*(q-1) = 20

 * e = 17(1<3<fai n的一个质数) 

 * d: e(17)关于 fai n(20)的模反元素,即 17*d + 20y = 1,取d为13 y = -60

 * encrypt：c = num.pow(e)%n | decrypt：num = c.pow(d)%n
 */
//此程序由于N设置的为33，故只能加密小于33的数据

#define N	33
#define PRIMER_P 3
#define PRIMER_Q 11
#define E 17
#define D 13

BIGNUM *encrypt(BIGNUM *pplain)
{
	BN_CTX *pcontext = BN_CTX_new();
	BN_CTX_init(pcontext);
	BIGNUM *pc = BN_new();
	BN_init(pc);

	BIGNUM *pn = BN_new();
	BN_dec2bn(&pn, "33");
	BIGNUM *pt = BN_new();
	BN_init(pt);
	BN_copy(pt, pplain);
	for(int i = 0; i < E - 1; i++)
		BN_mul(pt, pt, pplain, pcontext);
	BN_mod(pc, pt, pn, pcontext);
	BN_free(pt);
	BN_free(pn);
	BN_CTX_free(pcontext);
	return pc;
}

BIGNUM *decrypt(BIGNUM *pc)
{
	BN_CTX *pcontext = BN_CTX_new();
	BN_CTX_init(pcontext);
	BIGNUM *pplain = BN_new();
	BN_init(pplain);

	BIGNUM *pn = BN_new();
	BN_dec2bn(&pn, "33");
	BIGNUM *pt = BN_new();
	BN_init(pt);
	BN_copy(pt, pc);
	for(int i = 0; i < D - 1; i++)
		BN_mul(pt, pt, pc, pcontext);
	BN_mod(pplain, pt, pn, pcontext);

	BN_free(pt);
	BN_free(pn);
	BN_CTX_free(pcontext);
	return pplain;
}

int main()
{
	BIGNUM *pp = BN_new();
	BIGNUM *pq = BN_new();
	
	BN_dec2bn(&pp, "3");
	BN_dec2bn(&pq, "11");
	char num[128] = {0};
	while(1)
	{
		puts("select the operation: 1 for encrypt, others for decrypt");
		char csign = getchar();
		puts("input the num:");
		scanf("%s", num);
		BIGNUM *pplain = BN_new();
		BN_dec2bn(&pplain, num);

		BIGNUM *pc = BN_new();
		if('1' == csign)
			pc = encrypt(pplain);
		else 
			pc = decrypt(pplain);
		printf("the c is:%s\n",BN_bn2dec(pc));
		BN_free(pc);
		BN_free(pplain);
		getchar();
	}
	
	BN_free(pp);
	BN_free(pq);
	system("pause");
	return 0;
}