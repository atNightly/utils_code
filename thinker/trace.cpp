#include <iostream>
using namespace std;
#define TRACE(ARG) cout << #ARG << endl; ARG
#define D(a) cout << #a "=[" << a << "]" << endl;

int main()
{
    int a = 10;
    int b = 11;
    TRACE(cout << "test" << endl);       
    D(a + b);   
}
