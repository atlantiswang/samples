/*
	前置声明：
	前置声明个人感觉用来解决互相指向的问题。比如foo1中有foo2;foo2中双有foo1。这时候无论把谁放在前面都不能通过编译。
	解决方法：
	将其中一个比如foo2设置成前置声明。foo1中改为foo2的指针或引用 且 foo1中只先做声明， 不做定义。这样foo1就能过了。
	然后foo2中就有两种选择：第一种把foo1的声明放上头，就可以直接定义foo2了。第二种，把foo1的前置声明放前头，然后跟
	写foo1的声明或引用。定义分开写。

	总之：
	使用了前置声明，就要改为指针或引用 ，并将声明与定义分开。

	方法就是，把foo1、foo2的声明与定义分开，
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