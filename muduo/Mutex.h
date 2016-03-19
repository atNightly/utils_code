#ifndef _S_LIB_H_
#define _S_LIB_H_

#include <pthread.h>
#include <boost/noncopyable>

namespace s_lib
{
    class Mutex : public boost::noncopyable
    {
        public:
            Mutext():m_mutex(PTHREAD_MUTEX_INITIALIZER)
            {
                //do nothing;
            }

            int Lock()
            {
                return pthread_mutex_lock(m_mutex);
            }

            int Unlock()
            {
                return pthread_mutex_unlock(m_mutex);
            }

            pthread_mutext_t* getlock()
            {
                return &m_mutex;
            }

            ~Mutex()
            {
                pthread_mutex_destroy(&m_mutex);
            }
        private:
            bool is_lock;
            pthread_mutext_t m_mutex;
    };
}

#endif //end of _S_LIB_H_
