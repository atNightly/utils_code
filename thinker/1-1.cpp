#include <iostream>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string>

using namespace std;

int return_error()
{
    //do some thing
    cout << "may occurs some error" << endl;
    return -1; 
}

void setup_errno()
{
    //do some thing
    cout << "may occurs some error" << endl;
    errno = EBADE;       
}


void signal_error()
{
    //do some thing
    cout << "may occurs some error" << endl;
    raise(SIGUSR1); 
}

void handle_error(int sig)
{
    cout << "occurs some error" << endl;    
}

void exception_throw()
{
    //do some thing
    throw string("the malloc exists error");   
}
int main()
{
    signal(SIGUSR1,handle_error);
    int ret =return_error();
    if (ret == -1)
        cout << "occurs some error" << endl;
    setup_errno();
        perror("do some thing");
    signal_error();
    try{
        exception_throw();   
    }
    catch(string& e){
        cout << e << endl;
    }
}
