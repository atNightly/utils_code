#include <iostream>
#include <vector>

using namespace std;

int main() {

    //vector bool type
    //vector<bool> data(10);
    //bool *p = &data[1];
    //vector<bool> 内部保存的并不是bool类型，而是用bit来表示bool，通过一个代理对象来管理
    //代理对象实现了大多数vector的操作，使用户用起来感觉不到差异，但是唯独取地址操作使无法屏蔽的
    //因为不存在对一个bit取地址
    vector<int> data2(10);
    int *p = &data2[1];
}
