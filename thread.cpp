#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <pthread.h>

//基于对象的编程,面向对象的编程依托于继承自抽象类，实现虚接口来实现

using namespace std;

class Thread
{
	public:
		typedef boost::function<void ()> Threadfunc; 
		explicit Thread(const Threadfunc& data);//初始化，传入一个函数对象
		~Thread();
		int Start();
		int Join();
	private:
		pthread_t m_pthreadid;
		static void* ThreadRoute(void *arg); //Strat来调用
		void Run();
		Threadfunc m_func;
		bool m_autodelete;
		
};

Thread::Thread(const Threadfunc& data):m_func(data),m_autodelete(false)
{
	cout << "construct a object" << endl;
}

Thread::~Thread()
{
	cout << "desconstruct a object" << endl;
}

int Thread::Start()
{
	return pthread_create(&m_pthreadid,NULL,ThreadRoute,(void*)this);
}

int Thread::Join()
{
	return pthread_join(m_pthreadid,NULL);
}

void Thread::Run()
{
	m_func();
}

void* Thread::ThreadRoute(void *arg)
{
	Thread *p = (Thread *)arg;
	p->Run();
	if (p->m_autodelete)
		delete p;
	return NULL;
}

void func()
{
	int count  = 5;
	while(count--) cout << "Hello World" << count << endl;
}

int main()
{
	Thread th(boost::bind(&func));
	th.Start();
	th.Join();
}	

