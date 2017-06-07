// UseCOMObject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../COMObject/math.h"
#include "../COMObject/math_i.c"

typedef IMath*(*INSTANCE)();
typedef IUnknown*(*INSTANCEEX)(CLSID);
IMath *GetMath()
{
   HMODULE hDll=LoadLibrary("COMObject.dll");
   INSTANCE Instance=(INSTANCE)
	   GetProcAddress(hDll,"MyCreateInstance");
   IMath *pMath=Instance();
   return pMath;

}
IUnknown * GetInterface()
{
  HMODULE hDll=LoadLibrary("COMObject.dll");
  INSTANCEEX Instance=(INSTANCEEX)
	  GetProcAddress(hDll,"MyCreateInstanceEx");
  IUnknown *piUnknown=Instance(CLSID_Math);
  return piUnknown;
}
int main(int argc, char* argv[])
{
	//IMath *piMath=GetMath();
    IUnknown *piUnknown=GetInterface();
    IMath *piMath=NULL;
    piUnknown->QueryInterface(IID_IMath,(LPVOID*)&piMath); 
	//释放IUnknown接口
	piUnknown->Release();
	//使用IMath 接口
	int nAdd=0;//保存计算结果
	piMath->Add(100,100,&nAdd);
	//释放IMath接口
	piMath->Release();
	//输出结果
	printf("nAdd=%d\n",nAdd);
	getchar();
	return 0;
}

