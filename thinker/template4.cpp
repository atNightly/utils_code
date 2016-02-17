#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Array {
    enum{INIT = 10};
    size_t capacity;
    size_t count;
    T *data;

public:
        Array() {
            count = 0;
            data = new T[capacity = INIT];
        }
        ~Array() {delete [] data;}
        void push_back(const T& t) {
            size_t newCap = 2 * capacity;
            T* newData = new T[newCap];
            for(size_t i = 0; i < count; ++i)
                newData[i] = data[i];

            delete [] data;
            data = newData;
            capacity = newCap;
            data[count++] = t;
        }
};

template<class T,template<class> class Seq>
class Container {
    public:
        void append(const T& t) {seq.push_back(t);}
        T* begin() {return seq.begin();}
        T* end() {return seq.end();}
    private:
        Seq<T> seq;
};

int main()
{
    Container<int,Array> data;
    data.append(3);
}
