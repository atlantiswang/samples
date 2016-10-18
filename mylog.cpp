#include "mylog.h"
#include <time.h>
#include <memory>
#include <map>
#include <sys/stat.h>

static CRITICAL_SECTION gs_mutex;
static CRITICAL_SECTION gs_fun_mutex;
static std::map<unsigned, int> gs_level;

void msglog::log(const char *pszlog, unsigned short color)
{
	threadmutex raii_lock;
	time_t t;
	time(&t);

	struct tm* time_s;
	time_s = localtime(&t);

	std::shared_ptr<char> logs(new char[strlen(pszlog)+1+256]);
	sprintf(logs.get(), "%02d/%02d %02d:%02d:%02d [%d--%d] %s", 
		time_s->tm_mday, time_s->tm_mon + 1, time_s->tm_hour, time_s->tm_min, time_s->tm_sec,
		GetCurrentProcessId(), GetCurrentThreadId(), pszlog);

#ifdef LOG_TO_STD
	OutputDebugStringA(logs.get());//(pszlog);

	SetConsoleTextAttribute(m_console_handle, color);
	puts(logs.get());//(pszlog);
	SetConsoleTextAttribute(m_console_handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
#endif
	
#ifdef LOG_TO_FILE
	char szfilename[MAX_PATH] = {0};
	GetTempPathA(MAX_PATH, szfilename);
	strcat_s(szfilename, MAX_PATH, LOG_FILE_NAME);

	struct stat st;
	stat(szfilename, &st);
	if(st.st_size > MAX_FILE_SIZE)
	{
		remove(szfilename);
		Sleep(400);
	}

	FILE *m_fp;
	m_fp = fopen(szfilename, "a");
	fwrite(logs.get(), 1, strlen(logs.get()), m_fp);
	fputs("\n\n", m_fp);
	fclose(m_fp);
	m_fp = NULL;
#endif
}

stackclass::stackclass(const char *fun_name):m_strlog(fun_name)
{	
	m_thread_id = GetCurrentThreadId();
	EnterCriticalSection(&gs_fun_mutex);
	std::map<unsigned, int>::iterator it = gs_level.find(m_thread_id);

	if (it != gs_level.end())
	{
		gs_level[m_thread_id]++;
	}else{
		gs_level[m_thread_id] = 0;
	}
	LeaveCriticalSection(&gs_fun_mutex);
	m_level = gs_level[m_thread_id];

	char szTab[128] = {0};
	char szTemp[128] = {0};
	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s-> %s()", szTab, m_strlog.c_str());

	get_log_instance().log(szTemp, m_thread_id%14 + 2);
}

stackclass::~stackclass()
{
	char szTab[128] = {0};
	char szTemp[128] = {0};

	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s<- %s()", szTab, m_strlog.c_str());
	get_log_instance().log(szTemp, m_thread_id%14 + 2);

	EnterCriticalSection(&gs_fun_mutex);
	if(--gs_level[m_thread_id] == -1)
	{
		gs_level.erase(gs_level.find(m_thread_id));
	}
	LeaveCriticalSection(&gs_fun_mutex);
}

void msglog::logstring(const char *szformat, ...)
{	
	va_list valist;
	char szbuff[1024] = {0};
	va_start(valist, szformat);
	_vsnprintf(szbuff, 1024, szformat, valist);
	va_end(valist);

	log(szbuff);
}

void msglog::logstring(const wchar_t *szformat, ...)
{	
	va_list valist;
	wchar_t szbuff[1024] = {0};
	va_start(valist, szformat);
	_vsnwprintf(szbuff, 1024, szformat, valist);
	va_end(valist);

	int heapLen = WideCharToMultiByte(CP_ACP, 0, szbuff, -1, NULL, 0, NULL, NULL);
	char *ansi_buff = new char[heapLen];
	WideCharToMultiByte(CP_ACP, 0, szbuff, -1, ansi_buff, heapLen, NULL, NULL);

	log(ansi_buff);
	delete [] ansi_buff;
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
	delete [] pbuff;
}


threadmutex::threadmutex()
{
	EnterCriticalSection(&gs_mutex);
}

threadmutex::~threadmutex()
{
	LeaveCriticalSection(&gs_mutex);
}

msglog &get_log_instance()
{
	static msglog gs_log;
	return gs_log;
}

msglog::msglog()
{
	InitializeCriticalSection(&gs_mutex);
	InitializeCriticalSection(&gs_fun_mutex);
	m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}
msglog::~msglog()
{
	DeleteCriticalSection(&gs_mutex);
	DeleteCriticalSection(&gs_fun_mutex);
	CloseHandle(m_console_handle);
}