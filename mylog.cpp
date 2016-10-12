#include "stdafx.h"
#include "mylog.h"
#include <time.h>
#include <memory>
#include <vld.h>

//此处使用的全局变量线程不安全，需要改进，暂时不要使用FUN_IN功能
int g_fun_level = 1;

//最终的日志输出口
void msglog::log(const char *pszlog)
{
	time_t t;
	time(&t);

	struct tm* time_s;
	time_s = localtime(&t);

	std::shared_ptr<char> logs(new char[strlen(pszlog)+1+256]);
	sprintf(logs.get(), "%02d/%02d %02d:%02d:%02d [%d--%d] %s", 
		time_s->tm_mday, time_s->tm_mon + 1, time_s->tm_hour, time_s->tm_min, time_s->tm_sec,
		GetCurrentProcessId(), GetCurrentThreadId(), pszlog);

#ifdef LOG_TO_STD
	OutputDebugStringA(pszlog);
	puts(pszlog);
#endif
	
#ifdef LOG_TO_FILE
	char szfilename[128] = {0};
	GetTempPathA(128, szfilename);
	strcat_s(szfilename, 128, LOG_FILE_NAME);
	FILE *m_fp;
	m_fp = fopen(szfilename, "a");

	fwrite(logs.get(), 1, strlen(logs.get()), m_fp);
	fputs("\n\n", m_fp);
	fclose(m_fp);
	m_fp = NULL;
#endif
}

stackclass::stackclass(const char *fun_name):m_strlog(fun_name),m_level(g_fun_level++)
{
	char szTab[128] = {0};
	char szTemp[128] = {0};
	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s-> %s()", szTab, m_strlog.c_str());

	get_log_instance().log(szTemp);
}

stackclass::~stackclass()
{
	char szTab[128] = {0};
	char szTemp[128] = {0};

	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s<- %s()", szTab, m_strlog.c_str());
	get_log_instance().log(szTemp);
	g_fun_level--;
}

void msglog::logstring(const char *szformat, ...)
{	
	va_list valist;
	char szbuff[128] = {0};
	va_start(valist, szformat);
	_vsnprintf(szbuff, 128, szformat, valist);
	va_end(valist);
	log(szbuff);
}

void msglog::logbinary(char *strinfo, const char *pbyte, int nlen)
{
	int oldlen = nlen;
	nlen = nlen*3 +nlen/COLUMN;
	char *pbuff = new char[nlen+1];
	memset(pbuff, 0, nlen);
	for(int i = 0, j = 0; i < nlen && j < oldlen; i+= 3, j++)
	{
		sprintf(pbuff + i, "%02X ", pbyte[j]);
		if ((j+1)%16 == 0)
		{
			sprintf(pbuff + i + 2, "\r\n");
			i++;
		}
	}

	log(strinfo);
	log(pbuff);
}

msglog &get_log_instance()
{
	static msglog gs_log;
	return gs_log;
}