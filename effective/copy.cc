#include <iostream>

class Bitmap
{
    //....
};

class Widget {
  //....
    Widget& operator=(const Widget& rhs);
private:
    Bitmap *pb;
};

Widget& Widget::operator=(const Widget& rhs)
{
    if(this == &rhs) return *this;
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
};


Widget& Widget::operator=(const Widget& rhs)
{
    Bitmap *pOrig = pb;
    pb = new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
};


Widget& Widget::operator=(const Widget& rhs)
{
    Widget temp(rhs);
    swap(temp);
    return *this;
};
