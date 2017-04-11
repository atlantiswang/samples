/*
 *	单例模式是解决全局对象的创建的问题， 工厂模式是解决局部对象的创建问题
	由于我们在创建对象的时候不仅仅要考虑到创建出对象，还有创建时的一些初始化的操作，而仅仅依靠构造函数进行初始化又不够，也不
	符合面向对象的设计理念，故各种类有自己额外的一些函数在对象创建时被调用，为了方便统一，使用工厂模式（而不是像《C++设计模式》
	中那样描述的原因）
 */

#include <stdlib.h>
#include <iostream>
using namespace std;

class student
{
public:
	student(){}
	//初始化一般的学生
	void initstudent()
	{
		m_age = 18;
		strcpy(m_szname, "student");
	}
	//初始化大学生
	void initcollege()
	{
		m_age = 20;
		strcpy(m_szname, "college");
	}
	void print()
	{
		cout<<"age "<<m_age<<endl<<"name "<<m_szname<<endl;
	}
private:
	int m_age;
	char m_szname[128];
};

class people
{
public:
	void initpeople()
	{
		//默认为男性
		m_bman = true;
	}
public:
	void print()
	{
		cout<<"people's sex "<<(m_bman?("male"):("famale"))<<endl;
	}
private:
	bool m_bman;
};


class factory
{
public:
	student *createstudent()
	{
		student *pstu =
		new student();
		pstu->initstudent();
		return pstu;
	}
	student *createcollege()
	{
		student *pstu = new student();
		pstu->initcollege();
		return pstu;
	}
	people *createpeople()
	{
		people *ppel = new people();
		ppel->initpeople();
		return ppel;
	}

};

int main()
{
	factory fc;
	fc.createstudent()->print();
	fc.createcollege()->print();
	fc.createpeople()->print();
	system("pause");
	return 0;
}