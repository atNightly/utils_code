#include <iostream>

using namespace std;
int main() try{
        
        //do some thing
        cout << "start to do some thing" << endl;
        throw int(4);
        cout << "compltet throw error" << endl;
}
catch (...)
{
    cout << "occus some error" << endl;    
    throw;
}
