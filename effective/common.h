#ifndef _LIB_H_
#define _LIB_H_

#include <iostream>

using namespace std;
class test2;
test2& gettest();
class test2
{
    public:
        test2():value(100)
        {
            //value = 100;
            cout << "test2 construct" << endl;
        }

        void said()
        {
            cout << "I am test2 " << "value" << value << endl;
        }
    int value;
};


class test1
{
    public:
        test1()
        {
            cout << "test1 construct" << endl;
            gettest().said();
        }
};

#endif
