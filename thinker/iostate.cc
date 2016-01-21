#include <iostream>

using namespace std;

int main()
{
    int a = 1;
    cin >> a;
    cout << "state:"<<cin.fail() << endl;
    cout << a << endl;
}
