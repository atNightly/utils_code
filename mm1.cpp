#include <iostream>
#include <memory>

using namespace std;

class MyClass
{
		private:
				int m_Number{0};
		public:
				MyClass(int value)
						:m_Number{ value }
				{
					
				}
				~MyClass()
				{
					cout << "Destoring " << m_Number << endl;
				}

				void operator=(const int value)
				{
					m_Number = value;
				}

				int GetNumber()const
				{
					return m_Number;
				}
};

using UniqueMyclass = unique_ptr<MyClass>;

void CreateUniqueObject(UniqueMyclass& referenceToUniquePtr)
{
	UniqueMyclass uniquemyclass{static_cast<UniqueMyclass>(new MyClass(10))};
	cout << hex << showbase;
	cout << "Address in uniqueMyclass" << uniquemyclass.get() << endl;
	referenceToUniquePtr.swap(uniquemyclass);
	cout << "Address in uniqueMyclass" << uniquemyclass.get() << endl;
}

int main(int argc,char* argv[])
{
	cout << "Begin Main" << endl;
	UniqueMyclass  uniqueMyclass{static_cast<UniqueMyclass>(new MyClass(20))};
	CreateUniqueObject(uniqueMyclass);
	cout << "Address in main's UniqueMyclass" << uniqueMyclass.get() << endl;
	cout << dec << noshowbase << "Back in Main" << endl;
	return 0;
}
