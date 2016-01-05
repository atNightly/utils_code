#ifndef _LIB_SINGLETON_H_
#define _LIB_SINGLETON_H_
#include <boost/noncopyable.hpp>
#include <pthread.h>

template<typename T>
class Singleton : boost::noncopyable
{
    public:
        static T& instance()
        {
            pthread_once(&m_ponce,&Singleton::init);
            return *m_value;    
        }
    private:
        Singleton();
        ~Singleton();
        static void init()
        {
            m_value = new T();    
        }
        static pthread_once_t m_ponce;
        static T* m_value;
};

template<typename T>
pthread_once_t Singleton<T>::m_ponce = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::m_value = NULL;
#endif //end of _LIB_SINGLETON_H_
