#include "mylog.h"
#include <time.h>
#include <memory>
#include <map>
#include <sys/stat.h>
#include <intrin.h>
#define NOCOLOR

static HANDLE gs_mutex;
static CRITICAL_SECTION gs_fun_mutex;
typedef struct _thread_info
{
	int num;
	short color;
}THREAD_INFO, *PTHREAD_INFO;

static std::map<unsigned, THREAD_INFO> gs_level;

enum{CRITICAL, MUTEX};
class threadmutex
{
public:
	threadmutex(bool bMutex = CRITICAL):m_bMutex(bMutex),m_locked(false){Lock();}
	~threadmutex(){UnLock();}
	
	void Lock(){
		if(m_locked == false)
		{
			if(m_bMutex == true)
			{
				WaitForSingleObject(gs_mutex, 10000);
			}
			else
			{
				EnterCriticalSection(&gs_fun_mutex);
			}
		}
		m_locked = true;
	}

	void UnLock()
	{
		if (m_locked == true)
		{
			if(m_bMutex == true)
			{
				ReleaseMutex(gs_mutex);
			}
			else
			{
				LeaveCriticalSection(&gs_fun_mutex);
			}
		}
		m_locked = false;
	}
private:
	bool m_bMutex;
	bool m_locked;
};

void msglog::log(const char *pszlog, unsigned short color)
{
	threadmutex logMutex(MUTEX);
	time_t t;
	time(&t);

	tm *time_s = localtime(&t);
	int n = strlen(pszlog);
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
	strcat_s(szfilename, MAX_PATH, m_filename.c_str());

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

unsigned short int stackclass::ms_color = 0;
stackclass::stackclass(const char *fun_name):m_strlog(fun_name)
{	
	msglog::get_log_instance();
	m_thread_id = GetCurrentThreadId();
	threadmutex stackmutex;
	std::map<unsigned, THREAD_INFO>::iterator it = gs_level.find(m_thread_id);

	if (it != gs_level.end())
	{
		gs_level[m_thread_id].num++;
	}else{
		gs_level[m_thread_id].num = 0;
		gs_level[m_thread_id].color = getcolor();
	}
	stackmutex.UnLock();
	m_level = gs_level[m_thread_id].num;

	char szTab[128] = {0};
	char szTemp[128] = {0};
	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s-> %s()", szTab, m_strlog.c_str());

	msglog::get_log_instance().log(szTemp, gs_level[m_thread_id].color);
}

unsigned short stackclass::getcolor()
{
#ifdef NOCOLOR
	return (FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
#endif
	if(ms_color >= 0x7FFC) 
		return (FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
	unsigned short int bit = 1<<(m_thread_id%13 +2);
	while ((bit & ms_color) == bit)
	{
		 bit = (((bit<<1)==0x8000)?(1<<2):(bit<<1));
	}
	ms_color |= bit;
	DWORD dwbit = 0;
	_BitScanForward(&dwbit, bit);
	return (unsigned short)dwbit;
}

stackclass::~stackclass()
{
	char szTab[128] = {0};
	char szTemp[128] = {0};

	for(int i = 0; i < m_level; ++i)
		strcat(szTab, "   ");
	sprintf(szTemp, "FUN %s<- %s()", szTab, m_strlog.c_str());
	msglog::get_log_instance().log(szTemp, gs_level[m_thread_id].color);
	
	threadmutex stackmutex;
	if(--gs_level[m_thread_id].num == -1)
	{
		ms_color &= ~(gs_level[m_thread_id].color);
		gs_level.erase(gs_level.find(m_thread_id));
	}
	stackmutex.UnLock();
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

const void *msglog::ctrltopoint(const unsigned char *p, int nlen)
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

void msglog::logbinary(char *strinfo, const unsigned char *pbyte, int nlen)
{
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
				const void *p = ctrltopoint(pbyte+index-COLUMN, COLUMN);
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
	const void *p = ctrltopoint(pbyte+index-tailen, tailen);
	memcpy(pbuff.get() + bindex, p, tailen);
	delete [] p;

	log(pbuff.get());
}

msglog &msglog::get_log_instance()
{
	static msglog gs_log;
	return gs_log;
}

stringa msglog::getfilename()
{
	char name[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, name, MAX_PATH);
	strcpy(name, strrchr(name, '\\') + 1);
	strcpy(strrchr(name, '.') + 1, "log");
	return (stringa)name;
}

msglog::msglog()
{
	InitializeCriticalSection(&gs_fun_mutex);
	m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	m_filename = getfilename();
	gs_mutex = CreateMutexA(NULL, FALSE, m_filename.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		puts("log exist");
	}
}
msglog::~msglog()
{
	CloseHandle(gs_mutex);
	DeleteCriticalSection(&gs_fun_mutex);
	CloseHandle(m_console_handle);
}