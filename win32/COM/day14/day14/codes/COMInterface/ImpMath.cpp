// ImpMath.cpp: implementation of the CImpMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImpMath.h"
#include "math_i.c"
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
STDMETHODIMP CImpMath::Add(int nAdd1,int nAdd2,
						   int *pnAdd)
{
   *pnAdd=nAdd1+nAdd2;
   return S_OK;
}
STDMETHODIMP CImpMath::Sub(int nSub1,int nSub2,
						   int *pnSub)
{
	*pnSub=nSub1-nSub2;
	return S_OK;
}
STDMETHODIMP_(ULONG) CImpMath::AddRef()
{
	InterlockedIncrement(&m_nRef);
	return m_nRef;
}
STDMETHODIMP_(ULONG) CImpMath::Release()
{
	InterlockedDecrement(&m_nRef);
	if (0==m_nRef)
	{
		delete this;
	}
	return m_nRef;
}
STDMETHODIMP CImpMath::QueryInterface( REFIID iid,
								LPVOID* ppVoid )
{
	if (IID_IUnknown==iid)
	{
		*ppVoid=static_cast<IUnknown*>(this);
	}
	else if(IID_IMath==iid)
	{
		*ppVoid=static_cast<IMath*>(this);
	}
	else
	{
        *ppVoid=NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}
 
