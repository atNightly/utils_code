#include <iostream>
#include <memory>

using namespace std;

class MyClass
{
 private:
		 int m_value{ 10 };

 public:
		 MyClass()
		 {
			cout << "Constructing！"<< endl;
		 }
		 
		 ~MyClass()
		 {
		 	cout << "Destructing! " << endl;
		 }

		 int GetValue()const
		 {
		 	return m_value;
		 }
};

int main()
{
		{
			unique_ptr<MyClass> uniquePoingter = static_cast<unique_ptr<MyClass>>(new MyClass());
			cout << uniquePoingter->GetValue() << endl;
		}
	while(1);
	return 0;

}
