#include <iostream>
using  namespace std;

class obj1
{
public:
	int x = 4;
	char c = 'A';
};

class obj2:public obj1
{
public:
	char b = 'c';
};

int main()
{
	obj1 *o1;
	obj2 *o2;
	cout << sizeof(o1) << endl;
	cout << sizeof(o2) << endl;
	o2 = o1
	cout << o2.b << endl;
}
