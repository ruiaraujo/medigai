#ifndef DATE_EXCEPTION_H
#define DATE_EXCEPTION_H
#include <stdexcept>
#include <exception>
using std::runtime_error;

class DayNonexistent : public runtime_error{
  public:
    DayNonexistent(): runtime_error( "Non-existent day" ) {}
};

class MonthNonexistent : public runtime_error{
  public:
    MonthNonexistent(): runtime_error( "Non-existent month with the current day!" ) {}
};

class YearNonexistent : public runtime_error{
  public:
    YearNonexistent(): runtime_error( "Non-existent year with the current day or month!" ) {}
};

class DateNonexistent : public runtime_error{
  public:
    DateNonexistent(): runtime_error( "Non-existent Date!" ) {}
};

#endif
