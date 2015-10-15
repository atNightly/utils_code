#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//vector init
	vector<int> vectorA(1); //初始化一个元素,值为0
	vector<int> vectorB(1,10); //初始化1个元素，每个元素的值为10
	
	//{} 会隐式转换为initializer_list<int>
	vector<int> vectorC{1,10}; //初始化2个元素，其值分别是1 10

	//显示initializer_list初始化
	initializer_list<int> initList{1,10};
	vector<int> vectorD(initList);
}
