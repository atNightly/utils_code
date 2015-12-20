#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;


int main()
{
    //从某个位置开始查找指定的字符或者字符数组
    string s = "wo ai ni zhang yi fei ";
    assert(s.find("zhang",0) == 9);

    //返回第一个与"wiads"中任何字符匹配的位置
    cout << s.find_first_of("wiads",0) << endl;
    //返回最后一个与"wiads"中任何字符匹配的位置
    cout << s.find_last_of("wiads",0) << endl;
    /*
        find_first_not_of();//语义和find_first_of相反
        find_last_not_of();
        rfind();
    */
    s.erase(0,2);
    cout << s << endl;
}
