#include <cctype>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <stdint.h>
#include <ostream>
#include <iomanip>
using namespace std;

class Date
{
  public:
    Date(int year,int month,int day)
         :m_day(day),m_month(month),m_year(year)
    {
    
    }
    ~Date()
    {
    
    }
    
    int getMonth()const {
        return m_month;    
    }

    int getDay()const {
        return m_day;    
    }
    
    int getYear()const {
        return m_year;
    }
    
    int m_day;
    int m_month;
    int m_year;
};

ostream& operator<<(ostream& os,const Date& d) {
    char fillc = os.fill('0');
    //设置填充字符,当输出长度小于指定的长度的时候用于进行填充
    os<<setw(2) << d.getMonth() << '-' //setw用来设置输出长度
      <<setw(2) << d.getDay() << '-'
      <<setw(4) << setfill(fillc) << d.getYear();
      //setfill还原回原来的填充字符
    return os;
    
}

istream& operator>>(istream& is,Date& d) {
    is >> d.m_month;
    char dash;
    is >> dash;
    if (dash != '-')
        is.setstate(ios::failbit);
        //设置流错误状态,这使得下面的所有操作都会被忽略
    is >> d.m_day;
    cout << "OK" << endl;
    is >> dash;
    if (dash != '-')
        is.setstate(ios::failbit);
    is >> d.m_year;
    return is;
}

int main()
{
    Date date(2015,7,24);
    cout << date << endl;
    cin >> date;
    cout << date << endl;
}
