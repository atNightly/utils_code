#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    istringstream s("47 1.414 This is a test");
    int i;
    double f;
    s >> i >> f; //空白字符为分隔符输入
    assert(i == 47);
    double relerr = (fabs(f) - 1.414)  / 1.414;
    //double数据进行比较的时候不能使用恒等,应该使用这个epsilon
    //是两个double数的机器最小误差
    assert(relerr <= numeric_limits<double>::epsilon());
    string buf2;
    s >> buf2;
    assert(buf2 == "This");
    cout << s.rdbuf(); 
    cout << endl;
}
