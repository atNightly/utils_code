#include <iostream>
#include <typeinfo>

using namespace std;

//auto 类型推到

int main()
{
	auto variable = 1.0;
	cout << "Type of variable: " << typeid(variable).name() << endl;
	return 0;		
}
