/*
 《effective stl》条款7
  stl容器中如果保存指针，需要手动释放，如果使用for循环，不是太方便，可以使用for_each,但for_each的使用需要注意
  一些问题...
 */
 
#include <vector>
#include <algorithm>
#include <vld.h>
using namespace std;

/*
	如果T类型是继承而来的，容易出现问题（base class 未声明析构函数为虚函数，传入的类型又是父类）。
	故可以将模板化后延。
	但仍然有异常安全问题。这个可以使用智能指针代替。
	unary_function指明 operator()只有一个参数
	第一个参数是Operator()的第一个参数，第二个参数是其返回值类型。
	使用unary_function是为了能使用函数甜酸器(notl, not2, bind1st, bind2nd)
 */

//C++ 仿函数
 //template<typename T>
 struct deleteobj //条款40描述了为什么 这里有个继承
	// :public unary_function<const T*, void>
 {
	 //将模板化加在这里
	 template<typename T>
	 void operator() (const T* ptr) const
	 {
		 delete ptr;
	 }
 };
 
 class people
 {};

 int main()
 {
	people *p;
	std::vector<people*> temp;
	for (int i = 0; i < 10; i++)
	{
		p = new people;
		temp.push_back(p);
	}
	//使用for_each比 for循环要方便
	for_each(temp.begin(), temp.end(), deleteobj());
	 
	return 0;
 }