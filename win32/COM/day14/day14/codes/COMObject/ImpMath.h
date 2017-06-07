// ImpMath.h: interface for the CImpMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPMATH_H__E29B7FC6_CC24_4D0C_90EB_E8B87E317F38__INCLUDED_)
#define AFX_IMPMATH_H__E29B7FC6_CC24_4D0C_90EB_E8B87E317F38__INCLUDED_

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
	STDMETHOD(Add)(int nAdd1,int nAdd2,int *pnAdd);
	STDMETHOD(Sub)(int nSub1,int nSub2,int *pnSub);
};

#endif // !defined(AFX_IMPMATH_H__E29B7FC6_CC24_4D0C_90EB_E8B87E317F38__INCLUDED_)
