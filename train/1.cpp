#include <iostream>
using namespace std;

template<typename T>
void test(T a, T b)
{
    cout << "I am template func" << endl;    
}

void test(int a,char c)
{
    cout << "I am normal func" << endl;    
}

void test(char a,char c)
{
    cout << "I am specific func" << endl;    
}

int main()
{
    int a = 2;
    char c = 'a';

    test(a,c); //调用普通函数,类型和模板函数不是严格匹配
    test(a,a); //调用的是模板函数，因为类型完全和模板函数匹配
    test(c,c); //调用的是specific函数，优先选择普通函数
    test(c,a); //调用specific函数
    test<>(c,c); //通过加上<>强制使用模板函数
}
