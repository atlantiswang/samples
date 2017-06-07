// Math.h : Declaration of the CMath

#ifndef __MATH_H_
#define __MATH_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMath
class ATL_NO_VTABLE CMath : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMath, &CLSID_Math>,
	public IDispatchImpl<IMath, &IID_IMath, &LIBID_DISPMATHLib>
{
public:
	CMath()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MATH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMath)
	COM_INTERFACE_ENTRY(IMath)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMath
public:
	STDMETHOD(Sub)(int nSub1,int nSub2,int *pnSub);
	STDMETHOD(Add)(int nAdd1,int nAdd2,int *pnAdd);
};

#endif //__MATH_H_
