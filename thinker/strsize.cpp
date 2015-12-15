#include <string>
#include <iostream>
using namespace std;

int main() {
    string bigNews("I saw Elvis in a UFO. ");
    cout << bigNews << endl;
    
    //size = 当前元素的大小 
    cout << "Size = " << bigNews.size() << endl;
    //capacity = 当前string可容纳的最大元素大小
    cout << "Capacity = " << bigNews.capacity()<<endl;
    
    bigNews.insert(1," thought I");
    cout << bigNews << endl;
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity() << endl;
    //将当前string的大小扩充到指定大小
    bigNews.reserve(500);
    bigNews.append("I've been working too hard");
    
    cout << bigNews << endl;
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity() << endl;
    //调整string为指定大小，截断的部分，默认填充０,第二个参数是用来指定用什么字符进行填充   
    bigNews.resize(10,'#');
    cout << bigNews << endl;
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity() << endl;
    
    bigNews.resize(50,'#');
    cout << bigNews << endl;
    cout << "Size = " << bigNews.size() << endl;
    cout << "Capacity = " << bigNews.capacity() << endl;
}

