#ifndef _MATH_H_
#define _MATH_H_

#include <objbase.h>
// {6FABEE74-BEFF-4c86-9F7B-2C6303473C81}
static const GUID IID_IBase = 
{ 0x6fabee74, 0xbeff, 0x4c86, { 0x9f, 0x7b, 0x2c, 0x63, 0x3, 0x47, 0x3c, 0x81 } };

interface IBase
{
public:
	virtual ULONG AddRef()=0;
	virtual ULONG Release()=0;
    virtual HRESULT QueryInterface(REFIID iid,LPVOID* ppVoid )=0;
};
// {64A0740E-3E8D-4de8-A6A1-B2D9254D7325}
static const GUID IID_IMath = 
{ 0x64a0740e, 0x3e8d, 0x4de8, { 0xa6, 0xa1, 0xb2, 0xd9, 0x25, 0x4d, 0x73, 0x25 } };

interface IMath:public IBase
{
public:
   virtual int Add(int nAdd1,int nAdd2)=0;
   virtual int Sub(int nSub1,int nSub2)=0;
 
};
// {AB5DD939-9E75-4d46-BBD2-4DCF6FCB3F0A}
static const GUID IID_IMath2 = 
{ 0xab5dd939, 0x9e75, 0x4d46, { 0xbb, 0xd2, 0x4d, 0xcf, 0x6f, 0xcb, 0x3f, 0xa } };

interface IMath2:public IBase
{
   virtual int Mul(int nMul1,int nMul2)=0;
   virtual int Div(int nDiv1,int nDiv2)=0;
};
#endif  //_MATH_H_