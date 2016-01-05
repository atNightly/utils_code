#include <iostream>

using namespace std;

template<class T,class U>
class C{
    public:
        void f() {
            cout << "Primary Template\n";
        }
};

template<class U> class C<int,U> {
    public:
        void f() {
            cout << "T == int\n";
        }
};

template<class T> class C<T,double> {
    public:
        void f() {
            cout << "U == double\n";
        }
};

template<class T,class U> class C<T*,U> {
    public:
        void f() {
            cout << "T* used\n";
        }
};

template<class T,class U> class C<T,U*> {
    public:
        void f() {
            cout << "U* used\n";
        }
};

template<class T,class U> class C<T*,U*> {
    public:
        void f() {
            cout << "T* and U* used\n";
        }
};

template<class T> class C<T,T> {
    public:
        void f() {
            cout << "T == U\n";
        }
};

int main() {
    C<float,int>().f();
    C<int,float>().f();
    C<float,double>().f();
    C<float,float>().f();
    C<float*,float>().f();
    C<float,float*>().f();
    C<float*,int*>().f();
//The following are ambiguous
/*
 *  C<int,int>().f() //有两个模板特化
 *  C<double,double>().f() //同样也是的，两个模板特化
 *  C<float*,float*>().f() //三个模板特化
 *  C<int,int*>().f()
 *  C<int*,int*>().f()
 *
 */
}
