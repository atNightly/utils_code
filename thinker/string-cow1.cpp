#include <iostream>
#include <string>
#include <cstdio>
using namespace std;


int main()
{
    string s1 = "test";
    string s2 = s1;

    printf("s1:%p\n",s1.c_str());
    printf("s2:%p\n",s2.c_str());

}
