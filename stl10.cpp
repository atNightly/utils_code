#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <cinttypes>

using namespace std;

int main(int argc,char* argv[])
{
	forward_list<int32_t> mylist{1,2,3,4,5};
	mylist.emplace_front(6); //前插
	//mylist.emplace_back(7); //forward_list 没有后插
	auto forwardIter = mylist.begin(); //获取开始迭代器
	++forwardIter;
	++forwardIter;
	mylist.emplace_after(forwardIter,9); //在指定迭代器处插入
	//只有emplace_front 前插和emplace_after在一个元素后面插入
	for(auto &number : mylist)
	{
		cout << number << endl; //
	}

	return 0;

}
