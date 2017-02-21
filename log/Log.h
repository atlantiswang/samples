//*****************************************************************************
//  Copyright (c) 2009 Shenzhen Surfilter Network Technology Co., Ltd. 
//  All Rights Reserved.
//
//  Module Name:
//      Log.h ILog接口声明，定义ILog的各个接口功能
//
//  Abstract:
//      ILog是HostAudit系统中的系统日志接口，用来记录系统运行过程中的日志。
//
//  Notes:
//
//  Created: 2009/09/09
//*****************************************************************************

#ifndef _LOG_H_
#define _LOG_H_
#include <windows.h>
#include <tchar.h>
#include <string>
//#include "Utility/Platform.h"
#include <stdio.h>
#define  VSNPRINTF _vsnprintf;
#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif
#define LOG_CONFIG_FILE "./HTLOG.ini"
typedef TCHAR tchar;

// enum LogLevel
// {
//     LL_None,
//     LL_Verbose,
//     LL_Brief,
//     LL_Warning,
//     LL_Critical
// };

enum LogType
{
    LT_Debug,
    LT_Information,
    LT_Warning,
    LT_Error,
	LT_None
};

class ILog
{
public:
    //+--------------------------------------------------------------------------
    //  Method:     Log         [ILog]
    //  Synopsis:   记录系统运行日志
    //  Arguments:  [in] sourceName
    //                   记录日志的模块名称
    //              [in] logType
    //                   enum LogType中定义的日志类型
    //              [in] logData
    //                   日志字符串。
    //  Returns:    无
    //+--------------------------------------------------------------------------
	virtual void Log(const tchar* sourceName, LogType logType, const char *format, ...) =0;

	virtual void LogBin(const tchar* sourceName, LogType logType, const BYTE *logData, int nLen) = 0;
};

#endif
