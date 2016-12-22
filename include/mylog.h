#ifndef _MYLOG_H
#define _MYLOG_H
/*
 * FUN_IN(funname);

 * LOG_BIN("instruct:", p, nlen);
 
 * LOG_INF(("this is num :%d", 100)); or  LOG_INF((L"this is num :%d--%s", 100, L"mylog"));
 */
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#pragma warning(disable:4251)
#pragma warning(disable:4996)

#define IMPORT_LIB_PATH "../share/lib/host.lib"
#ifdef _USRDLL
	#define MYLOG_API __declspec(dllimport)
	#pragma comment(lib, IMPORT_LIB_PATH)
#else
	#define MYLOG_API __declspec(dllexport)
#endif

#define MAX_FILE_SIZE 30*1024*1024
typedef std::string stringa;

class MYLOG_API stackclass
{
public:
	stackclass(const char *fun_name);
	~stackclass();
private:
	unsigned short getcolor();
private:
	int m_level;
	int m_thread_id;
	stringa m_strlog;
	static unsigned short int ms_color;
};

class MYLOG_API msglog
{
public:
	enum {COLUMN = 16, REGION = 4, TOTALCOLUMN = 3*COLUMN+REGION+COLUMN+2};
	void logbinary(char *strinfo, const unsigned char *pbyte, int nlen);
	void logstring(const char *szformat, ...);
	void logstring(const wchar_t *szformat, ...);
	void log(const char *pszlog, unsigned short color = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	static msglog& get_log_instance();
private: 
	msglog();
	~msglog();
	const void *ctrltopoint(const unsigned char *p, int nlen);
	stringa getfilename();
private:
	
	HANDLE m_console_handle;
	stringa m_filename;
};

#if (defined LOG_TO_FILE) || (defined LOG_TO_STD)
	#define FUN_IN(fun_name) msglog::get_log_instance();stackclass sclss_##fun_name(#fun_name)
	#define LOG_INF(loginfo) msglog::get_log_instance().logstring loginfo
	#define LOG_BIN(strinfo, pbdata, nlen) msglog::get_log_instance().logbinary(strinfo, pbdata, nlen)
#else
	#define FUN_IN(fun_name)
	#define LOG_INF(loginfo)
	#define LOG_BIN(strinfo, pbdata, nlen)
#endif

#endif
