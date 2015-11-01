#include <iostream>
#include <stack>
#include <thread>
#include <vector>

using namespace std;


class MyManagedObject;

class MyManagedObject
{
 private:
	static const unsigned int MAX_OBJECTS{ 8 };
	using MyManagedObjectCollection = vector<MyManagedObject>;
	static MyManagedObjectCollection s_ManagedObjects;
	static stack<unsigned int> s_FreeList;
	unsigned int m_Value{ 0xFFFFFFFF };
 public:
	MyManagedObject() = default;
	MyManagedObject(unsigned int value)
		:m_Value{ value }
	{
		
	}
	void* operator new(size_t numBytes)
	{
		void* objectMemory{};
		 
		if (s_ManagedObjects.capacity() < MAX_OBJECTS)
		{
			s_ManagedObjects.reserve(MAX_OBJECTS);
		}
 
		if (numBytes == sizeof(MyManagedObject) &&
		s_ManagedObjects.size() < s_ManagedObjects.capacity())
		{
			unsigned int index{ 0xFFFFFFFF };
			if (s_FreeList.size() > 0)
			{
				index = s_FreeList.top();
				s_FreeList.pop();
			}
	 
			if (index == 0xFFFFFFFF)
			{
				s_ManagedObjects.push_back({});
				index = s_ManagedObjects.size() - 1;
			}
 
			objectMemory = s_ManagedObjects.data() + index;
		}
		else
			{
			objectMemory = malloc(numBytes);
			}
			 
		return objectMemory;
	}
 
	void operator delete(void* pMem)
	{
		const intptr_t index{
		(static_cast<MyManagedObject*>(pMem)-s_ManagedObjects.data()) /
		static_cast< intptr_t >(sizeof(MyManagedObject)) 
		};
		if (0 <= index && index < static_cast< intptr_t >(s_ManagedObjects.size()))
		{
			s_FreeList.emplace(static_cast<unsigned int>(index));
		} else {
			free(pMem);
		}
	}
};

int main(int argc,char* argv[]) 
{
	cout << hex << showbase;
	 
	MyManagedObject* pObject1{ new MyManagedObject(1) };
	 
	cout << "pObject1: " << pObject1 << endl;
	 
	MyManagedObject* pObject2{ new MyManagedObject(2) };
	 
	cout << "pObject2: " << pObject2 << endl;
	 
	delete pObject1;
	pObject1 = nullptr;
	 
	MyManagedObject* pObject3{ new MyManagedObject(3) };
	 
	cout << "pObject3: " << pObject3 << endl;
	 
	pObject1 = new MyManagedObject(4);
	 
	cout << "pObject1: " << pObject1 << endl;
	 
	delete pObject2;
	pObject2 = nullptr;
	 
	delete pObject3;
	pObject3 = nullptr;
	 
	delete pObject1;
	pObject1 = nullptr;
	 
	return 0;
}
