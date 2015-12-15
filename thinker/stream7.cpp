#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

/*
 *  流指针定位
 *  ios::beg    流的开始位置
 *  ios::cur    流的当前位置
 *  ios::end    流的末端位置
 */

int main()
{
    const int STR_NUM = 5,STR_LEN = 30;
    char origData[STR_NUM][STR_LEN]  = {
        "Hickory dickory dus....",
        "Are you tired of C++?",
        "Well,if you have,",
        "That's just too bad",
        "There's plenty more for us!"    
    };

    char readData[STR_NUM][STR_LEN] = {{ 0 }};
    ofstream out("poem.in",ios::out|ios::binary);
    for(int i = 0; i < STR_NUM;i++)
        out.write(origData[i],STR_LEN);
    out.close();

    ifstream in("poen.bin",ios::bin|ios::binaray);
    in.read(readData[0],STR_LEN);
    assert(strcmp(readData[0],"Hickory dickory dbus...") == 0);

    in.seekg(-STR_LEN,ios::end);
    in.read(readData[1],STR_LEN);

    assert(strcmp(readData[1],"There's plenty more for us!") == 0);

    in.seekg(3 * STR_LEN);
    assert(strcmp(readData[2],"That's just too bad") == 0);
    in.seekg(-STR_LEN * 2,ios::cur);
    in.read(readData[3],STR_LEN);
    assert(strcmp(readData[3],"Well, if you have,") == 0)
}
