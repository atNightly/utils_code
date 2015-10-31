#include <iostream>
#include <vector>
#include <memory>

using namespace std;

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

template<typename T>
class SmartPointer
{
 private:
	T* m_Object{ nullptr };
	ReferenceCount* m_ReferenceCount{ nullptr };
 public:
	SmartPointer()
	{
	}
	//初始化，初始化一个引用计数类，一个目标类
	SmartPointer(T* object)
			:m_Object{ object }
			,m_ReferenceCount{ new ReferenceCount }
	{
			//立刻增加引用计数
			m_ReferenceCount->Increment();
			cout << "Created smart pointer! Reference count is "
				 << m_ReferenceCount->GetCount() << endl;
	}
	
	//析构
	virtual ~SmartPointer()
	{
		//引用计数类是否为nullptr
		if(m_ReferenceCount)
		{
			//减少引用计数
			int decrementedCOunt = m_ReferenceCount->Decrement();
			cout << "Destoryed smart pointer! ReferenceCount count is "
				 << decrementedCOunt << endl;
			//如果减到０就释放对象
			if (decrementedCOunt == 0)
			{
				delete m_ReferenceCount;
				delete m_Object;
			}
			//否则只是设置指针指向nullptr
			m_ReferenceCount = nullptr;
			m_Object = nullptr;
		}
	}
	//智能指针是要支持拷贝的，浅拷贝而已
	SmartPointer(const SmartPointer<T>& other)
			:m_Object{other.m_Object}
			,m_ReferenceCount{other.m_ReferenceCount}
	{
		//把原有的指针减少１
		m_ReferenceCount->Increment();
		cout << "Copied smart pointer! Reference count is "
			 << m_ReferenceCount->GetCount() << endl;
	}
	//赋值操作符,也是浅拷贝
	SmartPointer<T>& operator=(const SmartPointer<T>& other)
	{
		if (this != &other)
		{
			//是否析构
			if (m_ReferenceCount && m_ReferenceCount->Decrement() == 0)
			{
				delete m_ReferenceCount;
				delete m_Object;
			}
			//浅拷贝
			m_Object = other.m_Object;
			m_ReferenceCount = other.m_ReferenceCount;
			m_ReferenceCount->Increment();
		}

		cout << "Assigning smart pointer! Reference count is"
			 << m_ReferenceCount->GetCount() << endl;

		return *this;
	}

	T& operator*()
	{
		return *m_Object;
	}
};

struct MyStruct
{
	public:
		int m_Value{ 0 };
		~MyStruct()
		{
			cout << "Destroying MyStruct object!" << endl;
		}
};

using SmartMyStructPointer = SmartPointer<MyStruct>;

//智能指针做值传递
SmartMyStructPointer PassValue(SmartMyStructPointer smartPointer)
{
	SmartMyStructPointer returnValue;
	returnValue = smartPointer;
	return returnValue;
}


int main(int argc,char* argv[])
{
	SmartMyStructPointer smartPointer{ new MyStruct };
	(*smartPointer).m_Value=10;
	SmartMyStructPointer secondSmartPointer = PassValue(smartPointer);
	return 0;
}

