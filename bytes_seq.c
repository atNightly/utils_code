/*
 *	 字节序判断
 *	
 */
#include <stdio.h>

void byteorder();

void byteorder()
{
	union
	{
		short value;
		char union_bytes[sizeof(short)];
	}test;
	test.value = 0x102;
	if(( test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
	{
		printf("big endian\n");
	}
	else if((test.union_bytes[0] == 2) &&(test.union_bytes[1] == 1))
	{
		printf("little endian\n");
	}
	else
	{
		printf("unknown...\n");
	}
}
	
int main()
{
	byteorder();
}
