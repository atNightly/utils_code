#include <iostream>
#include <ostream>
#include "complex.h"
using namespace std;

template<typename T>
Complex::Complex(T a,T b)
{
    a = a;
    b = b;    
}

template<typename T>
Complex<T> Complex<T>::operator+(Complex<T> &c)
{
    a =  c.a;
    b = c.b;    
    return Complex<T>(a,b);
}

template<typename T>
ostream& operator<<(ostream& c,Complex<T> &a)
{
    c <<  a.a << a.b << "i" << endl;
}

