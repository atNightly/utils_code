#include <iostream>
#include <exception>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <sstream>
#include <iomanip>

using namespace std;


/*
 *  流发生错误,需要手动查看其状态才能知道,这是早起c++不支持异常导致的,
 *  为了兼容,一致沿用,为了统一使用异常来处理错误,可以使用流的exception函数来设置当发生了指定流状态的时候,触发异常
 *
 */

int main()
{
    
    float a;
    cin.exceptions(ios::failbit);
    try {
        cin >> a; //接收了一个字符,触发了fail
    } catch(const std::ios_base::failure& fail) {
        cout <<"Get a error" << endl;    
        cout << fail.what() << endl;
    }
}
