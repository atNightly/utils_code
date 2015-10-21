#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int32_t> stlvector = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	cout << "The size is: " << stlvector.size() << endl;
	cout << "The capacity is: " << stlvector.capacity() << endl;

	stlvector.emplace_back(17);
	cout << "The size is: " << stlvector.size() << endl;
	cout << "The capacity is: "<<stlvector.capacity() << endl;

	for(auto &number : stlvector)
	{
		std::cout << number << std::endl;
	}
	return 0;
}
