#include <cstdlib>
#include <iostream>
#include <mutex>
#include <stack>
#include <thread>
#include <vector>

using namespace std;

mutex s_Mutex;
int count = 0;

void threadtask1()
{
	lock_guard<mutex> lock{ s_Mutex };
	cout << "task1" << endl;
	int t = 10;
		while(t--) {
			count++;
		}
		cout << count << endl;
}

void threadtask2()
{
	lock_guard<mutex> lock{ s_Mutex };
	int t = 10;
	cout << "task2" << endl;
		while(t--) {
			count++;
		}
		cout << count << endl;
}

int main()
{
	thread Mythread1 { threadtask1 };
	thread Mythread2 { threadtask2 };

	Mythread1.join();
	Mythread2.join();
	return 0;
}
