#include <iostream>
#include <vector>
#include <cstring>
#include "memcheck.h"


using namespace std;

class Foo {
    char *s;
    public:
        Foo(const char* s) {
            this->s = new char[strlen(s) + 1];
            strcpy(this->s,s);    
        }
        ~Foo(){
            delete [] s;    
        }
};

int main() {
    MEM_ON();
    cout << "Hello" << endl;
    int *p = new int;
    delete p;
    int *q = new int[3];
    delete []q;
    int *r;
    delete r;
    vector<int> v;
    v.push_back(1);
    Foo s("goodbye");
    MEM_OFF();    
}
