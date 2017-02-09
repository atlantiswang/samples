#include <stdio.h>
#include <windows.h>


typedef int(*DLL_ADD)(int m,int n);
//typedef int(*DLL_SUB)(int m,int n);
typedef int(*DLL_SUB)(int m,int n,int z);

int main()
{
	HINSTANCE hDll = LoadLibrary("CPPdll.dll");
	printf("hDll:%d\n",hDll);
	
	DLL_ADD myAdd = (DLL_ADD)GetProcAddress(hDll,"CPPdll_add");
	printf("myAdd:%p\n",myAdd);
	int sum = myAdd(5,6);
	printf("sum=%d\n",sum);
	DLL_SUB mySub = (DLL_SUB)GetProcAddress(hDll,"CPPdll_sub2");//(hDll,"?CPPdll_sub@@YAHHH@Z");
	printf("mySub:%p\n",mySub);
	//int sub = mySub(5,6);
	int sub = mySub(5,6,7);
	printf("sub=%d\n",sub);
	FreeLibrary(hDll);
	return 0;
}