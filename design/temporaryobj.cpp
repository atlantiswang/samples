#include <stdio.h>

class temp{
public:
	explicit temp(int param = 0)
	{
		puts("construct");
	}
	temp(const temp &other)
	{
		this->m_ = other.m_;
		puts("copy construct");
	}
	temp& operator = (const temp &other)
	{
		this->m_ = other.m_;
		return *this;
		puts("assign");
	}
	~temp()
	{
		puts("destruct");
	}
private:
	int m_;
};

//temporary object one
void test(temp &t)//(test t)
{
	puts("test for object one");
}
//temporary object two

/* if use the & ,which to reffer? if the input param don't want?
   so use the var define in function. but the & can't reffer a var temporary.
   so the temporary ojbect must have(for a,some compiler can ignore), the onlythine
   can optimize is to define the object when invoke the function. so can combine this invoke.
   like temp t = test_r(t1);
   */
temp test_r(temp &t)
{
	temp a;
	return a;
}


int main()
{
	temp t1;
/*	temp t2(t1); 
	temp t3;
	t3 = t2;*/
	
//	test(t1);
//	test_r(t1);

/*  temporary object three
	temp t2;
	t2 = 13;
	solution:
	temp t2 = 13; when explicit declare ahead, this can't complile.
	so use temp t2(13) instead.
	*/
	temp t2(13);
	
	getchar();
	return 0;
}