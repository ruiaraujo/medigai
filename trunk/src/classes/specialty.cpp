#include "specialty.h"
#include <iostream>
#include <vector>

using std::vector;
using std::string;

Specialty::Specialty() : name("") {}
Specialty::Specialty ( const string & e ): name(e) {}
Specialty::Specialty ( const Specialty & e ) : name(e.name) {}
void Specialty::setName( string name ) { this->name = name; }
string Specialty::getName() const {return this->name;}
bool Specialty::operator==( const Specialty & e){ return e.name == this->name; }
bool Specialty::operator!=( const Specialty & e){ return e.name != this->name; }
Specialty * Specialty::find ( const vector<Specialty *> & list_esp )
{
  for( int i = 0 ; i < (int) list_esp.size() ; i++ )
  {
    if ( this->name == list_esp.at( i )->getName() )
      return list_esp.at( i );
  }
  return NULL;
}
Specialty & Specialty::operator=( const Specialty & e)
{
  if ( this != &e )
    this->name = e.name;
  return *this;
}

