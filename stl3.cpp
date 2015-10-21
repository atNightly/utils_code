#include <iostream>
#include <cinttypes>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int32_t> strvector{10,65,3000,2,49};
	cout << "The size is: " << strvector.size() << endl;
	strvector.emplace_back(50);
	
	cout << "The size is: " << strvector.size() << endl;
	
	for(auto &number : strvector)
	{
		std::cout << number << endl;
	}
	return 0;
}
