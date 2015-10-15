#include <iostream>


int main()
{
//统一初始化，避免窄化转换
	int number{0};
	char another{512};
	double bigNumber{1.0};
	float littleNumber{bigNumber};
	return 0;
}
