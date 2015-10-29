#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char* argv[])
{
	vector<int> myVector{10,6,4,7,9,3};
	sort(myVector.begin(),myVector.end());

	for(auto &element : myVector)
	{
		cout << element << ",";
	}

	cout << endl;
	return 0;
}
