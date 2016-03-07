#include <iostream>

using namespace std;
template<typename T>
void f(T) {
    cout << "T" << endl;
}

template<typename T>
void f(T*) {
    cout << "T*" << endl;
}

template<typename T>
void f(const T*) {
    cout << "const T*" << endl;
}

int main() {
    f(0);
    int i = 0;
    f(&i);
    const int j = 0;
    f(&j);
}
