#include <iostream>
#include <thread>

using namespace std;

void ThreadTask()
{
   for(unsigned int i{0};i < 20;++i)
   {
	cout << "Output from thread" << endl;
   }
}

int main(int argc,char* argv[])
{
	const unsigned int numbreOfProcess{thread::hardware_concurrency()};
	cout << "This system can run " << numbreOfProcess << "concurrent tasks" << endl;

	if (numbreOfProcess > 1)
	{
		thread myThread{ ThreadTask };
		cout << "Output from main" << endl;
	} else {
		cout << "CPU does not have multiple cores" << endl;
	}
	return 0;
}
