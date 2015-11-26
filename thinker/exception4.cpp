#include <iostream>
#include <string>
using namespace std;

class dog
{
    public:
        dog()
        {
            cout <<"I am a dog construct" << endl;    
        }
        ~dog()
        {
            cout << "I am a dog destruct " << endl;    
        }
    private:    
};


class cat
{
    public:
        cat()
        {
            cout << "I am a cat construct" << endl;   
            throw string("I am a pig") ;
        }
        ~cat()
        {
            cout << "I am a cat destruct" << endl;    
        } 
};

int main()
{
 //   dog *p_dog;
 //   cat *p_cat;
 //构造函数中如果抛出异常，则析构函数无法被调用
 //解决办法:
 //1.在构造函数中捕获异常
 //2.对象在析构的时候释放其资源，自我管理(可以通过share_ptr来管理这类对象)
    try{
        dog p_dog[5];
        cat p_cat;
    } catch(...) {
        cout << "catch some exception" << endl;    
    }
    
}
