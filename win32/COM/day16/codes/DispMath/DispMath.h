/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 28 16:24:57 2013
 */
/* Compiler settings for F:\MFC\day16\codes\DispMath\DispMath.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DispMath_h__
#define __DispMath_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMath_FWD_DEFINED__
#define __IMath_FWD_DEFINED__
typedef interface IMath IMath;
#endif 	/* __IMath_FWD_DEFINED__ */


#ifndef __Math_FWD_DEFINED__
#define __Math_FWD_DEFINED__

#ifdef __cplusplus
typedef class Math Math;
#else
typedef struct Math Math;
#endif /* __cplusplus */

#endif 	/* __Math_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMath_INTERFACE_DEFINED__
#define __IMath_INTERFACE_DEFINED__

/* interface IMath */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMath;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1199596-C22C-4468-804C-C7C40A1D03D5")
    IMath : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            int nAdd1,
            int nAdd2,
            int __RPC_FAR *pnAdd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sub( 
            int nSub1,
            int nSub2,
            int __RPC_FAR *pnSub) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMathVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMath __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMath __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMath __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMath __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMath __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMath __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMath __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IMath __RPC_FAR * This,
            int nAdd1,
            int nAdd2,
            int __RPC_FAR *pnAdd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sub )( 
            IMath __RPC_FAR * This,
            int nSub1,
            int nSub2,
            int __RPC_FAR *pnSub);
        
        END_INTERFACE
    } IMathVtbl;

    interface IMath
    {
        CONST_VTBL struct IMathVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMath_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMath_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMath_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMath_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMath_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMath_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMath_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMath_Add(This,nAdd1,nAdd2,pnAdd)	\
    (This)->lpVtbl -> Add(This,nAdd1,nAdd2,pnAdd)

#define IMath_Sub(This,nSub1,nSub2,pnSub)	\
    (This)->lpVtbl -> Sub(This,nSub1,nSub2,pnSub)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMath_Add_Proxy( 
    IMath __RPC_FAR * This,
    int nAdd1,
    int nAdd2,
    int __RPC_FAR *pnAdd);


void __RPC_STUB IMath_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMath_Sub_Proxy( 
    IMath __RPC_FAR * This,
    int nSub1,
    int nSub2,
    int __RPC_FAR *pnSub);


void __RPC_STUB IMath_Sub_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMath_INTERFACE_DEFINED__ */



#ifndef __DISPMATHLib_LIBRARY_DEFINED__
#define __DISPMATHLib_LIBRARY_DEFINED__

/* library DISPMATHLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DISPMATHLib;

EXTERN_C const CLSID CLSID_Math;

#ifdef __cplusplus

class DECLSPEC_UUID("28FB6B9D-5080-40A4-893A-C3EEF0C10BAE")
Math;
#endif
#endif /* __DISPMATHLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
