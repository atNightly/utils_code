/*
 * =====================================================================================
 *
 *       Filename:  get_program_path.c
 *
 *    Description:  获取进程对应的静态镜像文件的绝对路径
 *
 *        Version:  1.0
 *        Created:  2014年09月26日 17时58分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jeff (JF), zyfforlinux@163.com
 *        Company:  Open source
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
char * get_program_path(char *buf,int count);
char * get_program_name(char *buf,int count);

int main()
{
	//程序测试
	char buf[1024];
	bzero(buf,sizeof(buf));
	//打印路径名称
	printf("%s\n",get_program_path(buf,sizeof(buf)));
	bzero(buf,sizeof(buf));
	//打印程序名称
	printf("%s\n",get_program_name(buf,sizeof(buf)));

}

/*
 * 获取程序的路径名称
 */
char * get_program_path(char *buf,int count)
{
	int i=0;
	int retval = readlink("/proc/self/exe",buf,count-1);
	if((retval < 0 || retval >= count - 1))
	{
		return NULL;
	}
	//添加末尾结束符号
	buf[retval] = '\0';
	char *end = strrchr(buf,'/');
	if(NULL == end)
		buf[0] = '\0';
	else
		*end = '\0';
	return buf;
}

/*
 * 获取这个程序的文件名,其实者有点多余,argv[0] 
 * 就代表这个执行的程序文件名
 */
char * get_program_name(char *buf,int count)
{
	int retval = readlink("/proc/self/exe",buf,count-1);
	if((retval < 0 || retval >= count - 1))
	{
		return NULL;
	}
	buf[retval] = '\0';
	//获取指向最后一次出现'/'字符的指针
	return strrchr(buf,'/');
}
