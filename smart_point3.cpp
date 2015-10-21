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

using MySharedPtr = shared_ptr<MyClass>;

MySharedPtr PassSharedPtr(MySharedPtr ptr)
{
	cout << "In Function Name: " << ptr->GetName() << endl;
	return ptr;
}

int main()
{
 
	auto sharePointer = make_shared<MyClass>("MyClass",10);
	{
		auto newSharedPointer = PassSharedPtr(sharePointer);
		if (sharePointer) {
			cout << "First Object Name: " << sharePointer->GetName() << endl;
		}
		cout << "Second Object Name: " << newSharedPointer->GetName() << endl;
	}
	while(1);
	return 0;
}
