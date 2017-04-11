#include "stdio.h"

//这里的名字是cpp里的名字，不是.def里的名字
_declspec(dllimport)int CPPdll_add(int add1,int add2);
_declspec(dllimport)int CPPdll_sub(int sub1,int sub2);
_declspec(dllimport)int CPPdll_sub(int sub1,int sub2,int sub3);

//.lib文件里存的是定义时的函数名与导出的实际函数名的对照表
#pragma comment(lib,"../lib/CPPdll.lib")
int main()
{
	int sum = CPPdll_add(5,3);
	int sub = CPPdll_sub(5,3);
	int sub2 = CPPdll_sub(5, 3, 1);
	printf("sum=%d,sub=%d,sub2=%d\n",sum,sub,sub2);
	return 0;
}