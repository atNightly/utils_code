#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s = "teststring";
	cout << s.replace(s.begin(),s.begin()+3,"new") << endl;
	cout << s.replace(0,4,"zhang") << endl;
	
}
