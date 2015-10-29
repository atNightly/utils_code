#include <iostream>

using namespace std;

template<typename T>

T Add(const T& a,const T& b)
{
	return a + b;
}

int main()
{
	Add(4,5);
	Add(4,5.4);
	Add<int>(4,6.5);
}
