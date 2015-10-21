#include<array>
#include <cinttypes>
#include <iostream>


int main(int argc,char* argv[])
{
	const uint32_t numberOfElements{5};
	std::array<int32_t,numberOfElements> stlarray{10,65,3000,249,11};
	for(uint32_t i = 0;i < numberOfElements;++i)
		std::cout<< stlarray[i] << std::endl;
	
	for(auto&& number:stlarray)
		std::cout<< number << std::endl;
}
