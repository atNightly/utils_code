#include <iostream>
#include <typeinfo>

using namespace std;

class MyClass
{

};

int main()
{
	auto variable{1}; //这里本意是生成一个int类型，并初始化
	cout << "Type of variable: " << typeid(variable).name() << endl;
	auto variable2{ MyClass{} }; // 这里的本意则是声明一个MyClass类型，并初始化
	cout << "Type of variable: " << typeid(variable2).name() << endl;
	// 但是因为auto的原因导致类型是initializer_list<int> 和initializer_list<MyClass>等
	// 给一个建议就是不要在使用auto定义变量的时候使用initializer_list来初始化
	return 0;
}
