#include <iostream>

using namespace std;
int main()
{
    try{

        throw 'a';
    }catch(int a) {
        cout << "int" << endl;
    }catch(char c) {
        cout << "char" << endl;
    }
}
