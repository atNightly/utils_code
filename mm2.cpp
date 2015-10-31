#include <iostream>
#include <vector>



using namespace std;
///引用计数类

class ReferenceCount
{
	private:
			int m_Count{ 0 };
	public:
			void Increment()
			{
				++m_Count;
			}

			int Decrement()
			{
				return --m_Count;
			}

			int GetCount()const
			{
				return m_Count;
			}
};



int main()
{
	ReferenceCount ref;
	ref.Increment();
	ref.Increment();
	cout << ref.GetCount() << endl;
}
