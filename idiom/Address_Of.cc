#include <iostream>

using namespace std;

/*
 *  取地址操作,我们都知道&操作符可以取地址,但是如果一个类重载了&操作符的话,该怎么办.
 *  对于这种情况就可以使用下面定义的取地址函数,boost库中也有类似实现
 *
 *  Boost addressof utility 一个取地址的函数
 *
 */

class nonaddressable
{
public:
    typedef double useless_type;

private:
    useless_type operator& ()const
    {
        cout << "test";
    }
};

template <typename T>
T* addressof(T &v)
{
    return reinterpret_cast<T *>(& const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
}

int main(void)
{
    nonaddressable na;
 //   nonaddressable *naptr = &na; //error
    nonaddressable *naptr = addressof(na);

    return 0;
}
