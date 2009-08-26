#include "date.h"
#include <iomanip>
#include <sstream>

using std::cerr;
using std::endl;
using std::setw;
using std::setfill;
using std::ostream;
using std::ofstream;
using std::fstream;
using std::string;

inline bool bissext(unsigned int year){ return ( year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0 ; }
Date::Date (unsigned int d , unsigned  int m , unsigned int y ) : day(1) , month(1) , year(1970)
{
  try
  {
    setDate( d , m , y );
  }
  catch ( DateNonexistent & ) 
  {
     this->day = 1; this->month = 1; this->year = 1970;
     cerr << "Error: Non-existent Date. Date by default: 1/1/1970" << endl;
  }
 }
Date::Date (const Date &d) : day(d.day), month(d.month), year(d.year) {} 
void Date::setDate( const Date & d) { setDate(d.day, d.month , d.year);}
void Date::setDay( unsigned int day )
{
  if ( day == 0 ) throw DayNonexistent();
  if ( this->month < 8)
  {
    if ( ( this->month%2 ) != 0 )
    {
      if ( day <= 31) this->day = day;
      else throw DayNonexistent();
    }
      else
      {
        if ( this->month == 2 )
        {
          if ( bissext( this->year ) )
          {
            if ( day <= 29 ) this->day = day;
            else throw DayNonexistent();
          }
          else
          {
            if ( day <= 28 ) this->day = day;
            else throw DayNonexistent();       
          }
        }
        else
        {
          if ( day <= 30 ) this->day = day;
          else throw DayNonexistent();     
        }
      }
  }
  else
  {
    if ( ( this->month % 2 ) != 0 )
    {
      if ( day <= 31 ) this->day = day;
      else throw DayNonexistent();
    }
      else
      {
        if ( day <= 30) this->day = day;
        else throw DayNonexistent();
      }
    }
}
void Date::setMonth( unsigned int month )
{
  int tmp = this->month;
  this->month = month;
  try
  {
    this->setDay( day );
  }
  catch(DayNonexistent &)
  {
    this->month = tmp;
    throw MonthNonexistent();
  }
}
void Date::setYear(unsigned int year)
{
  int tmp = this->year;
  this->year = year;
  try
  {
    this->setDay(day);
  }
  catch(DayNonexistent &)
  {
    this->year = tmp;
    throw YearNonexistent();
  }
}
void Date::setDate(unsigned int day, unsigned int month, unsigned int year)
{
  int tmp = this->day, tmp2 = this->month , tmp3 = this->year;
  this->year = year;
  this->month = month;
  try
  {
    this->setDay( day );
  }
  catch(DayNonexistent & DayNonexistent)
  {
    this->year = tmp3;
    this->day = tmp;
    this->month = tmp2;
    throw DateNonexistent();
  }
}
void Date::printDate ( ofstream & os ){  os <<  this->getDate(); }
void Date::printDate ( ostream & os )
{
  os << setfill('0') << setw(2) << this->day << "/" << setfill('0') << setw(2) << this->month;
  os << "/" << setfill('0') << setw(4)  << this->year;
}

void Date::printDate ( fstream & os ){  os <<  this->getDate(); }

unsigned int Date::getDay() const { return this->day; }
unsigned int Date::getMonth() const { return this->month; }
unsigned int Date::getYear() const { return this->year; }
bool Date::operator==( const Date & d )
{ return d.day == this->day && d.month == this->month && d.year == this->year; }
bool Date::operator<( const Date & d )
{
 if ( *this == d ) return false;
 if ( this->year < d.year )
   return true;
 else
   if ( this->year > d.year )
      return false;
   else
   {
      if ( this->month < d.month )
        return true;
      else
        if ( this->month > d.month )
          return false;
        else
          if ( this->day < d.day )
            return true;
          else
            return false;
   }
}
bool Date::operator>( const Date & d )
{
 if ( *this == d ) return false;
 if ( this->year < d.year )
   return false;
 else
   if ( this->year > d.year )
      return true;
   else
   {
      if ( this->month < d.month )
        return false;
      else
        if ( this->month > d.month )
          return true;
        else
          if ( this->day < d.day )
            return false;
          else
            return true;
    }
}
bool Date::operator<=( const Date & d )
{
 if ( *this == d ) return true;
 if ( this->year < d.year )
   return true;
 else
   if ( this->year > d.year )
      return false;
   else
   {
      if ( this->month < d.month )
        return true;
      else
        if ( this->month > d.month )
          return false;
        else
          if ( this->day < d.day )
            return true;
          else
            return false;
    }
}
bool Date::operator>=( const Date & d )
{
 if ( *this == d ) return true;
 if ( this->year < d.year )
   return false;
 else
   if ( this->year > d.year )
      return true;
   else
   {
      if ( this->month < d.month )
        return false;
      else
        if ( this->month > d.month )
          return true;
        else
          if ( this->day < d.day )
            return false;
          else
            return true;
    }
}
Date & Date::operator=( const Date & date)
{
  if ( this != &date )
  {
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
  }
  return *this;
}
ostream & operator<<(ostream & os, const Date &d)
{
  os << setfill('0') << setw(2) << d.day << "/" << setfill('0') << setw(2) << d.month;
  os << "/" << setfill('0') << setw(4)  << d.year;
  return os;
}

string Date::getDate()
{
  std::ostringstream sout;
  sout << setfill('0') << setw(2) << this->day << "/" << setfill('0') << setw(2) << this->month;
  sout << "/" << setfill('0') << setw(4)  << this->year;
  return sout.str();
}
