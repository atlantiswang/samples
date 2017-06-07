// ImpMath.h: interface for the CImpMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPMATH_H__E29B7FC6_CC24_4D0C_90EB_E8B87E317F38__INCLUDED_)
#define AFX_IMPMATH_H__E29B7FC6_CC24_4D0C_90EB_E8B87E317F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"
//#include "math_i.c"

extern const CLSID CLSID_Math;
class CImpMath : public IMath,
                 public CComObjectRootEx<CComSingleThreadModel>,
				 public CComCoClass<CImpMath,&CLSID_Math>
{
public:
	CImpMath();
	virtual ~CImpMath();
	//接口映射宏，作用是为了实现接口查询
	BEGIN_COM_MAP(CImpMath)
		COM_INTERFACE_ENTRY(IMath) 
	/*
	{&IID_IMath,//接口ID
	//offsetofclass(IMath, _ComMapClass), 
	//通过计算偏移量的到接口的地址
	((DWORD)(static_cast<IMath*>((CImpMath*)8))-8),
	_ATL_SIMPLEMAPENTRY},
	*/
	END_COM_MAP()
	//与组件注册相关的宏
	DECLARE_REGISTRY_RESOURCE(0)
//IMath
public:
	STDMETHOD(Add)(int nAdd1,int nAdd2,int *pnAdd);
	STDMETHOD(Sub)(int nSub1,int nSub2,int *pnSub);
};

#endif // !defined(AFX_IMPMATH_H__E29B7FC6_CC24_4D0C_90EB_E8B87E317F38__INCLUDED_)
