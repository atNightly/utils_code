#include <exception>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Up{};
class Fit{};
void g();

void f(int i)throw(Up,Fit/*,bad_exception*/) {
    switch(i) {
        case 1: throw Up();
        case 2: throw Fit();    
    }   
    g();
}

void g() {throw 47;}

void my_ternminate() {
    cout << "I am a ternminate" << endl;
    exit(0);    
}

void my_unexpected() {
    cout << "unexpected exception thrown" << endl;
 //   throw Up();
    throw 8;
    //如果在unexpected中继续抛出异常，抛出的是规格说明中的　则会被捕捉程序继续执行
    //如果抛出的异常不在异常规格说明中分两种情况
    //1.异常规格说明中有bad_exception ，那么会导致抛出一个bad_exception
    //2.异常规格说明中没有bad_exception 那么会导致程序调用ternminate函数
   // exit(0);    
}

int main() {
 set_terminate(my_ternminate);
 set_unexpected(my_unexpected);
 for(int i = 1;i <=3;i++)
 {
     //当抛出的异常,并不是异常规格说明中的异常时
     //会导致最终调用系统的unexpected函数，通过set_unexpected可以
     //用来设置自己的unexpected汗函数
    try {
        f(i);    
    }catch(Up) {
        cout << "Up caught" << endl;    
    }catch(Fit) {
        cout << "Fit caught" << endl;    
    }catch(bad_exception) {
        cout << "bad exception" << endl;    
    }
 }
}
