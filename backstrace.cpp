#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

class ExceptionTracer
{
	public:
			ExceptionTracer()
			{
				void* array[200];
			//得到堆栈中frame的地址
				int nSize = backtrace(array,200);
			//backtrace_symbols 用于产生堆栈符号表细心信息,存在array数组中
				char **symbols = backtrace_symbols(array,nSize);
				for(int i = 0;i < nSize; ++i)
				{
						cout << symbols[i] << endl;
				}
				free(symbols);
			}
};
void test()
{
	
	string stack_;
		for(int i=0;i < 100;i++);
 const int len = 200;
  void* buffer[len];
  int nptrs = ::backtrace(buffer, len);
  char** strings = ::backtrace_symbols(buffer, nptrs);
  if (strings)
  {
    for (int i = 0; i < nptrs; ++i)
    {
      // TODO demangle funcion name with abi::__cxa_demangle
      stack_.append(strings[i]);
      stack_.push_back('\n');
    }
    free(strings);
  }
	cout << stack_ << endl;
	
}

void test2()
{
		for(int i=0;i < 100;i++);
		test();
}
int main2()
{
		test2();
}

int main()
{
	main2();
}
