#include <iostream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <fstream>
using namespace std;
/*
 *  ios::in     打开输入文件,是的现存的文件不会被截断
 *  ios::out    打开输出文件,意味值是ios::trunc模式
 *  ios::app    打开文件,进行追加
 *  ios::ate    打开文件,指向文件末尾
 *  ios::trunc  打开文件,文件存在就截断旧文件
 *  ios::binary 按照二进制方式打开文件,默认打开为文本方式
 *
 */

int main()
{
    {
        ifstream in("1.txt");
        cout << in.rdbuf();
        cout << "+++++++++++++++++++++++++++++++++" << endl;
    }

    ifstream in("1.txt");
    streambuf& sb = *cout.rdbuf(); //指向了cout的streambuf
    while(!in.get(sb).eof()) { //从in读取内容到sb指向的streambuf中
        if (in.fail())  //如果出现流失败,说明碰到了\n
            in.clear(); //清除错误状态,
        cout << char(in.get());  //得到\n
    }
}
