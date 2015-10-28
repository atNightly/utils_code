#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int> myVector{4,0,6,9,1};
	//求最小值
	auto minimum = min_element(myVector.begin(),myVector.end());
	cout << "Minimum value: " << *minimum << std::endl;
	return 0;
}
