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
using MyWeakPtr = weak_ptr<MyClass>;

MySharedPtr PassSharedPtr(MySharedPtr ptr)
{
	cout << "In Function Name: " << ptr->GetName() << endl;
	return ptr;
}

int main()
{

	MyWeakPtr weakPtr;
  { 
	auto sharePointer = make_shared<MyClass>("MyClass",10); //引用计数为1
	weakPtr = sharePointer; 
	{
		auto newSharedPointer = PassSharedPtr(sharePointer); //引用计数为2
		if (sharePointer) {
			cout << "First Object Name: " << sharePointer->GetName() << endl;
		}
		cout << "Second Object Name: " << newSharedPointer->GetName() << endl;
		auto sharedFromWeak1 = weakPtr.lock(); //提升，引用计数为3
		if (sharedFromWeak1) {
			cout << "Name From Weak1: " << sharedFromWeak1->GetName() << endl;
		}
	} //减少newSharedPointer 和sharedFromWeak1 
  } //减少sharePointer

  auto sharedFromWeak2 = weakPtr.lock(); //提升无效
  if (!sharedFromWeak2) {

  	cout << "Shared Pointer Out Of Scope!" << endl;
  
  }
	return 0;
}
