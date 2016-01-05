#include <iostream>
#include "myvector.hpp"

using namespace std;

int main()
{
    //test construct
    MyVector<char> test1();
    //test construct
    MyVector<int> test2(10);
    test2.push_back(4);
    test2.push_back(5);    
    test2.push_back(6);    
    test2.push_back(7);
    for(int i = 0;i < test2.size();++i)    
    {
        cout << test2[i] << endl;    
    }

    //test copy construct
    MyVector<int> test3(test2);
    for(int i = 0;i < test3.size();++i)    
    {
        cout << test3[i] << endl;    
    }

}
