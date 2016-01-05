#include <iostream>
#include <string>

using namespace std;

int main()
{
    try{
        //do something
        throw string("this is exception");
    } catch(const string& e) {
        cout << "catch a exception " << e << endl;
    }
}
