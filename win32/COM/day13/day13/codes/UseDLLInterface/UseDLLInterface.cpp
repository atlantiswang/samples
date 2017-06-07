// UseDLLInterface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../DLLInterface/math.h"
//定义函数指针类型
typedef IMath*(*INSTANCE)();
IMath* GetMath()
{
	//1 加载dll
	HMODULE hDll=LoadLibrary("DLLInterface.dll");
	//2 获取导出函数的函数地址
	INSTANCE Instance=(INSTANCE)
		GetProcAddress(hDll,"CreateInstance");
	//3 调用导出函数
	IMath *pMath=Instance();
	return pMath;
} 
int main(int argc, char* argv[])
{
	IMath *pMath=GetMath();
    //使用接口前
	pMath->AddRef();
	int nAdd=pMath->Add(100,100);
	//多次使用该接口...

	//使用接口后
	pMath->Release();
	printf("nAdd=%d\n",nAdd);
    //删除对象
	//delete pMath;
	getchar();
	return 0;
}

