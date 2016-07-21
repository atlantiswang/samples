

#ifndef _XiaoGeMVarTempleteHasBeenDefined_
#define _XiaoGeMVarTempleteHasBeenDefined_
#include <afxmt.h>

//仅在windows VC++下用
//多线程安全的变量模板
template <class MVAR_TYPE>
class MVAR
{
public:
	MVAR()
	{
		m_pBegin=new char[sizeof(MVAR_TYPE)];
		memset(m_pBegin,0,sizeof(MVAR_TYPE));
	}
	~MVAR(){delete[] m_pBegin;}
	int GetLength(){return sizeof(MVAR_TYPE);}
	//设置变量的值
	MVAR_TYPE Set(MVAR_TYPE& value)
	{
		m_csLockHandle.Lock();
		memcpy(m_pBegin,(char*)&value,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return value;
	}
	//获取变量的值
	MVAR_TYPE Get()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载=，直接赋值符号
	MVAR_TYPE operator=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		myValue=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载按位取反运算符
	MVAR_TYPE operator~()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue=~myValue;
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载前加运算符
	MVAR_TYPE operator++(int)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue++;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	//重载后加运算符
	MVAR_TYPE operator++()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue++;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator--(int)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue--;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator--()
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue--;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator+(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue+=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator-(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue-=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator*(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue*=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator/(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue/=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator&(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue&=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator|(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue|=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator^(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue^=value;
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator+=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue+=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator-=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue-=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator*=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue*=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator/=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue/=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator&=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue&=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator|=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue|=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	MVAR_TYPE operator^=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));
		myValue^=value;
		memcpy(m_pBegin,(char*)&myValue,sizeof(MVAR_TYPE));
		m_csLockHandle.Unlock();
		return myValue;
	}
	BOOL operator>(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));

		bRet=(myValue>value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	BOOL operator<(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));

		bRet=(myValue<value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	BOOL operator>=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));

		bRet=(myValue>=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	BOOL operator<=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));

		bRet=(myValue<=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	BOOL operator==(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));

		bRet=(myValue==value);
		m_csLockHandle.Unlock();
		return bRet;
	}
	BOOL operator!=(MVAR_TYPE value)
	{
		MVAR_TYPE myValue;
		BOOL bRet;
		m_csLockHandle.Lock();
		memcpy((char*)&myValue,m_pBegin,sizeof(MVAR_TYPE));

		bRet=(myValue!=value);
		m_csLockHandle.Unlock();
		return bRet;
	}
private:
	//为了适用所有的变量类型，此处使用动态内存块保存变量区域，
	//内部仅保留一个指向变量区域的指针，通过强制指针类型转换实现访问
	char* m_pBegin;
	::CCriticalSection m_csLockHandle;
};
typedef MVAR<char> MCHAR;
typedef MVAR<TCHAR> MTCHAR;
typedef MVAR<unsigned char> MUCHAR;
typedef MVAR<short> MSHORT;
typedef MVAR<unsigned short> MUSHORT;
typedef MVAR<int> MINT;
typedef MVAR<unsigned int> MUINT;
typedef MVAR<long> MLONG;
typedef MVAR<unsigned long> MULONG;
typedef MVAR<float> MFLOAT;
typedef MVAR<double> MDOUBLE;
typedef MVAR<BOOL> MBOOL;
typedef MVAR<LPVOID> MLPVOID;
typedef MVAR<BYTE> MBYTE;
#endif //_XiaoGeMVarTempleteHasBeenDefined_
