#include "stdafx.h"
#include "MFCFile.h"

void File()
{
	CFile file;
	file.Open("c:/mfc.txt",CFile::modeCreate|
		CFile::modeReadWrite);
	file.Write("hello data",10);
	file.SeekToBegin();
	char szText[256] = {0};
	UINT nLen = file.Read(szText,256);//实际读多少返回值告诉
	printf("%s-%d\n",szText,nLen);
	file.Close();
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	File();
}


