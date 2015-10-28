#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	using IntVector = vector<int32_t>;
	using IntVectorIterator = IntVector::iterator;
	//常量迭代器 cbegin cend
	using ConstIntVectorIterator = IntVector::const_iterator;
	IntVector myVector{0,1,2,3,4};
	int32_t value{0};
for(IntVectorIterator iter = myVector.begin();iter != myVector.end();++iter)
{
	cout << "The value is: " << *iter << endl;
	*iter = value++;
}

for(ConstIntVectorIterator iter = myVector.cbegin();iter != myVector.cend();++iter)
{
	cout << "The value is: " << *iter << endl;
}
	return 0;
}
