#ifndef RATIONAL_H_
#define RATIONAL_H_
#include <iosfwd>

class Rational {

public:
    Rational(int numerator = 0,int denominator = 1);
    Rational operator-()const;
    friend Rational operator+(const Rational&,
                              const Rational&);
     
    friend Rational operator-(const Rational&,
                              const Rational&);
     
    friend Rational operator*(const Rational&,
                              const Rational&);
     
    friend Rational operator/(const Rational&,
                              const Rational&);
    friend std::ostream& operator<<(std::ostream&,const Rational&);
    friend std::istream& operator>>(std::istream&,Rational&);
    Rational& operator+=(const Rational&);
    Rational& operator-=(const Rational&);
    Rational& operator*=(const Rational&);
    Rational& operator/=(const Rational&);
    friend bool operator<(const Rational&,const Rational&);
    friend bool operator>(const Rational&,const Rational&);
    friend bool operator<=(const Rational&,const Rational&);
    friend bool operator>=(const Rational&,const Rational&);
    friend bool operator==(const Rational&,const Rational&);
    friend bool operator!=(const Rational&,const Rational&);
};
#endif //RATIONAL_H_
