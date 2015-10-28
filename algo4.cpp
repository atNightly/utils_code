#include <cinttypes>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	using IntVector = vector<int32_t>;
	using IntVectorIterator = IntVector::iterator;
	using ReverseIntVectorIterator = IntVector::reverse_iterator;
	using ConstReverseIntVectorIterator = IntVector::const_reverse_iterator;
	IntVector myVector{5,0};
	int32_t value{100};

for(ReverseIntVectorIterator iter = myVector.rbegin();iter != myVector.rend();++iter)
{
	cout << "before The value is: " << *iter << endl;
	*iter = value++;
}

for(ConstReverseIntVectorIterator iter = myVector.crbegin();iter != myVector.crend();++iter)
{
	cout << "after The value is: " << *iter << endl;
}
	return 0;
}
