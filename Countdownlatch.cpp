#include "Mutex.h"
#include "Condition.h"
#include "Countdownlatch.h"
#include <boost/noncopyable.hpp>

CountDownLatch::CountDownLatch(int count)
    :m_mutex(),
     m_cond(m_mutex),
     m_count(count)
{
    
}

void CountDownLatch::wait()
{
    MutexLockGuard lock(m_mutex);
    while(m_count > 0)
    {
        m_cond.wait();       
    }
}
        
void CountDownLatch::countDown()
{
    MutexLockGuard lock(m_mutex);
    --m_count;
    if (m_count == 0)
    {
        m_cond.notifyAll();    
    }
}
        
void CountDownLatch::getCount()const
{
    MutexLockGuard lock(m_mutex);
    return m_count;
}
    

#endif //_LIB_CONDITION_H_
