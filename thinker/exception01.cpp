#include <exception>
#include <iostream>
#include <cstdlib>
using namespace std;

class MyError {
    const char* const data;
public:
    MyError(const char* const msg = 0):data(msg)
    {
        //idle
    }
};

void do_error() {
    throw MyError("something bad happend");
}

void terminator()
{
    cout << "I'll be back" << endl;
    exit(0);
}

int main()
{
    void (*old_terminate)() = set_terminate(terminator);
    do_error();
}
