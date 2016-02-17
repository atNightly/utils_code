#include <iostream>
#include <vector>

using namespace std;

template<class T,size_t N = 10>
class Array {
    private:
        int size;
        T data[N];
    public:
        Array():size(0) {

        }

        void push_back(T num) {

            data[size++] = num;
        }

        T* begin() {
            return &data[0];
        }

        T* end() {
            return &data[N];
        }
};

template<class T,template<class,size_t N = 11> class Seq>
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
