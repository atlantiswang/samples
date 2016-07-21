

#ifndef ZL_CHAR_CONVERT_H
#define ZL_CHAR_CONVERT_H

#include <iostream>  
#include <windows.h>  
#include <string>  
using namespace std;  
class CCharConvert 
{  
public:  
	CCharConvert();  
	virtual~ CCharConvert();  
	char* WcharToChar(const wchar_t* wp);  
	char* StringToChar(const string& s);  
	char* WstringToChar(const wstring& ws);  
	wchar_t* CharToWchar(const char* c);  
	wchar_t* WstringToWchar(const wstring& ws);  
	wchar_t* StringToWchar(const string& s);  
	wstring StringToWstring(const string& s);  
	string WstringToString(const wstring& ws);  
	void Release();  
private:  
	char* m_pChar;  
	wchar_t* m_pWChar;  
};  

#endif // ZL_CHAR_CONVERT_H
