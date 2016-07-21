// CString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//getbuffer()
	//getbuffer(n)
	//这两个是重载，第一个相当于第二的n=0;也就是仅仅读
	//当n小于本有的长度时，该参数就被忽略。不分配内存
#if 0
	TCHAR strLen[128] = _T("1234567");
	printf("%d %d %d\n", strlen((const char*)strLen), lstrlen(strLen));
#endif
	
#if 0
	printf("%d", _MSC_VER);
	CString strTest;
	strTest = _T("123456789");
	AfxMessageBox(strTest);

	LPTSTR strTest2 = strTest.GetBuffer();
	wcscpy(strTest2, _T("fdsa"));
	wprintf(_T("%s"), strTest.GetBuffer());
#endif
	char regname[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkResult;
	int ret=RegOpenKey(HKEY_LOCAL_MACHINE,regname,&hkResult);

	ret=RegSetValueEx(hkResult,"Reminder",0,REG_SZ,(unsigned char *)"F:\\Reminder\\Reminder.exe",40);
	if(ret==0){
		printf("success to write run key\n");
		RegCloseKey(hkResult);
	}
	else {
		printf("failed to open regedit.%d\n",ret);
		return 0;
	}

	getchar();
	return 0;
}

