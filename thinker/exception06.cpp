#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


class Base
{
    public:
        Base(int data,string str)try:m_int(data),m_string(str)
       {
            // some initialize opt
       }catch(const char* msg) {
            cout << "catch a exception" << msg << endl;
       }

    private:
        int m_int;
        string m_string;
};

int main()
{
    Base base(1,"zhangyifei");
}
