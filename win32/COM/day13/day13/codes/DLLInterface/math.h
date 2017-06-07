#ifndef _MATH_H_
#define _MATH_H_

#include <objbase.h>
interface IMath
{
public:
   virtual int Add(int nAdd1,int nAdd2)=0;
   virtual int Sub(int nSub1,int nSub2)=0;
   virtual ULONG AddRef()=0;
   virtual ULONG Release()=0;
};

#endif  //_MATH_H_