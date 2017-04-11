/*
 * 1 需要提供一个创建的接口， 不能用类型-对象的方法创建，所以构造函数不能是公有的
 * 2 需要提供一种获取单例的方法。在全局都能使用，故可以使用类的静态成员的方式去创建和获取这个单例

 * 3 使用单例模式获取实例的原因：只有一个实例并且这个实例易于被访问
	 还有一个原因，在effective c++中有介绍：确保类对象的创建时机，因为全局对象创建有时候要有一定的次序，但全局对象的创建方式却没有
	 这种能力，故可以使用单例模式（具体可以去effective c++中查看）
 */

#include <stdlib.h>
#include <iostream>
using namespace std;

class single
{
	//如果使用全局函数的方式，就要声明为友员，以便能调用构造函数
	friend single getinstance();
	//friend single* getinstance();
private:
	single() {}
public:
	//这个地方不一定要使用类的静态函数的方式，因为我们需要条件2，故全局函数也可以实现
#if 0
	static single* getinstance()
	{
		static single* m_pinstance;
		if (m_pinstance == NULL)//这个是第一次调用，需要创建
		{
			m_pinstance = new single();
		}
		return m_pinstance;
	}
#endif
	void fun()
	{
		cout<<"fun invoke"<<endl;
	}
};

#if 0
single* getinstance()
{
	//也可以不使用指针的方式来获取这个单例，直接用对象也可以
	static single *pinstance;
	if(pinstance == NULL) pinstance = new single();
	return pinstance;
}
#endif

single getinstance()
{
	//也可以不使用指针的方式来获取这个单例，直接用对象也可以
	static single pinstance;
	return pinstance;
}

int main()
{
	//single::getinstance()->fun();
	//getinstance()->fun();
	getinstance().fun();
	system("pause");
	return 0;
}