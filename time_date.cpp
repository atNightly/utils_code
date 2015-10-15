#include <ctime>
#include <chrono>
#include <iostream>
#include <typeinfo>
using namespace std;
using namespace chrono; //时间相关

int main()
{
	auto currentTimePoint = system_clock::now(); //获取当前时间，返回的是一个std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long, std::ratio<1l, 1000000000l> > >
	auto currentTime = system_clock::to_time_t(currentTimePoint);
	auto timeText = ctime(&currentTime);
	cout << typeid(timeText).name() << endl;
	cout << typeid(currentTime).name() << endl;
	cout << typeid(currentTimePoint).name() << endl;
	cout << timeText << endl;
	return 0;
}

