#include <iostream>

using namespace std;

template <typename T,int numberOfElements>
class MyArray
{
	private:
			T m_Array[numberOfElements];
	public:
			MyArray()
					:m_Array{0}
			{
				
			}

			T& operator[](const unsigned int index)
			{
				return m_Array[index];
			}
};

int main(int argc,char* argv[])
{
	const unsigned int ARRAY_SIZE{ 5 };
	MyArray<int,ARRAY_SIZE> myIntArray;
	for(unsigned int i {0}; i < ARRAY_SIZE;++i)
	{
		myIntArray[i] = i;
	}

	for(unsigned int i{0}; i < ARRAY_SIZE;++i)
	{
		cout << myIntArray[i] << endl;
	}

	cout << endl;

	return 0;
}
