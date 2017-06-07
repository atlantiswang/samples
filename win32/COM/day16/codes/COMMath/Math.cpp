// Math.cpp : Implementation of CMath
#include "stdafx.h"
#include "COMMath.h"
#include "Math.h"

/////////////////////////////////////////////////////////////////////////////
// CMath


STDMETHODIMP CMath::Add(int nAdd1, int nAdd2, int *pnAdd)
{
	// TODO: Add your implementation code here
    *pnAdd=nAdd1+nAdd2;
	return S_OK;
}

STDMETHODIMP CMath::Sub(int nSub1, int nSub2, int *pnSub)
{
	// TODO: Add your implementation code here
    *pnSub=nSub1-nSub2;
	return S_OK;
}
