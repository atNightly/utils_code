#include <iostream>
#include <string>
using namespace std;

class base
{
    public:
        base(const char* str):m_string(str)
        {}
        void what()
        {
            cout << m_string << endl;
        }
    private:
        string m_string;
};

class drive : public base
{
    public:
        drive(const char* str):base(str)
        {
            
        }
    private:
        string m_second;
};

int main()
{
        try{
            //do some thing
            //throw base("I am a base class");
            throw drive("I am a drive class");
            

        } catch(drive& test){
            
            cout << "I receive a drive class" << endl;

        } catch(base& test) {
            cout << "I receive a base class" << endl;    
        }
}
