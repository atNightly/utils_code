#include <cstdlib>
#include <iostream>
#include <stack>
#include <thread>
#include <vector>

using namespace std;

thread_local unsigned int local1 = 500;

void ThreadTask()
{
	cout << local1 << endl;
	local1 =  100;
	cout << &local1 << endl;
}

void ThreadTask2()
{
	cout << local1 << endl;
	local1 = 200;
	cout << &local1 << endl;
}

int main(int argc,char* argv[])
{
	thread myThread{ ThreadTask };
	thread myThread2{ ThreadTask2 };
	myThread.join();
	myThread2.join();
	return 0;
}
