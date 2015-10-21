#include <iostream>
#include <vector>
#include <list>
#include <cinttypes>

using namespace std;

int main(int argc,char* argv[])
{
	list<int32_t> mylist{1,2,3,4,5};
	mylist.emplace_front(6); //前插
	mylist.emplace_back(7); // 后插
	auto forwardIter = mylist.begin(); //获取开始迭代器
	++forwardIter;
	++forwardIter;
	mylist.emplace(forwardIter,9); //在指定迭代器处插入


	auto reverseIter = mylist.end(); //获取尾迭代器
	++reverseIter;
	++reverseIter;
	++reverseIter;

	mylist.emplace(reverseIter,8); //在指定迭代器插入
	for(auto &number : mylist)
	{
		cout << number << endl; //
	}

	return 0;

}
