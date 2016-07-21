#include "StdAfx.h"
#include "MyClass.h"

MyClass& MyClass::BuildOjbect()
{
	// By creating theMap here, C++ doesn't instantiate it until/unless
	// it's ever used! This is a good trick to use in C++, to
	// instantiate/initialize a static object the first time it's used.
	//
	static MyClass theMyClass;
	return theMyClass;
}
int MyClass::m_mem1 = 0;

MyClass::MyClass(void)
{
}

MyClass::~MyClass(void)
{
}
