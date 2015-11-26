#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

class MyError:public runtime_error {
public:
    MyError(const string& msg = "") : runtime_error(msg) {}    
    
};

//runtime_error logic_error 两个都是继承自标准异常，带有string构造函数
//
int main()
{
    try {
        throw MyError("my message");   
    }   catch(MyError& x) {
        cout << x.what() << endl;    
    }
}
