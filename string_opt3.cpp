#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <boost/format.hpp>

using namespace std;

int main()
{
	
	std::string formattedName{"my name is %s %s"};
	std::string firstName {"zhangyifei"};
	std::string surname {"zhangyifei"};
	formattedName = str(boost::format(formattedName) % firstName % surname);
	cout << formattedName << endl;	
}
