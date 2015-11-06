#include <iostream>
#include <pthread.h>


template<typename T>
class ThreadLocal
{
public:
		ThreadLocal()
		{
			pthread_key_create(&m_key,&ThreadLocal::destructor);
		}

		~ThreadLocal()
		{
			pthread_key_delete(m_key);
		}
		T& value()
		{
			T* thread_value = static_cast<T*>(pthread_getspecific(m_key));
			if (!thread_value) {
				T* newObj = new T();
				pthread_setspecific(m_key,newObj);
				thread_value = newObj;
			}
			return *thread_value;
		}
private:
		static void destructor(void *x)
		{
			T* obj = static_cast<T*>(x);
			delete obj;
		}
		pthread_key_t m_key;
};

