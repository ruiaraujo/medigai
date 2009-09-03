#include "convention.h"
#include <iostream>
using std::string;
using std::ostream;

Convention::Convention(string s, float d, unsigned long a): insurance(s),discount(d), number (a) {}
Convention::Convention() : insurance(""), discount(0), number (0) {}
Convention::Convention (const Convention & s ) : insurance(s.insurance), discount(s.discount), number(s.number) {}
void Convention::setIns(string s){insurance = s;}
void Convention::setDis(float d){discount = d;}
void Convention::setNum(unsigned long a) {number = a;}
unsigned long Convention::getNum() const {return number;}
string Convention::getIns() const {return insurance;}
float Convention::getDis() const {return discount;}
Convention & Convention::operator=( const Convention & s)
{
  if (this != &s )
  {
   insurance = s.insurance;
   discount = s.discount;
    number = s.number;
  }
  return *this;
}
bool Convention::operator<( const Convention & s ) const { return discount < s.discount ? true:false; }
bool Convention::operator>( const Convention & s ) const { return discount > s.discount ? true:false; }

ostream & operator<<(ostream & os, Convention &c)
{
  os << c.getIns() << "|" << c.getDis() << "|" << c.getNum();
  return os;
}
