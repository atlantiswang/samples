#ifndef Bigint_H
#define Bigint_H

/*
  
 * 1 不需要暴露的接口声明为 private, 需要暴露的接口声明为 public(接口)
 
 * 2 如果一个函数不需要访问private成员。则可以设置成no-mem、no-friend函数。如果需要访问Private成员
 	 设置为成员函数或 非成员friend函数对封装性的影响是一样的。所以没有必要设置为非成员函数
 
 * 3 经验：再次计算的时候按适合去处理字节序，处理完成后再转换字节序

 */

#include <string>
using std::string;

#ifdef BIGINT_EXPORT
#define API _declspec(dllexport)
#else
#define API _declspec(dllimport)
#endif

class /*API*/ Bigint
{
public:
	Bigint();

	/*explicit */Bigint(const char *pstr);

	Bigint(const Bigint &big);

	~Bigint();

	Bigint& operator = (const Bigint&);
	
	inline char* getptr() const
	{
		return m_pnum;
	}

	char &getindex (int nindex) const
	{
		return *(m_pnum + nindex);
	}

	void swap(Bigint& num)
	{
		char *temp = this->m_pnum;
		this->m_pnum = num.m_pnum;
		num.m_pnum = temp;
	}

	friend Bigint& ten(Bigint&);
	inline int getlength() const;

private:

	char *m_pnum;

};

Bigint operator+(const Bigint& num1, const Bigint& num2);
Bigint operator*(Bigint num1, Bigint num2);

int bigcmp(const Bigint& num1, const Bigint& num2);
bool operator >(const Bigint& num1, const Bigint& num2);
bool operator <(const Bigint& num1, const Bigint& num2);
bool operator ==(const Bigint& num1, const Bigint& num2);

#endif