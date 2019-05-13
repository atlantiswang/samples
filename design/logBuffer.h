//数据缓冲类
#ifndef LOGBUFFER_H
#define LOGBUFFER_H
#include <pthread.h>
#include <list>
#include "data.h"

class LogBuffer
{
private:
	pthread_mutex_t m_mutex;//互斥量
	pthread_cond_t m_cond;//条件变量
	pthread_cond_t p_cond;
	list<MLogRec> m_logs;//链表作为缓冲池
public:
	//构造函数
	LogBuffer(void);
	//向缓冲池中放入数据的函数
	LogBuffer& operator<< (const MLogRec& log);
	//从缓冲池中取出数据
	LogBuffer& operator>> (MLogRec& log);
};

//声明一个全局对象，提供给其他程序使用
extern LogBuffer g_logBuffer;

#endif
