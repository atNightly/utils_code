#ifndef _LIB_BLOCKQUEUE_H_
#define _LIB_BLOCKQUEUE_H_

#include "Condition.h"
#include "Mutex.h"
#include <boost/noncopyable.hpp>
#include <deque>
#include <assert.h>
#include <boost/circular_buffer.hpp>

using namespace std;
template<typename T> 
class BlockingQueue : boost::noncopyable
{
    public:
        BlockingQueue()
            :m_mutex(),
            m_notempty(m_mutex),
            m_queue()
        {
            
        }

        void put(const T& x)
        {
            MutexLockGuard lock(m_mutex);
            m_queue.push_back(x);
            m_notempty.notify();
        }
        //T 是 copyable
        T take()
        {
            MutexLockGuard lock(m_mutex);
            while(m_queue.empty())
            {
                m_notempty.wait();    
            }
            assert(!m_queue.empty());
            T front(m_queue.front());
            m_queue.pop_front();
            return front;
        }
        size_t size()const
        {
            MutexLockGuard lock(m_mutex);
            return m_queue.size();  
        }
    private:
        Mutex m_mutex;
        Condition m_notempty;
        deque<T> m_queue;
};



#endif //end of _LIB_BLOCKQUEUE_H_
