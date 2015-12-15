#include <iomanip>
#include <iostream>

using namespace std;

/*
    badbit -发生了致命的错误 流将不能继续使用
    eofbit -流结束
    failbit-非法数据,流可以继续使用
    goodbit-一切正常,没有错误发生,也没有输入结束
    
    eofbit被置位的时候,failbit也会被置位

    系统提供了一系列的获取状态的函数
    good()
    fail()
    bad()
    eof()
 */

int main()
{
    cout << cin.good() << endl;
    cin.setstate(ios::eofbit); //设置流状态
    cout << cin.good() << endl;
    
    cin.clear();               //清除流状态
    cout << cin.good() << endl;

    cout << cin.fail() << endl;
    cin.setstate(ios::failbit);
    cout << cin.fail() << endl;
    cin.clear();
    cin.setstate(ios::badbit); //badbit也会导致fail返回true
    cout << cin.fail() << endl;
    
    cin.clear();
    cin.setstate(ios::failbit);
    cout << cin.bad() << endl; 
    //failbit不是bad,所以bad()返回false,只有出现badbit bad()才会返回false
}
