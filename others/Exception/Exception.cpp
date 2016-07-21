// Exception.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "exception.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		int a, b ;
		puts("input a, b:");
		scanf("%d%d", &a, &b);
		if(!b)
			throw ClientException("异常");
	}
	catch(exception &ex)
	{
		printf("%s\n", ex.what());
	}
	return 0;
}

