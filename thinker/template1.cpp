#include <cstddef>
#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::size_t;
using std::bitset;

using namespace std;
template<size_t UpperBound> 
class Urand {
  bitset<UpperBound> used;
  public:
    Urand() {srand(time(0));} 
    size_t operator()(); 
};

template<size_t UpperBound>
inline size_t Urand<UpperBound>::operator()() {
    if (used.count() == UpperBound)
        used.reset();
    size_t newval;
    while(used[newval = rand() % UpperBound]);
    
    used[newval] = true;
    return newval;   
}

int main()
{
    Urand<100> rand;
    cout << rand() << endl;    
}
