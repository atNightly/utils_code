#include <iostream>



int main()
{
    

typedef char T_must_be_complete_type[sizeof(char) == 0 ? -1 : 1];
T_must_be_complete_type dummy; (void) dummy;


}
