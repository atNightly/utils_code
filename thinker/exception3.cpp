#include <iostream>
#include <string>
using namespace std;

class base
{
    public:
        base()
        {
            cout << "I start to construct" << endl;
            if (count == 3)
                throw string("I am a error");
            count++;
            cout << "construct success" << endl;    
        }

        ~base()
        {
            cout << "I will destruct " << endl;    
        }
    private:    
        static int count;
};

int base::count = 0;

int main()
{
        try{

            base test[5];    

        } catch(...){
            
            cout << "catch some error" << endl;
                
        }
    while(1);
}
