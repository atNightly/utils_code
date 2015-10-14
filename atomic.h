#ifndef _LIB_ATOMIC_H_
#define _LIB_ATOMIC_H_
#include <boost/noncopyable.hpp>
#include <stdint.h>

template<typename T>
class Atomic: boost::noncopyable
{
  public:
	Atomic():m_value(0)
	{
		
	}
	
	T get()
	{
		return __sync_val_compare_and_swap(&m_value,0,0); //不等于0则返回value本身，否则置为0后再返回设置之前的值
	}

	T getAndAdd(T x)
	{
		return __sync_fetch_and_add(&m_value,x);
	}

	T addAndGet(T x)
	{
		return getAndAdd(x) + x;
	}

	T incrementAndGet()
	{
		return addAndGet(1);
	}

	T decrementAndGet()
	{
		return addAndGet(-1);
	}

	void add(T x)
	{
		getAndAdd(x);
	}

	void increment()
	{
		incrementAndGet();
	}

	void decrement()
	{
		decrementAndGet();
	}

	T getAndSet(T newValue)
	{
		return __sync_lock_test_and_set(&m_value,newValue);
	}
  private:
	volatile T m_value;
};

typedef Atomic<int32_t> AtomicInt32;
typedef Atomic<int64_t> AtomicInt64;


#endif //end of _LIB_ATOMIC_H_
