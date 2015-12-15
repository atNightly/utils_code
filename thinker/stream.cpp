#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>

using namespace std;

int main()
{
    const int SZ = 100;
    char buf[SZ];
    {
        ifstream in("1-1.cpp");
        ofstream out("out.txt");
        int i = 1;
        while(in.get(buf,SZ)) {
            in.get(); //为什么还要有个get ?
 //           cout << buf << endl;
            out << i++ << ": " << buf << endl;    
        }    
    } //Destructors close in & out
    
    {
        ifstream in("1-2.cpp") ;
        while(in.getline(buf,SZ)) {
            char *cp = buf;
           // while(*cp != ':') 
           //     ++cp;
           // cp +=2; 
            cout << cp << endl;   
        }  
    }
}
