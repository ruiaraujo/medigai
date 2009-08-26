#include "utente.h"

using std::string;
using std::ostream;
using std::vector;

unsigned long Utente::UltimoNumero = 1;
Utente::Utente (const Utente &u): Person (u.name,u.tel, u.id), morada(u.morada), insurance(u.insurance) {}
Utente::Utente(string n, string t, string m, Convention p): Person(n,t, UltimoNumero++), morada(m), insurance(p) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0): Person(n,t, UltimoNumero++),morada(m),insurance(seg,d,a){}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0, unsigned long i=0): Person(n,t, i),morada(m),insurance(seg,d,a){}
void Utente::setMor(string m ){morada = m;}
void Utente::setIns(string s, float d){insurance.setIns(s);insurance.setDis(d);}
void Utente::setIns(string s, float d , unsigned long a){insurance.setIns(s);insurance.setDis(d);insurance.setNum(a);}
void Utente::setIns(float d){insurance.setDis(d);}
void Utente::setIns(string s){insurance.setIns(s);}
string Utente::getMor() const {return morada;}
Convention Utente::getIns() const {return insurance;}
void Utente::setUN(unsigned long u ) { UltimoNumero = u; }
long Utente::getUN() const { return UltimoNumero; }
Utente & Utente::operator=( const Utente &u)
{
  if (this != &u)
  {
    name = u.name;
    tel = u.tel;
    morada = u.morada;
    insurance = u.insurance;
  }
  return *this;
}

Utente * Utente::find ( const std::vector<Utente *> & v )
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

Utente * Utente::find ( unsigned long id , const std::vector<Utente *> & v )
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

int Utente::findPos ( unsigned long ced , const vector<Utente *> & v )
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

int Utente::findPos ( const vector<Utente *> & v )
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


std::vector<Utente *>::iterator Utente::insOrd ( std::vector<Utente *> & list_pac )
{
  std::vector<Utente *>::iterator it = list_pac.begin();
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

ostream & operator<<(ostream & os, Utente &u)
{
  os << u.id << "|" << u.name << "|" << u.tel << "|" << u.morada << "|" << u.insurance.getIns() << "|" << u.insurance.getDis() << "|" << u.insurance.getNum() << "|" << u.system; 
 return os;
}
