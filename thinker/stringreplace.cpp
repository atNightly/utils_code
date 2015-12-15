#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string s("A piece of text");
    string tag("$tag$");
    //字符串的插入
    s.insert(8,tag + ' ');
    cout << s << endl;
    assert(s == "A piece $tag$ of text");
    //字符串的查找，查找不成功返回string:nops
    int start = s.find(tag);
    assert(start == 8);
    assert(tag.size() == 5);
    //字符串的替换
    s.replace(start,tag.size(),"Hello there");
    assert(s == "A piece Hello there of text");
    
    //STL算法,替换全部
    replace(s.begin(),s.end(),'x','X');
    cout << s << endl;
}
