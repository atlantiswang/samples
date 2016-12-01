/*
[]=========================================================================[]

	Copyright(C), Feitian Technologies Co., Ltd.
	All rights reserved.

FILE:
	thread_mutex.h

DESC:
	There are some class wrap sync object.

REVISION:
	[2006-06-15 Apex Liu] Created.

[]=========================================================================[]
*/

#ifndef	__ES_CSP11_SYNC_WRAP_H__
#define __ES_CSP11_SYNC_WRAP_H__

// WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!! 
//
// Here 'Mutex' not what the Mutex under Win32 means.
// Actually, it is the CRITICAL_SECTION.
//


//#include <entersafe/config.h>
//#include <entersafe/noncopyable.h>
//#include <es/base_type.h>
#include <es/es_typedef.h>

#if defined(WIN32)
#	include <windows.h>
#elif defined(linux) || defined(macitosh)
#	include <pthread.h>
#	include <es/thread.h>
#endif

//namespace our_test_namespace
//{
//以前觉得这是个RIIA，但后来发现不是，他是封装了各平台的互斥，使用时注意要将这个类的实例做为全局变量
class ThreadMutex
{
//friend class CScopedLockThreadMutexHelper;

public:
	ThreadMutex();

	virtual ~ThreadMutex();

	void Lock(void);

	void Unlock(void);

private:
#if defined(WIN32)
	CRITICAL_SECTION m_mutex;
#elif defined(linux) || defined(macintosh)
	pthread_mutex_t m_mutex;
	ES_ULONG m_threadid;
	ES_ULONG m_LockedCounts;;
#endif
};

class ThreadMutexHolder
{
public:
	ThreadMutexHolder(ThreadMutex& mutex) : m_mutex(mutex)
	{
		m_mutex.Lock();
	}
	virtual ~ThreadMutexHolder()
	{
		m_mutex.Unlock();
	}
private:
	ThreadMutex& m_mutex;
};


ES_LONG InterlockedIncrement(ES_LONG_PTR ref);
ES_LONG InterlockedDecrement(ES_LONG_PTR ref);

//} // namespace our_test_namespace

#endif // __ES_CSP11_SYNC_WRAP_H__
