#include <iostream>
#include <typeinfo>

using namespace std;

template<class T>
class Outer {
    public:
        template<class R>
        class Inter {
            public:
                void f();
        };
};

template<class T>
template<class R>
void Outer<T>::Inter<R>::f() {
    cout << "Outer == " << typeid(T).name() << endl;
    cout << "Inner == " << typeid(R).name() << endl;
    cout << "Full Inner == " << typeid(*this).name() << endl;
}

int main() {
    Outer<int>::Inter<bool> inner;
    inner.f();
}
