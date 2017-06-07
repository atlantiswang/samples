// ImpMath.h: interface for the CImpMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPMATH_H__986B0B83_65A8_46A7_B669_56AD83867981__INCLUDED_)
#define AFX_IMPMATH_H__986B0B83_65A8_46A7_B669_56AD83867981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"

class CImpMath : public IMath,public IMath2  
{
public:
	CImpMath();
	virtual ~CImpMath();
    virtual int Add(int nAdd1,int nAdd2);
	virtual int Sub(int nSub1,int nSub2);
	virtual int Mul(int nMul1,int nMul2);
    virtual int Div(int nDiv1,int nDiv2);
	virtual ULONG AddRef();
    virtual ULONG Release();
	virtual HRESULT QueryInterface(
		   REFIID iid,LPVOID* ppVoid );

public:
	LONG m_nRef;//引用计数
};

#endif // !defined(AFX_IMPMATH_H__986B0B83_65A8_46A7_B669_56AD83867981__INCLUDED_)
