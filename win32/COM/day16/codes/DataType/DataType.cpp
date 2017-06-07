// DataType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>//Win32平台
#include <atlbase.h>//ATL库
#include <comdef.h>//C++库
void TestBSTR()
{
    // 1 创建字符串
	BSTR bstr=SysAllocString(L"Hello");
	// 2 调用接口函数...，使用字符串

	// 3 使用完成后，释放
	SysFreeString(bstr);
	CComBSTR bstr2("Hello");
	bstr2.Length();
	_bstr_t bstr3("Hello");
	bstr3.length();

}
void TestVariant()
{
    //使用VARIANT表示整数(long)100
	VARIANT varInt={0};
	varInt.lVal=100;
	varInt.vt=VT_I4;
    //使用VARIANT表示指向一个long型的指针
	VARIANT varIntPtr={0};
	long nValue=0;
	varIntPtr.plVal=&nValue;
	varIntPtr.vt=VT_BYREF|VT_I4;
	//使用对应的封装类
	CComVariant varInt2(100);
	_variant_t varInt3((long)100);


}
void TestSafeArray()
{
	//1 定义数组的维信息
	SAFEARRAYBOUND bound[2];
	bound[0].cElements=10;
	bound[0].lLbound=0;
	bound[1].cElements=10;
	bound[1].lLbound=0;
	//2 创建安全数组
	SAFEARRAY *pArray=SafeArrayCreate(VT_I4,2,bound);
	//3 赋值
	for (long i=0;i<10;i++)
	{
		for (long j=0;j<10;j++)
		{
			long nValue=i*10+j;
			long nIndices[2]={i,j};//元素的位置
			SafeArrayPutElement(pArray,nIndices,&nValue);
		}
	}
	//4 取值
	for (i=0;i<10;i++)
	{
		for (long j=0;j<10;j++)
		{
			long nValue=0;//使用该变量保存从数组中取出的值
            long nIndices[2]={i,j};
			SafeArrayGetElement(pArray,nIndices,&nValue);
			printf("%02d  ",nValue);
		}
		printf("\n");
	}
	//5 释放
	SafeArrayDestroy(pArray);


}
int main(int argc, char* argv[])
{
	TestBSTR();
	TestSafeArray();
	printf("Hello World!\n");
	return 0;
}

