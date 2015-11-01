#include <iostream>
#include <thread>

using namespace std;

void ThreadTask()
{
	for(unsigned int i = 0;i < 20;++i)
	{
		cout << "Output from thread" << endl;
	}
}

int main(int argc,char* argv[])
{

	const unsigned int numberOfProcess{ thread::hardware_concurrency() };
	cout << "This system can run" << numberOfProcess << "concurrent tasks" << endl;

	if(numberOfProcess > 1)
	{
		thread myThread{ ThreadTask };
		cout << "Output from main" << endl;
		myThread.detach();
	} else {
		cout << "CPU does not have multiple cores." << endl;
	}
	return 0;
}
