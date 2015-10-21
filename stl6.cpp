#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int32_t> stlvector = {1,2,3,4,5};
	auto iterator = stlvector.begin() + 2;
	stlvector.emplace(iterator,6);
	for(auto &number : stlvector)
	{
		std::cout << number << std::endl;
	}
	return 0;
}
