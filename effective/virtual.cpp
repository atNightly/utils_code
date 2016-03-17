#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
    Base()
    {
        string str("derived construct");
        Log(str);
    }

    void Log(string &str)
    {
        log(str);
    }

    virtual void log(string &str)
    {
        cout << "I am base log:" << str << endl;
    }
};


class Derived : public Base
{
public:

    virtual void log(string &str)
    {
        cout << "I am derived log:" << str << endl;
    }
};


int main()
{
    Derived d;
}
