#include <stdio.h>

#define COMPILE_TIME_ASSERT(desc,exp)	\
		extern char desc [(exp) ? 1 : -1]

int main()
{
	COMPILE_TIME_ASSERT(test,1==1);	
}
