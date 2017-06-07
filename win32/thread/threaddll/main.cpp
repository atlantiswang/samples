#include <windows.h>
#include <stdio.h>

_declspec(dllexport)  void fun()
{
	for (int i = 0; i <100 ; i++)
	{
		printf("%d\n", i);
		Sleep(1000);
	}
}