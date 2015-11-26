#include <iostream>
#include <string>
using namespace std;

int main()
{

    //异常的基本使用，try{...}catch{....}这种形式，通过throw来抛出异常，
    //抛出异常的过程就是创建一个异常类的过程，只不过异常类可以是普通的类，也就是任意类型
    //通过throw来抛出异常，然后在catch语句快中通过形参来接收，为了避免浅拷贝，最好使用const引用的形式
    try{
        
        cout << "start to test exception" << endl;   
        throw string("Hello World");
        cout << "end to test exception" << endl;
    }
    catch(const string& what) {

        cout << what << endl;    
    }
}
