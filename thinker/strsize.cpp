#include <string>
#include <iostream>
using namespace std;

int main() {
    string bigNews("I saw Elvis in a UFO. ");
    cout << bigNews << endl;
    
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity()<<endl;
    
    bigNews.insert(1," thought I");
    cout << bigNews << endl;
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity() << endl;
    bigNews.reserve(500);
    bigNews.append("I've been working too hard");
    
    cout << bigNews << endl;
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity() << endl;
}
