#pragma once

class MyClass
{
public:
	MyClass(void);
	~MyClass(void);
public:
	static int m_mem1;
	static MyClass& BuildOjbect();
};
