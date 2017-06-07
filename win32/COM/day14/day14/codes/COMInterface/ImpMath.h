// ImpMath.h: interface for the CImpMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPMATH_H__B4228D53_1A96_4E56_BE32_EFC89A2B4A68__INCLUDED_)
#define AFX_IMPMATH_H__B4228D53_1A96_4E56_BE32_EFC89A2B4A68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"
class CImpMath : public IMath  
{
public:
	CImpMath();
	virtual ~CImpMath();
//IMath
public:
	STDMETHOD(Add)(int nAdd1,int nAdd2,int  *pnAdd);
	STDMETHOD(Sub)(int nSub1,int nSub2,int  *pnSub);
//IUnknown
public:
	STDMETHOD_(ULONG,AddRef)();
	STDMETHOD_(ULONG,Release)();
    STDMETHOD(QueryInterface)(REFIID iid,LPVOID* ppVoid);
public:
	LONG m_nRef;//引用计数
};

#endif // !defined(AFX_IMPMATH_H__B4228D53_1A96_4E56_BE32_EFC89A2B4A68__INCLUDED_)
