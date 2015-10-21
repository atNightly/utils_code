#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int32_t> stlvector = {1,2,3,4,5,6,7,8,9,10};
	cout << "The size is: " << stlvector.size() << endl; //输出10
	cout << "The capacity is: " << stlvector.capacity() << endl << endl; 

	for(auto &number : stlvector)
	{
		std::cout << number << endl;
	}

	while(stlvector.size() > 0)
	{
		auto iterator = stlvector.end() -1; //尾迭代器，-1后为最后一个位置
		stlvector.erase(iterator); //删除最后一个元素
	}

	cout << endl << endl << "The size is: " << stlvector.size() << endl;
	cout << "The capacity is: " << stlvector.capacity() << endl << endl;

	for(auto &number : stlvector)
	{
		std::cout << number << ", ";
	}
	std::cout << std::endl;
	return 0;
}
