#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;
const int i = 5;

__thread int var = 10; 

void* worker1(void* arg);
void* worker2(void* arg);

int main()
{
	pthread_t pid1,pid2;
	static __thread int temp = 100;
	pthread_create(&pid1,NULL,worker1,NULL);
	pthread_create(&pid2,NULL,worker2,NULL);
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	cout << temp << endl;
	return 0;
}

void* worker1(void* arg) {
	cout << ++var << endl;
} //end of worker1(void* arg)


void* worker2(void* arg) {
	sleep(1);
	cout << ++var << endl;
}
