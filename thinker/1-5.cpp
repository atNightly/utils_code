#include <iostream>


class foo
{
    public:
        static cleanup(void *data)
        {
            
        }
        static int count;
    private:
        void* operator new(size_t size)
        {
            cout << "start to new some " << endl;
            if(count == 11)
                throw string("occus some error");
            void *p = new size;
            count++:
            return p;
        }
}

c
int main()
{
    while(1)
    {
        try{
            
            
        }catch{
            
            
        } 
        cout << "continue to run" << endl;
    }
}
