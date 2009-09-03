#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <fstream>
#include "DateExceptions.h"

class Date {
  unsigned int day;
  unsigned int month;
  unsigned int year;
  public:
    Date( const Date & );
    Date( unsigned int = 1 , unsigned int = 1 , unsigned int = 1970 );
    void setDay( unsigned int );
    void setMonth( unsigned int );
    void setYear( unsigned int );
    void setDate( unsigned int , unsigned int , unsigned int );
    void setDate ( const Date & );
    void printDate ( std::ostream & os);
    void printDate ( std::ofstream & os);    
    void printDate ( std::fstream & os);
    std::string getDate();
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    bool operator==( const Date & );
    bool operator<( const Date & );
    bool operator>( const Date & );
    bool operator<=( const Date & );
    bool operator>=( const Date & );
    Date & operator=( const Date & );
    friend std::ostream & operator<<(std::ostream & os, const Date &);
    
};

#endif
