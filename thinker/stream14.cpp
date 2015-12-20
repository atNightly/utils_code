#include <iostream>

using namespace std;

/*
 *  操纵算子,不需要使用setf来设置对应的位是否开启
 *  直接插入到流中
 *
 *
 */

int main()
{
    cout << flush; //==>cout.flush();
    int i = 16;
    cout << hex << "0x" << i << endl;
    
    cin >> ws; //吃掉空格
    cin >> i;
    cout << "0x" << i << endl;
}
