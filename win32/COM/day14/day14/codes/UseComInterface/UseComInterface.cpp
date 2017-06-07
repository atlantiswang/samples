// UseComInterface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../COMInterface/math.h"
typedef IMath*(*INSTANCE)();
IMath* GetMath()
{
	//加载dll
	HMODULE hDll=LoadLibrary("ComInterface.dll");
	//获取导出函数的函数地址
	INSTANCE Instance=(INSTANCE)
		GetProcAddress(hDll,"CreateInstance");
	//调用该函数
	IMath *piMath=Instance();
	return piMath;
}
int main(int argc, char* argv[])
{
	IMath *piMath=GetMath();
	int nAdd=0;//保存计算结果
	piMath->Add(100,100,&nAdd);
	//接口使用后
	piMath->Release();
	printf("nAdd=%d\n",nAdd);
	getchar();
	return 0;
}

