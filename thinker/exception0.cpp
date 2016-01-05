#include <iostream>
#include <setjmp.h>

       void longjmp(jmp_buf env, int val);

              void siglongjmp(sigjmp_buf env, int val);


jmp_buf static_buf; //用来存放处理器上下文，用于跳转

void do_jmp()
{
    //do something,simetime occurs a little error
    //调用longjmp后，会载入static_buf的处理器信息，然后第二个参数作为返回点的setjmp这个函数的返回值
    longjmp(static_buf,10);//10是错误码，根据这个错误码来进行相应的处理
}

int main()
{
    int ret = 0;
    //将处理器信息保存到static_buf中,并返回0，相当于在这里做了一个标记，后面可以跳转过来
    if((ret = setjmp(static_buf)) == 0) {
        //要执行的代码
        do_jmp();
    } else {    //出现了错误
        if (ret == 10)
            std::cout << "a little error" << std::endl;
    }
}
