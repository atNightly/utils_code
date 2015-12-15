#include <cassert>
#include <sstream>
#include <string>

using namespace std;

/*
 *  seekp写指针 seekg读指针
 *
 */
int main()
{
    string text = "We will hook no fish";
    stringstream ss(text); //初始化
    ss.seekp(0,ios::end); //定位到结束
    ss << " before its time."; //输出这些字符到ss
    assert(ss.str() == "We will hook no fish before its time.");
    ss.seekg(8,ios::beg); //定位到
    string word;
    ss >> word;
    assert(word == "hook");
    ss.seekp(8,ios::beg);
    ss << "ship";
    ss.seekg(16,ios::beg);
    ss << "code";
    
    ss.str("A horse of a different color.");
    assert(ss.str() == "A horse of a different color.");
}
