#include <iostream>

using namespace std;

class base
{
    public:
        base(int age):m_age(age)
        {
            //
        }
    //private:
        int m_age;
        int getAge()
        {
            return m_age;
        }
};

class Drived : private base
{
    public:
        Drived(int age):base(age)
        {

        }
        int test()
        {
            return getAge();
        }
};

int main()
{
    Drived d(10);
    cout << d.test() << endl;
}
