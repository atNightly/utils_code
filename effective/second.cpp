#include <iostream>
#include "common.h"

test2& gettest()
{
    static test2 t2;
    return t2;
}

