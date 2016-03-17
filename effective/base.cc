#include <iostream>
#include <string>


using namespace std;

class Base {

 private:
    int x;
 public:
    virtual void mf1() = 0;
    virtual void mf1(int) {cout << "Base::mf1(int)" << endl;}
    virtual void mf2() {cout << "Base::mf2()" << endl;}
    void mf3() {cout << "Base::mf3()" << endl;}
    void mf3(double) {cout << "Base::mf3(double)" << endl;}
};

class Derived:public Base {
 public:
     virtual void mf1() {cout << "Derived::mf1()" << endl;}
     void mf3() {cout << "Derived::mf3()" << endl;}
     void mf4() { cout << "Derived::mf4()" << endl;}
};


int main()
{
    Derived d;
    int x;
    d.mf1();
    //d.mf1(x);
    d.mf2();
    d.mf3();
    //d.mf3(x);
}
