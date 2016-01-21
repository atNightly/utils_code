#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    cout << "type an in ,a float and a string: ";
    int i;
    float f;
    cin >> i >> f;
    string stuff;
    getline(cin,stuff);
    ostringstream os;
    os << "integer = " << i << endl;
    os << "float = " << f << endl;
    os << "string = " << stuff << endl;
    string result = os.str();
    cout << result << endl;
}
