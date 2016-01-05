#ifndef _COMPLEX_H_
#define _COMPLEX_H

#include <iostream>
#include <ostream>
using namespace std;
template<typename T>
class Complex
{
   public:
        Complex(T a,T b);   
        friend ostream& operator<< <T>(ostream& c,Complex<T> &a);
   private:
        Complex operator+(Complex& c);
    T a;
    T b;   
};

#endif //end of _COMPLEX_H_
