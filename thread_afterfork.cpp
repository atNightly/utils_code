#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void before_fork()
{
	cout << "string fork" << endl;
} //end of before_fork


void parent_fork()
{
	cout << "fork after parent" << endl;
} //end of parent_fork

void child_fork()
{
	cout << "fork after child" << endl;
} //end of child_fork()

void* handler(void* data)
{
	cout << "I am a child thread" << endl;
	if (fork() == 0) {
		
			cout << "I am child" << endl;

	} else {

			cout << "I am parent" << endl;
	}
}

int main()
{	
	pthread_t tid;
	int c = 0;
	pthread_atfork(before_fork,parent_fork,child_fork);
	pthread_create(&tid,NULL,handler,NULL);
	pthread_join(tid,NULL);
}//end main()
