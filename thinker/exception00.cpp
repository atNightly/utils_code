#include <iostream>
#include <csetjmp>

using namespace std;

class base {
    public:
        base() {
            cout << "base construct func call" << endl;
        }
        ~base() {
            cout << "~base destruct func call" << endl;
        }
};

jmp_buf static_buf;

void test_base() {
    base b;
    for(int i = 0; i < 3;i++)
        cout << "creat some class" << endl;
    longjmp(static_buf,47);//进行了跳转
}

int main() {
    if(setjmp(static_buf) == 0) {
        cout << "deal with some thing" << endl;
        test_base();
    } else {
        cout << "catch a error" << endl;
    }
}
