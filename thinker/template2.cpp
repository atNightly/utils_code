#include <iostream>
using namespace std;

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

template<class T,size_t N = 100>
void Stack<T, N>::push(const T& t) {
    cout << sizeof(data) << endl;
}

template<class T=int>
T sum(T a,T b)
{
    return a + b;
}

int main()
{
    Stack<int> st;//整型的，大小为100的栈
    st.push(1);
    cout << sum(8.0,9.0) << endl;
}
