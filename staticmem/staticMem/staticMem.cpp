// staticMem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyClass.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//静态成员 刚开始就被初始化
	printf("static m_mem1 = %d\n", MyClass::m_mem1);
	//对象 只到此时才被初始化。
	MyClass::BuildOjbect().m_mem1 += 1;
	printf("static m_mem1 = %d\n", MyClass::m_mem1);

	return 0;
}

