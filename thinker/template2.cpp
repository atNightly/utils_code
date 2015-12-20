#include <iostream>

/*
 *  模板的默认参数
 *
 *
 */
 

template<class T,size_t N = 100>
class Stack {
    T data[N];
    size_t count;
public:
    void push(const T& t);         
};


template<class T=int>
T sum(T a,T b)
{
    return a + b;    
}
