#include <iostream>
#include <vector>

using namespace std;

class base
{
	public:
			base(){cout << "construct" << endl;}
			base(const base &rhs)
			{
				cout << "copy OK" << endl;
			}
			~base(){cout << "destruct"<<endl;}
};

int main()
{
	vector<base> data;
	cout << data.size() << endl; //输出0
	//base zhang;
	//data.push_back(zhang); //导致一次copy初始化
	data.emplace_back(); //添加了一个对象,避免了copy construct
	cout << data.size() << endl; //输出1 
}
