#ifndef _MYLOG_H
#define _MYLOG_H
/*
 * FUN_IN(funname); add()auto

 * LOG_INF(("this is num :%d", 100));

 * LOG_BIN("instruct", p, nlen);
 
 * log for error need add file and line information
 */
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

#define LOG_FILE_NAME "host_log.txt"

typedef std::string stringa;
class stackclass
{
public:
	stackclass(const char *fun_name);
	~stackclass();
	
private:
	stringa m_strlog;
	int m_level;
};


class msglog
{
public:
	enum {COLUMN = 16};
	void logbinary(char *strinfo, const char *pbyte, int nlen);
	void logstring(const char *szformat, ...);
	void log(const char *pszlog);
	friend msglog& get_log_instance();
private:
	msglog(){}
	~msglog(){}
};
#endif

//此处为log的接口
#if (defined LOG_TO_FILE) || (defined LOG_TO_STD)
	#define FUN_IN(fun_name) stackclass sclss_##fun_name(#fun_name)
	#define LOG_INF(loginfo) get_log_instance().logstring loginfo
	#define LOG_BIN(strinfo, pbdata, nlen) get_log_instance().logbinary(strinfo, pbdata, nlen)
#else
	#define FUN_IN(fun_name)
	#define LOG_INF(loginfo)
	#define LOG_BIN(strinfo, pbdata, nlen)
#endif