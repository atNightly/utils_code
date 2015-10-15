#include <iostream>
#include <typeinfo>


using namespace std;

auto AutoFunctionFromReturn(int parameter)->int // 这里需要加
{
	return parameter;
}

int main()
{
	auto value = AutoFunctionFromReturn(1);
	cout << value << endl;
	return 0;
}
