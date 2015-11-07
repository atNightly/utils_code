#ifndef LIB_MUTEX_H_
#define LIB_MUTEX_H_

#include <iostream>
#include <pthread.h>
#include <boost/noncopyable.hpp>

class Mutex:boost::noncopyable
{

public:
	Mutex():m_mutex(PTHREAD_MUTEX_INITIALIZER)
	{
			//do nothing
	}	

	~Mutex()
	{
		pthread_mutex_destroy(&m_mutex);
	}

	int Lock()
	{
		return pthread_mutex_lock(&m_mutex);
	}

	pthread_mutex_t *get_mutex()
	{
		return &m_mutex;
	}

	int Unlock()
	{
		return pthread_mutex_unlock(&m_mutex);
	}

private:
	pthread_mutex_t m_mutex;
};

class MutexLockGuard:boost::noncopyable
{
	public:	
		MutexLockGuard(Mutex &mutex):m_mutex(mutex) {
			m_mutex.Lock();
		}

		~MutexLockGuard() {
			m_mutex.Unlock();
		}
	private:
		Mutex& m_mutex;
};
#endif //end of LIB_MUTEX_H_
