// Serialize.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Serialize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
//写数据
void Store()
{
	CFile file;
	//新建文件
	file.Open("c:/serial.dat",CFile::modeCreate|
		CFile::modeWrite);
	//写入数据
	CArchive ar(&file,CArchive::store);
	ar<<100<<12.25<<'A';
	ar.Close();
	file.Close();
}
//读数据
void Load()
{
	CFile file;
	file.Open("c:/serial.dat",CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	int nValue=0;
	double fValue=0.0;
	char cValue;
	ar>>nValue>>fValue>>cValue;
	printf("%d\n%f\n%c\n",nValue,fValue,cValue);
	ar.Close();
	file.Close();
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	Store();
	Load();
	return 0;
}


