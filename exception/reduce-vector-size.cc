#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> data(100);
    cout << data.size() << endl;
    cout << data.capacity() << endl;

    data.resize(50);
    cout << data.size() << endl;
    cout << data.capacity() << endl;

    //通过resize虽然调节了data的大小，但是实际上data占用的内存没有变
    //同理利用clear,erase等减少data的大小，但是实际上并没有真正回收内存
    //利用下面的方法可以达到真正回收内存的效果
    vector<int>(data).swap(data);
    cout << data.size() << endl;
    cout << data.capacity() << endl;

    data.push_back(3);
    cout << data.size() << endl;
    cout << data.capacity() << endl;

    data.shrink_to_fit(); //等同于上面的swap
    cout << data.size() << endl;
    cout << data.capacity() << endl;
}
