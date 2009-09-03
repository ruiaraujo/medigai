#ifndef CONVENTION_H
#define CONVENTION_H
#include <iostream>

class Convention{
   std::string insurance;
   float discount;
   unsigned long number;
   public:
      Convention(); 
     Convention(std::string, float, unsigned long);
     Convention (const Convention &);
     void setIns(std::string);
     void setDis(float);
     void setNum(unsigned long);
     unsigned long getNum() const;
     std::string getIns() const;
     float getDis() const;
     Convention & operator=( const Convention &);
     bool operator<( const Convention &) const;
     bool operator>( const Convention &) const;
     friend std::ostream & operator<<(std::ostream &, const Convention &);
};



#endif
