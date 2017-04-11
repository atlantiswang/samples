//*****************************************************************************
//  Copyright (c) 2009 Shenzhen Surfilter Network Technology Co., Ltd. 
//  All Rights Reserved.
//
//  Module Name:
//      FileLog.h ILog接口的文件记录实现方式
//
//  Abstract:
//      记录所有的日志到文件中。
//
//  Notes:
//
//  Created: 2009/09/09
//*****************************************************************************

#ifndef __FileLog_H__
#define __FileLog_H__

#include "Log.h"
#define LOG_DATA_LEN 4096

#define LTT_Debug _T("LT_Debug")
#define LTT_Information _T("LT_Information")
#define LTT_Warning _T("LT_Warning")
#define LTT_Error _T("LT_Error")
#define LTT_None _T("LT_None")
//#include "Common/Configurator.h"
//#include "Utility/Configuration.h"
//#include "Utility/Mutex.h"
class Mutex
{
public:
	Mutex() {InitializeCriticalSection(&m_Mutex);}
	~Mutex()
	{
		LeaveCriticalSection(&m_Mutex);
		DeleteCriticalSection(&m_Mutex);
	}
	void _Lock(){EnterCriticalSection(&m_Mutex);}
	void _unlock(){LeaveCriticalSection(&m_Mutex);}
private:
	CRITICAL_SECTION m_Mutex;
};

class CFileLog : public ILog
{
public:
	enum {COLUMN = 16, REGION = 4, TOTALCOLUMN = 3*COLUMN+REGION+COLUMN+2};
	CFileLog();
	~CFileLog();
	bool Initialize();
	virtual void Log(const tchar* sourceName, LogType logType, const char *format, ...);
	virtual void LogBin(const tchar* sourceName, LogType logType, const BYTE *logData, int nLen);
private:
	void ReadString(tchar *pSection, tchar *pValue);
	unsigned ReadInt(tchar *pSection);
	const tchar* LogTypeToString(LogType logType);
	LogType StringToLogLevel(const tchar* level);
    inline void ApplySettings();
    void LogToFile(const tchar* sourceName, LogType logType, const tchar* logData);
    void Close();
	std::string CFileLog::GetLogFileName();	
	void *CtrltoPoint(const unsigned char *p, int nlen);
private:
    LogType m_logLevel;
    Mutex m_Mutex;
    FILE *m_logFile;
    time_t m_timeOld;
    tstring m_logFileName;
    tstring m_configFilePath;
	unsigned m_MaxFileSize;//文件的最大大小（MB)
	unsigned m_InterVal;//读取日志文件的时间间隔
};

#endif // !defined(ES_E1E13F05_575F_4cd9_A5B5_786F45430AFF__INCLUDED_)
