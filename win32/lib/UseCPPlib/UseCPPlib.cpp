//为什么C++的文件中一定要有函数的声明？
//就是因为C++编译器有两种编译方式，必须得注明
//用不用extern "C"，用不用换名编译
#include "stdio.h"
//C++的名字一样，不用加extern "C"
int CPPlib_add(int add1,int add2);
int CPPlib_sub(int sub1,int sub2);
//C语言写的与C++中的函数名字不一样，为了一致加extern "C"
extern "C" int Clib_add(int add1,int add2);
extern "C" int Clib_sub(int sub1,int sub2);
//编译器看的
#pragma comment(lib,"../lib/CPPlib.lib")
#pragma comment(lib,"../lib/Clib.lib")
//链接器看的
int main()
{
	int sum = CPPlib_add(5,4);
	int sub = CPPlib_sub(5,4);
	printf("sum=%d,sub=%d\n",sum,sub);
	
	sum = Clib_add(5,3);
	sub = Clib_sub(5,3);
	printf("sum = %d,sub = %d\n",sum,sub);
	return 0;
}