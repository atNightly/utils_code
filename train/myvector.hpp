#include <iostream>
#include <exception>
#include <stdexcept>
#include "myvector.h"
using namespace std;
template<typename T>
MyVector<T>::MyVector(const size_t size = 0)
{
    m_len = size;
    m_last  = 0;
    if(m_len)
        m_data = new T[m_len - 1];
}

template<typename T>
void MyVector<T>::push_back(const T data)
{
    m_data[m_last++] = data;
}

template<typename T>
size_t MyVector<T>::size()
{
    return m_last;    
}

template<typename T>
T& MyVector<T>::operator[](const size_t size)
{
    if (size > (m_len-1) || size < 0)
        throw std::out_of_range("Out of range");
    if (size > m_last)
        m_last = size;
    return m_data[size];
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector &rhs)
{
    if (this == &rhs)return *this; //证同性测试
    //先保存原有指针
    T *pOrig = m_data;
    //如果这里出现异常,m_data还是指向原来的存储空间
    m_data = new T[rhs.m_len-1];
    for(size_t i = 0; i < rhs.m_len;++i)
    {
        m_data[i] = rhs.m_data[i];     
    }
    m_last = rhs.m_last;
    delete[] pOrig;
    return *this;
}

template<typename T>
MyVector<T>::MyVector(const MyVector &data)
{
    m_len = data.m_len;
    m_last = data.m_last;
    if (m_len) {
        m_data = new T[data.m_len - 1];
        for(size_t i = 0; i < data.m_len;++i)
        {
            m_data[i] = data.m_data[i];     
        }
    } else {
        m_data = nullptr;
    }
}

template<typename T>
MyVector<T>::~MyVector()
{
    if(m_len) {
        delete[] m_data; 
    }
}
