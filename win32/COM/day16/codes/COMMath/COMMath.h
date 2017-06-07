/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 28 10:05:20 2013
 */
/* Compiler settings for F:\MFC\day16\codes\COMMath\COMMath.idl:
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

#ifndef __COMMath_h__
#define __COMMath_h__

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
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMath;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B441E881-7662-4984-BB97-AA258A520149")
    IMath : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            int nAdd1,
            int nAdd2,
            int __RPC_FAR *pnAdd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Sub( 
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
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IMath __RPC_FAR * This,
            int nAdd1,
            int nAdd2,
            int __RPC_FAR *pnAdd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sub )( 
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


#define IMath_Add(This,nAdd1,nAdd2,pnAdd)	\
    (This)->lpVtbl -> Add(This,nAdd1,nAdd2,pnAdd)

#define IMath_Sub(This,nSub1,nSub2,pnSub)	\
    (This)->lpVtbl -> Sub(This,nSub1,nSub2,pnSub)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMath_Add_Proxy( 
    IMath __RPC_FAR * This,
    int nAdd1,
    int nAdd2,
    int __RPC_FAR *pnAdd);


void __RPC_STUB IMath_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMath_Sub_Proxy( 
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



#ifndef __COMMATHLib_LIBRARY_DEFINED__
#define __COMMATHLib_LIBRARY_DEFINED__

/* library COMMATHLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_COMMATHLib;

EXTERN_C const CLSID CLSID_Math;

#ifdef __cplusplus

class DECLSPEC_UUID("CAFACD34-937A-41AA-A4E8-EDED32971AE9")
Math;
#endif
#endif /* __COMMATHLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
