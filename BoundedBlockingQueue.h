#include "Mutex.h"
#include "Condition.h"
#include <boost/circular_buffer.hpp>
#include <assert.h>


template<typename T>
class BoundedBlockingQueue : boost::noncopyable
{
    public:
        explicit BoundedBlockingQueue(int maxSize)
            :m_mutex(),
            m_notempty(m_mutex),
            m_notfull(m_mutex),
            m_queue(maxSize)
        {
                
        }
        
        void put(const T& x)
        {
            MutexLockGuard lock(m_mutex);
            while(m_queue.full())
            {
                m_notfull.wait();       
            }
            assert(!m_queue.full());
            m_queue.push_back(x);
            m_notempty.notify();
        }

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
            m_notfull.notify();
            return front;
        }

        bool empty()const
        {
            MutexLockGuard lock(m_mutex);
            return m_queue.empty();        
        }

        bool full()const
        {
            MutexLockGuard lock(m_mutex);
            return m_queue.full();    
        }

        size_t size()const
        {
            MutexLockGuard lock(m_mutex);
            return m_queue.size();   
        }

        size_t capacity()const
        {
            MutexLockGuard lock(m_mutex);
            return m_queue.capacity();    
        }
    private:
        Mutex m_mutex;
        Condition m_notempty;
        Condition m_notfull;
        boost::circular_buffer<T> m_queue;
};
