#include <iostream>
#include <typeinfo>
#include <execinfo.h>
#include <stdlib.h>
#include <exception>
#include <cxxabi.h>
#include <string>

using namespace std;
void test(int data)
{
	cout << "test" << endl;
}

/*
           ./prog(myfunc3+0x5c) [0x80487f0]
           ./prog [0x8048871]
           ./prog(myfunc+0x21) [0x8048894]
           ./prog(myfunc+0x1a) [0x804888d]
           ./prog(myfunc+0x1a) [0x804888d]
           ./prog(main+0x65) [0x80488fb]
           /lib/libc.so.6(__libc_start_main+0xdc) [0xb7e38f9c]
           ./prog [0x8048711]

		   输出格式如上，这是C的堆栈结果，如果
*/
//对于没一行，过滤出函数名称,
string demmangle(const char *str)
{
	
}

int main()
{
char *p;	
//abi::__cxa_demangle
//第一个参数是mangled_name 要demangle的name
//第二个参数是输出的demangle的name要存在哪
//第三个参数是输出的demangle的长度
//第四个参数是demaneg的状态是成功还是失败
		//0 demangle success
		//-1 memory allocation failure
		//-2 mangled_name is not a valid name
		//-3 one of the argument is invalid
cout <<abi::__cxa_demangle(typeid(p).name(),nullptr,nullptr,nullptr) << endl;
}
