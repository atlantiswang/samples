// auto_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <string>
#include "auto_ptr_array.h"
using std::cout;
using std::endl;

class People
{
public:
	People(const std::string &name = "default", int age = -1):
	  name (name), age(age)
	{
		cout<<"name:"<<name<<endl
			<<"age:"<<age<<endl;
	}

	~People()
	{
		cout<<"People destruct invoke"<<endl;
	}

private:
	std::string name;
	int age;
};

void test_ptr()
{
	//原始的方式会造成内存泄露
	//People *ptr_old = new People;

	//使用auto_ptr，在测试函数调用完后会释放（构造函数被调用）
	std::auto_ptr<People> ptr_auto(new People("wanghao", 26));
	auto_array<People> ptr_auto_array(new People[3]);

	//由于auto_ptr没有提供数组指针，所以靠我们自己做一个
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_ptr();

	system("pause");
	return 0;
}

