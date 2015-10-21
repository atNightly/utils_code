#include <iostream>
#include <stdint.h>
using namespace std;

int main(int argc,char* argv[])
{
	uint32_t hexvalue{ 0x89 };
	cout << showbase <<"Decimal: " << hexvalue << endl; //打印十进制
	cout << hex << "Hexadecimal: " << hexvalue << endl; //打印16进制
	cout << showbase << oct << "Oct: " << hexvalue << endl; //打印16进制
	cout << showbase << hex << "Hexadecimal (with base):" << hexvalue << endl; //打印十六进制并且附带0x开头
}
