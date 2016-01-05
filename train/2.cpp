#include <iostream>


using namespace std;

template<typename T>
void test(T a)
{
    cout << "I am template func" << endl;    
}

int main()
{
    int a = 0;
    test(a);
    char c = 'a';
    test(c); 
}
