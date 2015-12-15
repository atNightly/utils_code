#include <iostream>
#include <ostream>
#include <istream>
#include <sstream>
#include <iomanip>


using namespace std;

int main()
{
    int i;
    cin >> i;
    
    float f;
    cin >> f;

    char c;
    cin >> c;

    char buf[100];
    cin >> buf;

    cout << "i = " << i << endl;
    cout << "f = " << f << endl;
    cout << "c= " << c << endl;
    cout << "buf = " << buf << endl;

    cout << flush;
    cout << hex << "0x" << i << endl;
}


