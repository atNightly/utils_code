#include <iostream>
#include <exception>

using namespace std;

class exception_throw
{
    public:
    class Exception
    {
        public:
            Exception(const char* str):m_exception(str)
            {}
            ~Exception(){ cout << "i am destruct " << endl;};
            const char* what()
            {
                return m_exception;    
            }
        private:
        const char* m_exception;  
    };
    void throw_exception() throw(Exception)
    {
        //do some thing
        cout << "star to throw a exception" << endl;
        throw Exception("I am a exception");
    }
  private:  
};

int main()
{
    exception_throw test;
    try{
            test.throw_exception();  
    }catch (exception_throw::Exception& recv){
        cout << recv.what() << endl;
        cout << "catch a exception" << endl;       
    }
    //test离开 try的作用域后就会析构
    while(1);
}
