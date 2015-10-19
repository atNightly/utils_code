#include <iostream>

using namespace std;

class MyClass
{
private:
	static int s_Counter;
	int* m_Member{&s_Counter};
public:
	MyClass()
	{
		++(*m_Member);
		cout << "Constructing: " << GetValue()<< endl;
	}

	~MyClass()
	{
		if (m_Member) {

			--(*m_Member);
			m_Member = nullptr;
			cout << "Destructing: " << s_Counter << endl;
		
		} else {
			cout << "Destructing a moved-from instance" << endl;
		}
	}

	MyClass(const MyClass& rhs)
			:m_Member{rhs.m_Member}
	{
		++(*m_Member);
		cout << "Copy: " << GetValue() << endl;
	}

	MyClass(MyClass&& rhs)
			:m_Member(rhs.m_Member)
	{
		cout << hex << showbase;
		cout << "Moving: " << &rhs<< " to" << this << endl;
		cout << noshowbase << dec;
		rhs.m_Member = nullptr;
	}

	int GetValue()const
	{
		return *m_Member;
	}
};

int MyClass::s_Counter{0}; //静态变量初始化

MyClass CopyMyClass(MyClass parameter)
{
	return parameter;
}

int main()
{
	auto object1 = MyClass();
	cout << object1.GetValue() << endl;
	{
		auto object2 = MyClass();
		cout << object2.GetValue() << endl;
	}
	auto object3 = MyClass();
	cout << object3.GetValue() << endl;

	auto object4 = CopyMyClass(object3); //发生了两次拷贝动作,如果引入移动语义可以避免临时对象到object4的拷贝
	
	return 0;
}


