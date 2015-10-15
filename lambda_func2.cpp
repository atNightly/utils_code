#include <iostream>
#include <array>
#include <cstdint>
#include <typeinfo>
#include <algorithm>


int main()
{
	using MyArray = std::array<uint32_t,5>;
	MyArray myArray{1,2,3,4,5};
	auto MyClosure = [](uint32_t number) {
		std::cout << number << std::endl;
	};

	std::cout << typeid(MyClosure).name() << std::endl;
	std::for_each(myArray.begin(),myArray.end(),MyClosure);
	return 0;
}
