#include "person.h"
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

Person::Person (string n, string t, unsigned long i) : name( n ), tel( t ), system( true ) , id( i ) {}
Person::Person (const Person & p) : name(p.name), tel( p.tel ), system( true ) , id( p.id ){}
void Person::setName(string name ){ this->name = name; }
void Person::setTel(string tel ){ this->tel = tel; }
string Person::getName() const {return this->name; }
string Person::getTel() const{ return this->tel; }
unsigned long Person::getId() const { return this->id; }
bool Person::getSis() const {return this->system;}
void Person::setSis( bool e ) { this->system = e; }
Person::~Person() {}
Person & Person::operator=( const Person & p )
{
  if (this != &p)
  {
    name = p.name;
    tel= p.tel;
  }
  return *this; 
}

Person * Person::find ( const std::vector<Person *> & v )
{
  if ( !v.empty() )
  {
    int left = 0 , right = v.size() - 1;
    while ( left <= right )
    {
      int middle = ( left + right ) / 2;
      if ( this->id == v.at( middle )->getId() ) return v.at( middle );
      else if ( this->id < v.at( middle )->getId() ) right = middle - 1;
      else left = middle + 1;
    }
  }
  return NULL;
}

ostream & operator<<(ostream & os, const Person & p)
{
  os << p.id << "|" << p.name << "|" << p.tel << "|" << p.system; 
 return os;
}
