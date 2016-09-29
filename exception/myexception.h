//常见的异常类
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>
using namespace std;

/*
 * exception C++标准的异常类
 * mem: int m_doFree ;const char *m_what
 * 四个构造函数
 * 一个析构函数 virtual
 * 一个what()函数,子类通过重写的方式可以访问到子类扩展的成员
 * virtual const char * __CLR_OR_THIS_CALL what() const;
 
 how to use C++ exception:
 first: create a myexception header file myexception.h
	use #include <exception> to include stdanddard exception.
 second: write my own exception class inherit from exception.
 third: when you need throw or cath exception in you cpp file. include the myexception.h
 over.
 -------------------------------------------------------------------
 
 * 在windows下还有结构化异常（SEH），也支持C/C++，但不是C++标准异常的子集或父集：
   SEH :__try __except (异常处理)| __try __finally & __leave(结束处理)
   但由于是MicroSoft的，所以不具有移植性。
 */
//客户端异常类 由于本异常类没有使用到exception的成员的作用。故可以不继承自exception
class ClientException : public exception
{
private:
	string m_msg;
public:
	//无论是无参构造还是有参构造都没有指明调用父类的哪个构造函数，所以会调用父类的
	//默认构造函数
	ClientException(void):m_msg("客户机异常!"){}
	ClientException(const string& msg):m_msg("客户机异常:")
	{
		m_msg += msg;
		m_msg += "!";
	}
	//与exception类中析构函数的异常说明保持一致
	//此函数一定不抛出任何异常
	~ClientException() throw(){}

	//由于此函数为虚函数，所以只要是多态方式调用。最终都后调用此函数
	const char* what() const throw()
	{
		//将string转换为C风格字符串
		return m_msg.c_str();
	}
};

//备份异常类
class BackupException : public ClientException
{
public:
	//前面都会加一句：客户机异常，然后默认“备份异常”如果带参。就改为参数内容
	BackupException(void):ClientException("备份异常"){}
	BackupException(const string& msg):ClientException(msg){}
};

//网络异常类
class SocketException : public ClientException
{
public:
	SocketException(void):ClientException("网络异常"){}
	SocketException(const string& msg):ClientException(msg){}
};

//读取异常类
class ReadException : public ClientException
{
public:
	ReadException(void):ClientException("读取异常"){}
	ReadException(const string& msg):ClientException(msg){}
};

//发送异常类
class SendException : public ClientException
{
public:
	SendException(void):ClientException("发送异常"){}
	SendException(const string& msg):ClientException(msg){}
};

//存储异常类
class SaveException : public ClientException
{
public:
	SaveException(void):ClientException("存储异常"){}
	SaveException(const string& msg):ClientException(msg){}
};

#endif
