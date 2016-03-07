#include <iostream>


template<typename T,typename X>
auto min(const T& a,const X& b) ->decltype((a < b)? a:b)
{
    return (a < b) ? a:b;
}
