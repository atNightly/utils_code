#include <ctime>
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <typeinfo>
using namespace std;
using namespace chrono;

int main()
{
	auto startTimePoint = system_clock::now();
	sleep(3);	
	auto endTimePOint = system_clock::now();
	auto timeTaken = duration_cast<milliseconds>(endTimePOint - startTimePoint);
	cout << "timeTaken:" << typeid(timeTaken).name() << endl;
	cout << "Time Taken: " << timeTaken.count() << endl;
	return 0;
}
