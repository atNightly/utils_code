#include <iostream>

using namespace std;
template<typename T,typename U>
class C {
    public:
        void f() {cout << "Primary Template\n";}
};

template<typename T,typename U>
class C<T,double> {
    public:
        void f() {cout << "doubel\n";}
}
