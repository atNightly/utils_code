#include <iostream>
using namespace std;

template<typename T>
class MyVector
{
  public:
    MyVector(const size_t size);
    void push_back(const T data);
    size_t size();
    T& operator[](const size_t size);
    MyVector& operator=(const MyVector &rhs);
    MyVector(const MyVector &data);
    ~MyVector();
  private:
    size_t m_len;
    size_t m_last;
    T *m_data;
};
