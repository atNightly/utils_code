#include <iostream>

using namespace std;


class base
{
public:
	virtual void fbase(int data1)final
	{
		cout << "base::fbase(int)" << endl;
	}

};

class fabase:public base
{
public:
	void fbase(int data1)override
	{
		cout << "base:fbase(int,int)" << endl;
	}
};



int main()
{
	
}
