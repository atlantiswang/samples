// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HMACTest.h"


int main(int argc, char* argv[])
{
	cout<<"[]==================================================[]"<<endl;
	cout<<" |             Hmac PKCS#11 Demo               |"<<endl;				
	cout<<"[]==================================================[]"<<endl;
	HmacTest test;
	test.Test();
	return 0;
}