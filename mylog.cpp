#include "mylog.h"
#include <time.h>

int g_fun_level = 1;

stackclass::stackclass(const char *fun_name):m_strlog(fun_name),m_level(g_fun_level++)
{
	char szTab[128] = {0};
	char szTemp[128] = {0};
	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s-> %s()", szTab, m_strlog.c_str());

	get_log_instance().logtofile(szTemp);
}

stackclass::~stackclass()
{
	char szTab[128] = {0};
	char szTemp[128] = {0};

	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s<- %s()", szTab, m_strlog.c_str());
	get_log_instance().logtofile(szTemp);
	g_fun_level--;
}

void msglog::logstring(const char *szformat, ...)
{
#if 0
	simple_va_fun(4, 23, 43, 54, 32);
	void simple_va_fun(int i, ...) 
	{ 
		va_list arg_ptr; 
		int j=0; 
		va_start(arg_ptr, i); 
		j=va_arg(arg_ptr, int); 
		int k = va_arg(arg_ptr, int);
		va_end(arg_ptr); 
		printf("%d %d %d\n", i, j, k); 
		// 4 23 43
		return; 
	}
#endif	
	
	va_list valist;
	char szbuff[128] = {0};
	va_start(valist, szformat);
	_vsnprintf(szbuff, 128, szformat, valist);
	va_end(valist);
	logtofile(szbuff);
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

	logtofile(strinfo);
	logtofile(pbuff);
}

void msglog::logtofile(const char *pszlog)
{
	time_t t;
	time(&t);

	struct tm* time_s;
	time_s = localtime(&t);

	char log[1024] = {0};
	sprintf(log, "%02d/%02d %02d:%02d:%02d [%d--%d] %s", 
		time_s->tm_mday, time_s->tm_mon + 1, time_s->tm_hour, time_s->tm_min, time_s->tm_sec,
		GetCurrentProcessId(), GetCurrentThreadId(), pszlog);
	fwrite(log, 1, strlen(log), m_fp);
	fputs("\n\n", m_fp);
}

msglog &get_log_instance()
{
	static msglog gs_log;
	return gs_log;
}