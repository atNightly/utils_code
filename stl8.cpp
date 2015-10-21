#include <iostream>
#include <vector>
#include <cinttypes>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int32_t> stlvector = {1,2,3,4,5,6,7,8,9,10};
	while(stlvector.size() > 0)
	{
		auto iterator = stlvector.end() - 1;
		stlvector.erase(iterator);

		if ((stlvector.size() * 2) == stlvector.capacity())
		{
			stlvector.shrink_to_fit(); //减少capacity的大小
		}
		cout << "The size is: " << stlvector.size() << endl;
		cout << "The capacity is: " << stlvector.capacity() << endl;
	}
	return 0;
	
}
