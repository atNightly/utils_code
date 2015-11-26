#ifndef _LIB_CONDITION_H_
#define _LIB_CONDITION_H_

#include "Mutex.h"
#include "Condition.h"
#include <boost/noncopyable.hpp>

class Condition;
class CountDownLatch: boost::noncopyable
{
    public:
        explicit CountDownLatch(int count);
        
        void wait();
        
        void countDown();
        
        void getCount()const;
    
    private:
        mutable Mutex m_mutex;
        Condition m_cond;
        int m_count;
    
};

#endif //_LIB_CONDITION_H_
