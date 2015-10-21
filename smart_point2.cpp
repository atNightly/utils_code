#include <iostream>
#include <memory>

using namespace std;

class MyClass
{
private:
		string m_name;
		int m_value;
public:
		MyClass(const string& name,int value)
				:m_name { name },m_value{ value }
		{
			cout << "Constructing！" << endl;
		}

		~MyClass()
		{
			cout << "Destructing!" << endl;
		}

		const string& GetName()const
		{
			return m_name;
		}

		int GetValue()const
		{
			return m_value;
		}
};

using MyUniquePtr = unique_ptr<MyClass>;

MyUniquePtr PassUniquePtr(MyUniquePtr ptr)
{
	cout << "In Function Name: " << ptr->GetName() << endl;
	return ptr;
}

int main()
{
 {
	auto uniquePointer = static_cast<MyUniquePtr>(new MyClass{"myclass",10});
	auto newUniquePOinter = PassUniquePtr(move(uniquePointer)); //通过移动语义来传递unique_ptr

	if (uniquePointer)
	{
		cout << "First Object Name: " << uniquePointer->GetName() << endl;
	}
	
	cout << "Second Object Name: " << newUniquePOinter->GetName() << endl;
 }
	while(1);
	return 0;
}
