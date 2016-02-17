#include <iostream>

template<typename T>
void f(T*) {
    //NULL
}

void h(void (*pf)(int*)) {
    //NULL
}

template<typename T>
void g(void (*pf)(T*)) {
    //NULL
}

int main() {
    h(&f<int>);
    h(&f);
    g<int>(&f<int>);
    g(&f<int>);
    g<int>(&f);
}

