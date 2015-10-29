#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool IsGreater(int left,int right)
{
	return left > right;
}

int main(int argc,char* argv[])
{
	vector<int> myVector{10,6,4,7,9,3};
	sort(myVector.begin(),myVector.end(),IsGreater);
//	sort(myVector.begin(),myVector.end(),[](int &left,int &right){
//					return left > right;
//					});

	for(auto &element : myVector)
	{
		cout << element << ",";
	}

	cout << endl;
	return 0;
}
