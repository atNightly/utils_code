#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char* argv[])
{
	string myString{"Bruce SUtherland!"};

	auto numberofCapitals = count_if(
					myString.begin(),
					myString.end(),
					[](char &character)
					{
						return static_cast<bool>(isupper(character));
					}
				);
	cout << "The number of capatials: " << numberofCapitals << endl;

}
