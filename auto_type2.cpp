#include <iostream>
#include <typeinfo>

using namespace std;


class MyClass
{
	
};

int main()
{
	auto variable = MyClass();
	cout << "Type of Variable: " << typeid(variable).name() << endl;
	return 0;
}
