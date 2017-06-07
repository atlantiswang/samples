// ImpMath.cpp: implementation of the CImpMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImpMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImpMath::CImpMath()
{
   m_nRef=0;//引用计数的初始化
}

CImpMath::~CImpMath()
{

}
ULONG CImpMath::AddRef()
{
	//m_nRef++;
    InterlockedIncrement(&m_nRef);
	return m_nRef;
}
ULONG CImpMath::Release()
{
	//m_nRef--;
	InterlockedDecrement(&m_nRef);
	if (0==m_nRef)
	{
		delete this;
	}
	return m_nRef;
}
HRESULT CImpMath::QueryInterface(REFIID iid,
								 LPVOID *ppVoid)
{
    if(iid==IID_IMath)
	{
		*ppVoid=static_cast<IMath*>(this);
	}
	else if(iid==IID_IMath2)
	{
        *ppVoid=static_cast<IMath2*>(this);
	}
	else
	{
		*ppVoid=NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}
int CImpMath::Add(int nAdd1,int nAdd2)
{
	return nAdd1+nAdd2;
}
int CImpMath::Sub(int nSub1,int nSub2)
{
	return nSub1-nSub2;
}
int CImpMath::Mul(int nMul1,int nMul2)
{
	return nMul1*nMul2;
}
int CImpMath::Div(int nDiv1,int nDiv2)
{
	return nDiv1/nDiv2;
}