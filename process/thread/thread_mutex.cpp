/*
[]=========================================================================[]

	Copyright(C) 2000-2004, Feitian Technologies Co., Ltd.
	All rights reserved.

FILE:
	process_mutex.h

DESC:
	This is a mutex implementation only used inside a process.
	(Mutex for thread.)

REVISION:
	2004-03-21 [Euphen Liu]
		Created.
[]=========================================================================[]
*/
#include <es/thread_mutex.h>
#include <assert.h>
#if defined(NG_HAS_PTHREADS)
//#	include <thread/thread.h>
//#	include <pthread.h>
#	include <errno.h>
#endif


//namespace our_test_namespace
//{

ThreadMutex::ThreadMutex()/// :
//	m_bLock(false)
{
#if defined(NG_HAS_WINTHREADS)
    InitializeCriticalSection(&m_mutex);
#elif defined(NG_HAS_PTHREADS)
	m_LockedCounts = 0;
	m_threadid = 0;
	int res = 0;
	res = pthread_mutex_init(&m_mutex, 0);
//	if (res != 0)
//		throw thread_resource_error();
#else
#	error("Can not support such platform.")
#endif
}

ThreadMutex::~ThreadMutex()
{
#if defined(NG_HAS_WINTHREADS)
	LeaveCriticalSection(&m_mutex);
    DeleteCriticalSection(&m_mutex);
#elif defined(NG_HAS_PTHREADS)
	int res = 0;
	res = pthread_mutex_destroy(&m_mutex);
	assert(res == 0);
#else
#	error("Can not support such platform.")
#endif
}

void ThreadMutex::Lock(void)
{
#if defined(NG_HAS_WINTHREADS)
    EnterCriticalSection(&m_mutex);
#elif defined(NG_HAS_PTHREADS)
	if(m_threadid == (ES_ULONG)pthread_self())
	{
		m_LockedCounts++;
		return;
	}
	int res = 0;
	res = pthread_mutex_lock(&m_mutex);
//	if (res == EDEADLK)
//		throw lock_error();
	assert(res == 0);
	m_threadid = (ES_ULONG)pthread_self();
	m_LockedCounts = 1;
#else
#	error("Can not support such platform.")
#endif
}

void ThreadMutex::Unlock(void)
{
#if defined(NG_HAS_WINTHREADS)
    LeaveCriticalSection(&m_mutex);
#elif defined(NG_HAS_PTHREADS)
	if((m_threadid != (ES_ULONG)pthread_self()) || (m_LockedCounts <= 0))
	{
		return;
	}
	m_LockedCounts--;
	if(m_LockedCounts > 0)
	{
		return;
	}
	m_threadid = 0;
	int res = 0;
	res = pthread_mutex_unlock(&m_mutex);
//	if (res == EPERM)
//		throw lock_error();
	assert(res == 0);
#else
#	error("Can not support such platform.")
#endif
}
/////////////////////////////////////////////////////////////////////////////
//InterlockedIncrement && InterLockedDecrement
#if defined(linux) || defined(macintosh)
	ThreadMutex g_thread_mutex_interlocked;
#endif

ES_LONG InterlockedIncrement(ES_LONG_PTR ref)
{
#if defined(WIN32)
	return ::InterlockedIncrement((ES_LONG volatile *)ref);
#else
	ThreadMutexHolder locker(g_thread_mutex_interlocked);
	++(*ref);
	return *ref;
#endif

	
}

ES_LONG InterlockedDecrement(ES_LONG_PTR ref)
{
#if defined(WIN32)
	return ::InterlockedDecrement((ES_LONG volatile *)ref);
#else
	ThreadMutexHolder locker(g_thread_mutex_interlocked);
	--(*ref);
	return   *ref;
#endif
	
}
