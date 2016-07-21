
#include "stdafx.h"
#include "CharConvert.h"

CCharConvert::CCharConvert()  
	:m_pChar(NULL)  
	,m_pWChar(NULL)  
{  
}  
CCharConvert::~CCharConvert()  
{  
	Release();  
}  
char* CCharConvert::WcharToChar(const wchar_t* wp)  
{  
	Release();  
	int len= WideCharToMultiByte(CP_ACP,0,wp,wcslen(wp),NULL,0,NULL,NULL);  
	m_pChar=new char[len+1];  
	WideCharToMultiByte(CP_ACP,0,wp,wcslen(wp),m_pChar,len,NULL,NULL);  
	m_pChar[len]='\0';  
	return m_pChar;  
}  
wchar_t* CCharConvert::CharToWchar(const char* c)  
{  
	Release();  
	int len = MultiByteToWideChar(CP_ACP,0,c,strlen(c),NULL,0);  
	m_pWChar=new wchar_t[len+1];  
	MultiByteToWideChar(CP_ACP,0,c,strlen(c),m_pWChar,len);  
	m_pWChar[len]='\0';  
	return m_pWChar;  
}  
void CCharConvert::Release()  
{  
	if(m_pChar)  
	{  
		delete m_pChar;  
		m_pChar=NULL;  
	}  
	if(m_pWChar)  
	{  
		delete m_pWChar;  
		m_pWChar=NULL;  
	}  
}  
char* CCharConvert::StringToChar(const string& s)  
{  
	return const_cast<char*>(s.c_str());  
}  
char* CCharConvert::WstringToChar(const std::wstring &ws)  
{  
	const wchar_t* wp=ws.c_str();  
	return WcharToChar(wp);  
}  
wchar_t* CCharConvert::WstringToWchar(const std::wstring &ws)  
{  
	return const_cast<wchar_t*>(ws.c_str());  
}  
wchar_t* CCharConvert::StringToWchar(const string& s)  
{  
	const char* p=s.c_str();  
	return CharToWchar(p);  
}  
string CCharConvert::WstringToString(const std::wstring &ws)  
{  
	string s;  
	char* p=WstringToChar(ws);  
	s.append(p);  
	return s;  
}  
wstring CCharConvert::StringToWstring(const std::string &s)  
{  
	wstring ws;  
	wchar_t* wp=StringToWchar(s);  
	ws.append(wp);  
	return ws;  
}  