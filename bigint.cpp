#define BIGINT_EXPORT

#include <stdlib.h>
#include "bigint.h"
#include "smart_ptr.h"

static
void makestr(char *p)
{
	int nlen = strlen(p);
	for (int i = 0; i <nlen/2; i++)
	{
		char temp = p[i];
		p[i] = p[nlen - 1 -i];
		p[nlen - 1 -i] = temp;
	}
}


Bigint& ten(Bigint &num)
{
	int nlen = num.getlength();
	char *p =
	(char*)realloc(num.getptr(), nlen+2);
	
	if(p == NULL) puts("ten error");
	else
	{
		*(num.getptr()+nlen) = '0';
		*(num.getptr()+nlen+1) = 0;
	}
	return num;
}


Bigint::Bigint()
{
  m_pnum = new char[1];
  *m_pnum = '\0';
//  m_len = 0;
}

Bigint::Bigint(const char *pstr)
{
	if (NULL == pstr)
	{
		m_pnum = new char[1];
		*m_pnum = '\0';
//		m_len = 0;
	}else
	{
		int nlen = strlen(pstr);
		m_pnum = new char[nlen +1];
		strcpy(m_pnum, pstr);
//		m_len = nlen;
	}
}

Bigint::Bigint(const Bigint &big)
{
  int nlen = strlen(big.getptr());
  m_pnum = new char[nlen +1];
  memset(m_pnum, 0, nlen + 1);
  strcpy_s(m_pnum, nlen +1, big.getptr());
}

Bigint::~Bigint()
{
  if (m_pnum) delete [] m_pnum;
  m_pnum = NULL;
}

int Bigint::getlength() const
{
	return strlen(m_pnum);
}

Bigint& Bigint::operator = (const Bigint& num)
{
#if 1
	/*
	 *	exception safety（异常安全性）往往自动获得“自我赋值安全”的回报。

	 *	因此愈来愈多的人对“自我赋值”的处理态度上是倾向不去管它，把焦点放在

	 *	实现exception safety（异常安全性）（条款 29）上。

	 *											-------《effective c++》条款 10
	 */
	char *pold = m_pnum;
	int nlen = strlen(num.getptr());
	m_pnum = new char[nlen +1];
	delete [] pold;
	strcpy(m_pnum, num.getptr());
	return *this;
#elif 0
	if (this == &num)
		return *this;
	
	int nlen = strlen(num.getptr());
	if(m_pnum)
	{
		delete [] m_pnum;
	}
	m_pnum = new char[nlen + 1];
	memset(m_pnum, 0, nlen +1);
	strcpy(m_pnum, num.getptr());
	return *this;
#endif
}


Bigint operator+(const Bigint& num1, 
				 const Bigint& num2)
{
	int nlen1 = num1.getlength();
	int nlen2 = num2.getlength();
	const Bigint &maxint = nlen1>=nlen2?num1:num2;
	const Bigint &minint = nlen1>=nlen2?num2:num1;

	//申请的字节数永远比最长的数多1.但计算的时候按不进位计算
	//memory leak
	ptr_array<char> ptr(new char[maxint.getlength()+1+1]);
	Bigint temp = ptr.getptr();
	memset(temp.getptr(), 0, maxint.getlength()+1+1);

	int maxindex = maxint.getlength() -1;
	int minindex = minint.getlength() -1;
	int nindex  = strlen(maxint.getptr()) -1;

	int nmax = maxint.getlength();
	int nmin = minint.getlength();

	bool flag = false;

	for(int max = maxint.getlength(); max>0; max--)
	{
		temp.getindex(nindex) = (maxint.getindex(maxindex--) + (minindex>=0?minint.getindex(minindex--):'0') +flag -'0');
		flag = false;
		if( temp.getindex(nindex--)> '9')
		{
			flag = true;
			temp.getindex(nindex+1) = (temp.getindex(nindex+1) % ('9'+1)) +'0';
		}
	}
	if(flag)
	{
		for (int i=temp.getlength(); i>0; i--)
		{
			temp.getindex(i) = temp.getindex(i-1);
		}
		temp.getindex(0) = '1';
	}

	return temp;
}

//right param is litter one
Bigint operator *(Bigint num1,Bigint num2)
{	
#if 1
	static bool s_first = 1;

	if(num2.getlength() == 0|| num1.getlength() ==0||
		strcmp(num2.getptr(), "0") == 0 ||
		strcmp(num1.getptr(), "0") == 0)
		return "0";
	if (s_first && num1<num2){num1.swap(num2);}

	s_first = 0;
#endif

	int nlen1 = num1.getlength();
	int nlen2 = num2.getlength();
	//memory leak
	ptr_array<char> sum = new char[nlen1+1+1];
	memset(sum.getptr() , 0, nlen1+2);
	int flag = 0;

	int nindex = 0;
	for(; nindex < nlen1; nindex++)
	{
		int num = (num2.getindex(nlen2-1)-'0')*(num1.getindex(nlen1 - nindex - 1)-'0') +flag;
		sum[nindex] = num%10 +'0';
		flag = num/10;
	}
	if(flag) sum[nindex] = flag +'0';
	makestr(sum.getptr());
	//memory leak
	ptr_array<char> pleft =new char[nlen2+1];
	strcpy(pleft.getptr(), num2.getptr());
	pleft[num2.getlength() - 1] = 0;

//	Bigint temp =ten(num1*pleft);
	return (Bigint(sum.getptr()) + ten(num1*pleft.getptr()));
}

int bigcmp(const Bigint& num1, const Bigint& num2)
{
	int nlen1 = num1.getlength(), nlen2 = num2.getlength();

	if(nlen1 > nlen2) return 1;

	if(nlen1 < nlen2) return -1;

	return strcmp(num1.getptr(), num2.getptr());
}

bool operator >(const Bigint& num1, const Bigint& num2)
{
	if(bigcmp(num1, num2) >0) return true;
	return false;
}

bool operator <(const Bigint& num1, const Bigint& num2)
{
	if(bigcmp(num1, num2) <0) return true;
	return false;
}

bool operator ==(const Bigint& num1, const Bigint& num2)
{
	if(bigcmp(num1, num2) ==0) return true;
	return false;
}