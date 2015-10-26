#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class ExceptionTracer
{
	public:
			ExceptionTracer()
			{
				void* array[25];
				int nSize = backtrace(array,25);
				char **symbols = backtrace_symbols(array,nSize);
				for(int i = 0;i < nSize; ++i)
				{
						cout << symbols[i] << endl;
				}
				free(symbols);
			}
};

int main()
{
	ExceptionTracer test;
}

