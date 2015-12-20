#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
/*
 * 一些开关标志位
 *  ios::skipws 跳过空格(输入流默认情况)
 *  ios::showbase 打印整型值时指出数字的基数
 *  ios::showpoint 显示浮点值的小数点并截断数字末尾的零
 *  ios::uppercase  显示十六进制数值时使用大写A~F
 *  ios::showpos    显示整数前的加号(+)
 *  ios::unitbuf    单元缓冲区,每次插入后刷新流
 */

using namespace std;

int main()
{
    ofstream out("log.txt");
    //当这个选项没有开启的时候,某些编辑器仅写入一个字母'o'到文件log.txt
    //开启单元缓冲器后则不会丢失任何数据
    out.setf(ios::unitbuf);
    out << "one" << endl;
    out << "two" << endl;
    abort();           
}
