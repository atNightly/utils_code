#include <iostream>
using namespace std;


class Base{
    public:
        Base(string msg):m_msg(msg)
        {
        }
        virtual void what(){
            cout << m_msg << endl;
        }
    protected:
        string m_msg;
};

class CBase : public Base
{
    public:
        CBase(string msg):Base(msg)
        {

        }
        void what()
        {
           cout << "CBase:" << m_msg << endl;
        }
        void test()
        {
            cout << "I am a CBase" << endl;
        }
};


int main()
{
    try {
        //do some thing
        throw CBase("I am a CBase exception");

    }catch(Base e) {
        e.test();
    }
}
