/*
	前置声明：
	
	使用前置声明的目的：
	*避免了使用#include包含头文件，
	从而
	1. 不会造成文件编译依赖性(还有一种防止编译依赖的方法是PIMPL)
	2. 在两个类相互引用对方类的情况下，解决使用#include包含不能编译通过
	
	1.
	类A声明在 a.h a.cpp中。类B声明在 b.h b.cpp中，如果使用B中有A的实例做为成员，则一般情况下需要使用#include"a.h"进行包含，这样就造成了编译依赖性。
	所以我们完成可以不使用#include"a.h",只使用前置声明class A;即可，但要如果类B中使用" A m_a;"来写。就不会通过编译。因为这种写法要知道A的类型的大小，
	而前置声明的方法是只提供接口，不提供定义。故我们无法知道A的大小。但可以使用 A *m_pa;或 A &m_a;来写这个成员变量。
	
	2.
	比如foo1中有foo2;foo2中双有foo1。这时候无论把谁放在前面都不能通过编译。
	解决方法：
	将其中一个比如foo2设置成前置声明。foo1中改为foo2的指针或引用 且 foo1中只先做声明， 不做定义。这样foo1就能过了。
	然后foo2中就有两种选择：第一种把foo1的声明放上头，就可以直接定义foo2了。第二种，把foo1的前置声明放前头，然后跟
	写foo1的声明或引用。定义分开写。

	.还有一点需要注意，在声明一个函数的时候，不管这个函数的返回值还是参数，即便是定义式，也可以使用前置声明就可以了，这一点与类B的成员不一样。
*/

struct foo2;

struct foo1
{
	void fun(const foo2&);
private:
	foo2* m_pfoo2;
};

struct foo2
{
	foo1 val;
	void bar(const foo2&);
};


void foo1::fun(const foo2& temp)
{
	m_pfoo2->bar(temp);
}

void foo2::bar(const foo2&)
{
	;
}



int main(void)
{
	return 0;
}
