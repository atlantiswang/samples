#ifndef DLLCLASS_H
#define DLLCLASS_H

#ifdef DLLCLASS_EXPORTS
#define EXT_CLASS _declspec(dllexport)
#else 
#define EXT_CLASS _declspec(dllimport)
#endif
class EXT_CLASS CMath
{
public:
	int Add(int add1,int add2);
	int Sub(int sub1,int sub2);
};

#endif