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

#include "FileLog.h"
//#include "Common/Common.h"
//#include "Files.h"
#include "log.h"
#include <time.h>
#include <memory>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

#ifdef _WIN32
#define strtime _strtime
#define strdate _strdate
#else
#define strtime
#define strdate
#endif

#define HA_DEFAULT_BUF_SIZE 30

int ierr;
CFileLog::CFileLog()
: m_logLevel(LT_Debug)
, m_logFile(NULL), m_InterVal(5), m_MaxFileSize(100)
{
    m_timeOld = time(NULL) - 5;
	Initialize();
}

CFileLog::~CFileLog()
{
    
}

void CFileLog::Close()
{
    if (m_logFile)
    {
        fclose(m_logFile);
    }
    m_logFile = NULL;
}

// bool CFileLog::Initialize()
// {
//     Mutex lock();
//     m_configFilePath = "./HTLOG.INI";//configFilePath;
//     ApplySettings();
// 
//     return  Initialize();
// }

std::string CFileLog::GetLogFileName()
{
	char ExePath[MAX_PATH] = {0};
	GetModuleFileName(NULL, ExePath, MAX_PATH);
	strcat(ExePath, ".log");
	char *pMiddle = strrchr(ExePath, '\\');

	char LogFileName[MAX_PATH];
	strcpy(LogFileName, pMiddle+1);

	strcpy(pMiddle+1, "log\\");
	strcat(ExePath, LogFileName);

	return ExePath;
}


bool CFileLog::Initialize()
{
	m_configFilePath = LOG_CONFIG_FILE;//configFilePath;
	m_logFileName = GetLogFileName();
	ApplySettings();

	Close();

	m_logFile = _tfopen(m_logFileName.c_str(), _T("a+"));
	if (m_logFile==NULL)
	{
		ierr = GetLastError();
	}

    return true;
}

/*
enum LogType
{
LT_Debug,
LT_Information,
LT_Warning,
LT_Error,
LT_None
};
*/
void CFileLog::Log(const tchar* sourceName, LogType logType, const char *format, .../*const tchar* logData, ...*/)
{
    ApplySettings();

	va_list arg;
	tchar logData[LOG_DATA_LEN];

	va_start(arg, format);
	memset(logData, 0, sizeof(logData));
	//VSNPRINTF(logData, dataLen - 1, format, arg);
	_vsnprintf(logData, LOG_DATA_LEN - 1, format, arg);
	va_end(arg);

    if (m_logLevel == LT_None)
    {
        return;
    }

    if (m_logLevel == LT_Debug)
    {
        if (logType >= LT_Debug)
        {
            LogToFile(sourceName, logType, logData);
        }
    }
    else if (m_logLevel == LT_Information)
    {
        if (logType >= LT_Information)
        {
            LogToFile(sourceName, logType, logData);
        }
    }
    else if (m_logLevel == LT_Warning)
    {
        if (logType >= LT_Warning)
        {
            LogToFile(sourceName, logType, logData);
        }
    }
	else if(m_logLevel == LT_Error)
	{
		if (logType >= LT_Error)
		{
			LogToFile(sourceName, logType, logData);
		}
	}
    else
    {
        LogToFile(sourceName, logType, logData);
    }
}

void CFileLog::LogBin(const tchar* sourceName, LogType logType, const BYTE *pbyte, int nlen)
{
	char strinfo[128] = {0};
	strcpy(strinfo, "二进制信息：");
	int num = nlen, rowlen = nlen/COLUMN+((nlen%COLUMN)>0), 
		infolen = strlen(strinfo) + 2, bytelen = rowlen*(COLUMN*3), 
		regionlen = rowlen*REGION, textlen = nlen + rowlen * 2;
	nlen = infolen + bytelen + regionlen + textlen;

	std::shared_ptr<char> pbuff(new char[nlen+1]);
	memset(pbuff.get(), 0, nlen+1);

	strcpy(pbuff.get(), strinfo);
	strcat(pbuff.get(), "\r\n");

	int bindex = infolen, index = 0;
	while(index < num)
	{
		int a = TOTALCOLUMN;
		switch ((bindex - infolen)%TOTALCOLUMN)
		{
		case 48:
			{
				strncat(pbuff.get() + bindex, "       ", REGION);
				bindex += REGION;
				break;
			}
		case 52:
			{
				const void *p = CtrltoPoint(pbyte+index-COLUMN, COLUMN);
				memcpy(pbuff.get() + bindex, p, COLUMN);
				delete [] p;

				bindex += COLUMN;
				strcat(pbuff.get() + bindex, "\r\n");
				bindex += 2;
				break;
			}
		default:
			{
				sprintf(pbuff.get() + bindex, "%02X ", pbyte[index]);
				bindex += 3;
				index += 1;
			}
		}
	}

	int remainlen = COLUMN*3 - (bindex - infolen) % TOTALCOLUMN;
	strncat(pbuff.get() + bindex, ".. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..", remainlen);
	bindex += remainlen;
	strncat(pbuff.get() + bindex, "            ", REGION);
	bindex += REGION;
	int tailen = index % COLUMN;
	tailen = tailen?tailen:COLUMN;
	const void *p = CtrltoPoint(pbyte+index-tailen, tailen);
	memcpy(pbuff.get() + bindex, p, tailen);
	delete [] p;

	Log(sourceName, logType, pbuff.get());
}

void *CFileLog::CtrltoPoint(const unsigned char *p, int nlen)
{
	unsigned char *temp = new unsigned char[nlen];
	memcpy(temp, p, nlen);
	for (int i = 0; i < nlen; ++i)
	{
		if (p[i] == 0)
		{	
			temp[i] = '.';
		}
	}
	return temp;
}

void GetFilePath(char *cPath)
{
// 	LPSTR lpPath;
// 	char buffer[MAX_PATH] = {0};
// 	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH在WINDEF.h中定义了，等于260  
// 	memset(exeFullPath,0,MAX_PATH);  
// 	lpPath = buffer;
// 
// 	GetModuleFileName(NULL,exeFullPath,MAX_PATH);  
// 
// 	string str;
// 	str = exeFullPath;
// 	int pos3 = str.find("htmonitor.exe");
// 	//int pos3 = str.find("htmonitor.exe");
// 	if (pos3 >-1)  
// 	{  
// 		const char* ch=str.c_str();
// 		memcpy(buffer,ch,pos3);
// 	} 
	char buffPath[100] = {0};
	GetWindowsDirectory(buffPath,100);
	strcat(buffPath,"\\SecConfig.ini");
	memcpy(cPath,buffPath,strlen(buffPath));
}

void CFileLog::ReadString(tchar *pSection, tchar *pValue)
{

	char cPath[1024] = {0};
	GetFilePath(cPath);

	GetPrivateProfileString("HTLOG", pSection, NULL, pValue, MAX_PATH, cPath);
	//printf("pValue:%s",pValue);
}

unsigned CFileLog::ReadInt(tchar *pSection)
{
	char cPath[1024] = {0};
	GetFilePath(cPath);
	return GetPrivateProfileInt("HTLOG", pSection, 0, cPath);
}

const tchar* CFileLog::LogTypeToString(LogType logType)
{
	if (logType == LT_Debug)
	{
		return LTT_Debug;
	}
	else if (logType == LT_Warning)
	{
		return LTT_Warning;
	}
	else if (logType == LT_Error)
	{
		return LTT_Error;
	}
	else
	{
		return LTT_Information;
	}
}

LogType CFileLog::StringToLogLevel(const tchar* level)
{
	if (stricmp(level, LTT_Debug) == 0)
	{
		return LT_Debug;
	}
	else if (stricmp(level, LTT_Information) == 0)
	{
		return LT_Information;
	}
	else if (stricmp(level, LTT_Warning) == 0)
	{
		return LT_Warning;
	}
	else if (stricmp(level, LTT_Error) == 0)
	{
		return LT_Error;
	}
	else
	{
		return LT_None;
	}
}

void CFileLog::LogToFile(const tchar* sourceName, LogType logType, const tchar* logData)
{
	m_Mutex._Lock();
    
    if (!m_logFile)
    {
		m_Mutex._unlock();
        return;
    }

    tchar timebuf[32];
    tchar dateBuf[32];

    strtime(timebuf);
    strdate(dateBuf);
    fprintf(m_logFile, _T("[%s %s] [%s] [%s]: %s\n"), dateBuf, timebuf, LogTypeToString(logType), sourceName, logData);
#ifdef LOG_TO_STD
	printf(_T("[%s %s] [%s] [%s]: %s\n"), dateBuf, timebuf, LogTypeToString(logType), sourceName, logData);
#endif
    fflush(m_logFile);
	m_Mutex._unlock();
}

inline void CFileLog::ApplySettings()
{
	m_Mutex._Lock();

	Close();
	struct stat st;
	stat(m_logFileName.c_str(), &st);
	if (st.st_size >= m_MaxFileSize*1024*1024)
	{
		std::string LogFileBak(m_logFileName+".bak");
		DeleteFile(LogFileBak.c_str());
		rename(m_logFileName.c_str(), LogFileBak.c_str());
	}

	m_logFile = _tfopen(m_logFileName.c_str(), _T("a+"));
	if (m_logFile==NULL)
	{
		ierr = GetLastError();
	}

    time_t timeNew = time(NULL);
    if (timeNew - m_timeOld < m_InterVal)
    {
		m_Mutex._unlock();
        return;
    }
    tchar szValue[MAX_PATH];
    bool settingChanged = false;

    ReadString(_T("Level"), szValue);
    m_logLevel = StringToLogLevel(szValue);

	m_MaxFileSize = ReadInt(_T("LogMaxSize"));
	m_InterVal = ReadInt(_T("Interval"));
    m_timeOld = timeNew;

	m_Mutex._unlock();
}