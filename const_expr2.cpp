#include <array>
#include <cstdint>
#include <iostream>

// 一个constexpr函数
constexpr uint32_t ArraySizeFunction(int parameter)
{
	//parameter = parameter +2 ;   不能运算，要保证parameter是常量
	return parameter;
}

int main()
{
	int c= 0;
	constexpr uint32_t ARRAY_SIZE{ArraySizeFunction(5)}; //参数必须是常量,否则编译出错
	std::array<uint32_t,ARRAY_SIZE> myArray{1,2,3,4,5};

	for(auto &number: myArray)
	{
		std::cout << number << std::endl;
	}
	return 0;
}
