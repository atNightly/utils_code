#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int32_t> myVector{1,2,3,4,5};
	//遍历算法+然后对每一个元素应用lambda函数
	for_each(myVector.begin(),myVector.end(),[](int32_t value)
	{
		cout << value << endl;
	});
	return 0;
}
