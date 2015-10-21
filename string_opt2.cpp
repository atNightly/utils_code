#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

int main()
{
	ifstream csvfile{"string.csv"};
	assert(csvfile);
	if (csvfile) {
		while(!csvfile.eof()) {
			string line;
			getline(csvfile,line);
	
			cout << "line:" << line << endl;

			if (line.size() > 0)
			{
				stringstream lineStream{ line };
				string stringIdText;
				getline(lineStream,stringIdText,',');
				cout << stringIdText << endl;
				stringstream idStream{ stringIdText };
		
				getline(lineStream,stringIdText,','); //getline 第三个参数 实现分割
				cout << stringIdText << endl;
			}
		}
	}
	
}
