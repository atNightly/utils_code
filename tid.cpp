#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <stdio.h>


pid_t gettid()
{
	return static_cast<pid_t>(::syscall(SYS_gettid));
}

int main()
{
		printf("%d\n",gettid());
}

