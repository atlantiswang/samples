// Interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <objbase.h>
//定义接口
interface IMath
{
public:
	virtual int Add(int nAdd1,int nAdd2)=0;
	virtual int Sub(int nSub1,int nSub2)=0;
};
//定义组件的实现类
class CImpMath:public IMath
{
public:
	virtual int Add(int nAdd1,int nAdd2);
	virtual int Sub(int nSub1,int nSub2);
};
int CImpMath::Add(int nAdd1,int nAdd2)
{
	return nAdd1+nAdd2;
}
int CImpMath::Sub(int nSub1,int nSub2)
{
	return nSub1-nSub2;
}
//定义组件的第二个实现类
class CImpMath2:public IMath
{
public:
	virtual int Add(int nAdd1,int nAdd2);
	virtual int Sub(int nSub1,int nSub2);
};
int CImpMath2::Add(int nAdd1,int nAdd2)
{
	return nAdd1+nAdd2+100;
}
int CImpMath2::Sub(int nSub1,int nSub2)
{
	return nSub1-nSub2-100;
}
//定义一个创建对象的函数，使用接口返回
IMath* CreateInstance()
{
	return new CImpMath2;
} 
//功能的提供者，提供Add/Sub功能
////////////////////////////////////////

//以下是功能的使用者
int main(int argc, char* argv[])
{
	//1 不通过接口，使用Add/Sub功能
    CImpMath2 math;
	int nAdd=math.Add(100,100);

	//2 使用接口调用Add/Sub函数
    IMath *pMath=CreateInstance();
	nAdd=pMath->Add(100,100);


	printf("nAdd=%d\n",nAdd);
	return 0;
}

