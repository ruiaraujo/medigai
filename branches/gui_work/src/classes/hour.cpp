#include "hour.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "HourExceptions.h"

Hour::Hour(unsigned int h,unsigned  int m): hour(h) , min(m) {
  try
  {
    setHour(h);
    setMin(m);
  }
  catch(...)
  {
    setHour(0,0);
    std::cerr << "Error: Non-existent hour. Hour default to 0:0" << std::endl;  
    throw HourNonexistent();  
  }
}
Hour::Hour( const Hour & h ) : hour(h.hour), min(h.min) {}
void Hour::setHour( unsigned int hour ){ if ( hour < 24 ) this->hour = hour; else throw HourNonexistent();}
void Hour::setMin( unsigned int min ){ if ( min < 60 ) this->min = min; else throw MinNonexistent();}
void Hour::setHour( const Hour &h){setHour(h.hour,h.min);}
void Hour::setHour( unsigned int hour , unsigned int min )
{
  try
  {
    setHour( hour );
    setMin( min );
  }
  catch (...)
  {
    throw HourNonexistent();  
  }
}
unsigned int Hour::getHor() const { return this->hour; }
unsigned int Hour::getMin() const { return this->min; }
Hour operator+( const Hour & hour , int extra)
{
  Hour tmp ( hour );
  if ( extra > 0 )
  {
    tmp.min += extra%60;
    extra -= extra%60;
    if  ( tmp.min >59)
    {
      tmp.hour += tmp.min/60;
      tmp.min = tmp.min%60;
    }
    tmp.hour += extra/60;
    if ( tmp.hour>23)
      tmp.hour = tmp.hour%24;
  }
  else 
    if ( extra < 0 )
      tmp = tmp - ( -extra) ;
  return tmp;
}

Hour operator-( const Hour & h , int extra)
{
  int min = h.min , hor = h.hour;
  if (extra > 0)
  {
    min -= extra%60;
    extra -= extra%60;
    while ( min < 0 )
    {
     min += 60;
     hor--;
    }
    hor -= extra/60;
    while (hor < 0 )
      hor += 24;
  }
  else
    if ( extra < 0 )
    {
      Hour a = h + ( -extra );
      return a;
    }
  Hour a (hor , min );
  return a;
}
int Hour::operator-( Hour & h ){return ( this->hour - h.hour )*60  + this->min-h.min;}// diferença em minutos entre duas datas (se negativo hour )
bool Hour::operator<( const Hour & h ) const
{
 if (h.hour == hour )
 {
  if (min < h.min)
    return true;
  else
    return false;
 }
 else
   if (hour < h.hour) return true;
   else return false;
}
bool Hour::operator<=( const Hour & h ) const
{
 if ( h.hour == hour && h.min == min ) return true; 
 if (h.hour == hour )
 {
  if (min < h.min)
    return true;
  else
    return false;
 }
 else
   if (hour < h.hour) return true;
   else return false;
}
bool Hour::operator>( const Hour & h ) const
{
 if (h.hour == hour )
 {
  if (min < h.min)
    return false;
  else
    return true;
 }
 else
   if (hour < h.hour) return false;
   else return true;
}
bool Hour::operator>=( const Hour &h ) const
{
 if ( h.hour == hour && h.min == min ) return true; 
 if (h.hour == hour )
 {
  if (min < h.min)
    return false;
  else
    return true;
 }
 else
   if (hour < h.hour) return false;
   else return true;
}
Hour & Hour::operator=( const Hour & h )
{
  if (this != &h)
  {
    hour = h.hour;
    min = h.min;
  }
  return *this;
}
bool Hour::operator==( const Hour & h ) const { return ( this->hour == h.hour && this->min==h.min ); }
bool Hour::operator!=( const Hour & h ) const { return !( this->hour == h.hour && this->min==h.min ); }
std::ostream & operator << ( std::ostream & os , const Hour & h )
{
  os << std::setfill('0') << std::setw(2) << h.hour << ":" << std::setfill('0') << std::setw(2) << h.min;
  return os;
}

std::string Hour::getHour() const
{
  std::ostringstream sout;
  sout << std::setfill('0') << std::setw(2) << this->hour << ":" << std::setfill('0') << std::setw(2) << this->min;
  return sout.str();
}
