//数据缓冲类
#include "logBuffer.h"

//构造函数
LogBuffer::LogBuffer(void)
{
	//初始化互斥量
	pthread_mutex_init(&m_mutex,0);
	//初始化条件变量
	pthread_cond_init(&m_cond,0);
}

//向缓冲池中放入数据的函数
LogBuffer& LogBuffer::operator<< (const MLogRec& log)
{
	cout << "向缓冲池中放入数据开始..." << endl;
	
	//1.使用互斥量进行加锁
	pthread_mutex_lock(&m_mutex);
	//2.将指定的记录放入缓冲区中
	while(g_logBuffer.size() > 10*1024)
	{
		pthread_cond_wait(&p_cond, &m_mutex);
	}
	m_logs.push_back(log);
	//3.一旦生产，激活消费者
	pthread_cond_signal(&m_cond);
	//4.释放互斥锁
	pthread_mutex_unlock(&m_mutex);
	
	cout << "向缓冲池中放入数据结束" << endl;
	return *this;
}	

//从缓冲池中取出数据
LogBuffer& LogBuffer::operator>> (MLogRec& log)
{
	cout << "取出数据开始..." << endl;
	//1.使用互斥量加锁
	pthread_mutex_lock(&m_mutex);
	//2.判断链表是否为空
	while(m_logs.empty())
	{
		pthread_cond_wait(&m_cond,&m_mutex);
	}
	//3.取出链表中的数据，并从链表中移除
	log = m_logs.front();
	m_logs.pop_front();
	//pthread_cond_signal(&p_cond);
	pthread_cond_broadcast(&p_cond);
	//4.释放互斥锁
	pthread_mutex_unlock(&m_mutex);
	cout << "取出数据结束" << endl;
	return *this;
}

//定义一个全局对象，提供给其他程序使用
LogBuffer g_logBuffer;
