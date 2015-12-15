#include <fstream>
#include <iostream>
#include <ostream>

using namespace std;


int main()
{
    ifstream in("1.txt");
    ofstream out("1.out");
    
    out << in.rdbuf(); //copy file
    in.close();
    out.close();

    ifstream in2("1.out",ios::in|ios::out);
    ostream out2(in2.rdbuf()); //out2中的内容是对in2的引用,并不是拷贝
    
    cout << in2.rdbuf();//输出1.out的内容到标准输出
    out2 << "Where does this end up?";
    out2.seekp(0,ios::beg);//
    out2 << "And what about this?";
    in2.seekg(0,ios::beg);
    cout << in2.rdbuf();
}
