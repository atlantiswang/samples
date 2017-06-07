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