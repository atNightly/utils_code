#include <string>
#include <iostream>

using namespace std;
int main()
{
    string s = "zhangyifei";
    char &rc = s[0];
    string s2(s);
    rc = 'w';
    cout << s2 << endl;
    cout << s << endl;
}
