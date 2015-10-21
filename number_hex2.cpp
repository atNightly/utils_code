#include <iostream>
#include <stdint.h>
#include <bitset>

using namespace std;

int main(int argc,char *argv[])
{
	const uint32_t maskBits{ 16 };
	uint32_t narrowingBits{ 0x1111111 << 2};
	bitset<sizeof(uint32_t) * 8> a(narrowingBits);
	cout << a << endl;
//	cout << showbase << hex << narrowingBits << endl;
	return 0;
}
