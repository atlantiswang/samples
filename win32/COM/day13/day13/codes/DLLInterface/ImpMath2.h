// ImpMath2.h: interface for the CImpMath2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPMATH2_H__B4E4F9F6_1D0F_4AC5_9AC6_C0E531DE4574__INCLUDED_)
#define AFX_IMPMATH2_H__B4E4F9F6_1D0F_4AC5_9AC6_C0E531DE4574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"

class CImpMath2 : public IMath  
{
public:
	CImpMath2();
	virtual ~CImpMath2();
    virtual int Add(int nAdd1,int nAdd2);
	virtual int Sub(int nSub1,int nSub2);
};

#endif // !defined(AFX_IMPMATH2_H__B4E4F9F6_1D0F_4AC5_9AC6_C0E531DE4574__INCLUDED_)
