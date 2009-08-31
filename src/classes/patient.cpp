#include "patient.h"
#include <iostream>
#include "person.h"
#include "convention.h"

using std::string;
using std::ostream;
using std::vector;

unsigned long Patient::LastNumber = 1;
Patient::Patient (const Patient &u): Person (u.name,u.tel, u.id), address(u.address), insurance(u.insurance) {}
Patient::Patient(string n, string t, string m, Convention p): Person(n,t, LastNumber++), address(m), insurance(p) {}
Patient::Patient(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0): Person(n,t, LastNumber++),address(m),insurance(seg,d,a){}
Patient::Patient(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0, unsigned long i=0): Person(n,t, i),address(m),insurance(seg,d,a){}
void Patient::setAdd(string address ){ this->address = address;}
void Patient::setIns(string s, float d){insurance.setIns(s);insurance.setDis(d);}
void Patient::setIns(string s, float d , unsigned long a){insurance.setIns(s);insurance.setDis(d);insurance.setNum(a);}
void Patient::setIns(float d){insurance.setDis(d);}
void Patient::setIns(string s){insurance.setIns(s);}
string Patient::getAdd() const {return this->address;}
Convention Patient::getIns() const {return this->insurance;}
void Patient::setUN(unsigned long u ) { LastNumber = u; }
long Patient::getUN() const { return LastNumber; }
Patient & Patient::operator=( const Patient &u)
{
  if (this != &u)
  {
    this->name = u.name;
    this->tel = u.tel;
    this->address = u.address;
    this->insurance = u.insurance;
  }
  return *this;
}

Patient * Patient::find ( const std::vector<Patient *> & v )
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

Patient * Patient::find ( unsigned long id , const std::vector<Patient *> & v )
{
  if ( !v.empty() )
  {
    int left = 0 , right = v.size() - 1;
    while ( left <= right )
    {
      int middle = ( left + right ) / 2;
      if ( id == v.at( middle )->getId() ) return v.at( middle );
      else if ( id < v.at( middle )->getId() ) right = middle - 1;
      else left = middle + 1;
    }
  }
  return NULL;
}

int Patient::findPos ( unsigned long ced , const vector<Patient *> & v )
{
  int left = 0, right = v.size() - 1;
  while (left <= right)
  {
    int middle = (left + right) / 2;
    if ( ced == (*v.at(middle)).getId() ) return middle;
    else if ( ced < (*v.at(middle)).getId() ) right = middle - 1;
    else left = middle + 1;
  }
  return -1;
}

int Patient::findPos ( const vector<Patient *> & v )
{
  int left = 0, right = v.size() - 1;
  while (left <= right)
  {
    int middle = (left + right) / 2;
    if ( this->id == v.at(middle)->getId() ) return middle;
    else if ( this->id < v.at(middle)->getId() ) right = middle - 1;
    else left = middle + 1;
  }
  return -1;
}


std::vector<Patient *>::iterator Patient::insOrd ( std::vector<Patient *> & list_pac )
{
  std::vector<Patient *>::iterator it = list_pac.begin();
  for ( int i = 0 ; i < (int) list_pac.size() ; i++ )
  {
    if ( list_pac.at( i )->getId() >= this->getId() )
    {
      list_pac.insert( it , this );
      it++;
      return it;
    }
    it++;
  }
  list_pac.push_back( this );
  return it;
} 

ostream & operator<<(ostream & os, Patient &u)
{
  os << u.id << "|" << u.name << "|" << u.tel << "|" << u.address << "|" << u.insurance.getIns() << "|" << u.insurance.getDis() << "|" << u.insurance.getNum() << "|" << u.system; 
 return os;
}
