#ifndef ESPE_H
#define ESPE_H
#include <iostream>
#include <vector>

class Specialty {
  std::string name;
  public:
  Specialty();
  Specialty ( const std::string & );
  Specialty ( const Specialty & );
  void setName( std::string );
  std::string getName() const;
  bool operator==( const Specialty & );
  bool operator!=( const Specialty & );
  Specialty * find ( const std::vector<Specialty *> & );
  Specialty & operator= ( const Specialty & );
};

#endif
