#include <iostream>
#include <exception>
#include <string>

using namespace std;

//默认异常没有被捕捉会调用terminate函数，这个函数中使用了abort终止了程序
void new_terminate()
{
    cout << "I will terminate the programing" << endl;    
    exit(0);
}

int main()
{
    void (*p)() = set_terminate(new_terminate);//设置自定义terminate函数
    try{
        
        cout << "start to throw some exception" << endl;
        throw int(100);

    }catch(string& what){
        
        cout << what << endl;
    }
}
