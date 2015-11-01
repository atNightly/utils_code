#include <iostream>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <stack>
#include <thread>
#include <vector>
#include <unistd.h>
using namespace std;


mutex s_mutex;
int count = 0;

void ThreadTask1()
{
	int t = 1000;
	s_mutex.lock();
	cout << "I am therad1" << endl;
	while(t--) {
		count++;
		cout << count << endl;
		sleep(1);
	}
	s_mutex.unlock(); 
}

void ThreadTask2()
{
	int t = 1000;
	s_mutex.lock();
	cout << "I am therad2" << endl;
	while(t--) {
	count++;
	cout << count << endl;
	}
	s_mutex.unlock(); 
}
int main()
{
	thread Mythread1{ ThreadTask1};
	thread Mythread2{ ThreadTask2};
	thread Mythread3{ ThreadTask1};
	thread Mythread4{ ThreadTask2};
	thread Mythread5{ ThreadTask1};
	Mythread1.join();
	Mythread2.join();
	Mythread3.join();
	Mythread4.join();
	Mythread5.join();
	return 0;
}
