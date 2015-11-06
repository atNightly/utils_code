#include <iostream>
#include <unistd.h>
#include <sys/prctl.h>
#include <pthread.h>

using namespace std;

void* thread_func(void* data)
{
	cout << "I am child thread" << endl;
	prctl(PR_SET_NAME,"test");
	while(1);
}

int main()
{
		pthread_t tid;
		pthread_create(&tid,NULL,thread_func,NULL);
		pthread_join(tid,NULL);
}
