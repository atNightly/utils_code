#include <iostream>


class MyClass
{
  private:
	int m_Member;
  public:
	MyClass() = default;
	MyClass(const MyClass& rhs) = default;
};


int main()
{
//uniforma Initialization
	MyClass objectA{};
	MyClass objectB{MyClass{}};
	return 0;
}
