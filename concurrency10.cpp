#include <condition_variable>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <stack>
#include <vector>
#include <unistd.h>
using namespace std;

condition_variable condition;
mutex queueMutex;
vector<int> data;

void ThreadTask1(void)
{
	while(1)
	{
		queueMutex.lock();
		data.push_back(1);
		cout << "insert data to queue" << endl;
		queueMutex.unlock();
		condition.notify_one();
		sleep(1);
	}
}

void ThreadTask2(void)
{
		unique_lock<mutex> lock(queueMutex);
		function<bool()> predicate{
			[]()
			{
				return !data.empty();
			}
		};
		while(1) {
			condition.wait(lock,predicate);
			data.pop_back();
			cout << "construm data" << endl;
		}
}

int main(int argc,char* argv[])
{
	
	thread myThread1{ThreadTask1};
	thread myThread3{ThreadTask1};
	thread myThread4{ThreadTask1};
	thread myThread5{ThreadTask1};
	thread myThread2{ThreadTask2};
	
	myThread1.join();
	myThread2.join();
	myThread3.join();
	myThread4.join();
	myThread5.join();
	
}
