// COMObject.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ImpMath.h"
#include "math_i.c"
//ATL中需要的全局变量，保存了ATL库的信息
CComModule _Module;
//组件ID与组件实现类的映射关系
BEGIN_OBJECT_MAP(objectMap)
  OBJECT_ENTRY(CLSID_Math,CImpMath)
END_OBJECT_MAP()

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    //当dll第一个被加载到应用程序的进程空间时
	if (ul_reason_for_call==DLL_PROCESS_ATTACH)
	{
		//将组件ID与组件类的映射关系保存到_Module中
		_Module.Init(objectMap,(HINSTANCE)hModule);
	}
	return TRUE;
}
/*
//创建对象，返回接口的函数
IMath* CreateInstance()
{
	//CImpMath是一个抽象类，不能创建对象
	  IMath *piMath=new CImpMath;
	piMath->AddRef();
	return piMath;
}
*/
//创建对象是ATL库提供的CComObject类
IMath* MyCreateInstance()
{
	CComObject<CImpMath> *pObject;
	//创建对象，对象的地址保存pObject指针变量中
	CComObject<CImpMath>::CreateInstance(&pObject);
	pObject->AddRef();
	return pObject;
}
//通用的代码，任何组件的创建都可以使用该方式创建
IUnknown* MyCreateInstanceEx(CLSID clsid)
{
   //1 创建指定组件的类厂对象，并返回该类厂的接口
	IClassFactory *pFactory;
    _Module.GetClassObject(clsid,IID_IClassFactory,
		(LPVOID*)&pFactory);
	//2 使用类厂创建组件对象，返回IUnknown接口
	IUnknown *piUnknown;
    pFactory->CreateInstance(NULL,IID_IUnknown,
		(LPVOID*)&piUnknown);
	return piUnknown;

} 
