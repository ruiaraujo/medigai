#include "medico.h"

using std::string;
using std::vector;
using std::ostream;

Doctor::Doctor ( const Person &p, Specialty *e, Hour i, Hour f, unsigned int d=0) : 
                                                    Person(p), specialty(e), duracao(d) , dur_max(0), inicio(i), fim (f) {}
Doctor::Doctor ( const Person & p, Specialty *e, unsigned int d=0): Person(p), specialty(e), duracao(d) , 
                                                                      dur_max(0) , inicio(0,0) , fim (0,0){}
Doctor::Doctor (string n, string t="", unsigned int d=0, unsigned long c=0): Person(n,t,c), specialty(NULL) ,  duracao(d) , dur_max(0), inicio(0,0) , fim (0,0){}
Doctor::Doctor (const Doctor &m): Person(m.name,m.tel, 0), specialty(m.specialty), duracao(m.duracao) , dur_max(m.dur_max) , inicio(m.inicio) , fim(m.fim){}
Doctor & Doctor::operator=( const Doctor & m)
{
  if (this != &m)
  {
    this->name = m.name;
    this->tel= m.tel;
    this->specialty = m.specialty;
  }
  return *this;
}
Hour Doctor::getIni() const {return inicio;}
Hour Doctor::getFim() const {return fim;}
void Doctor::setDur(unsigned int d){duracao = d;}
void Doctor::setDurM(unsigned int d){dur_max = d;}
void Doctor::setEspe(Specialty * specialty ){this->specialty = specialty;}
Specialty * Doctor::getEspe() const{return specialty;}
unsigned int Doctor::getDur() const {return duracao;}
unsigned int Doctor::getDurM() const {return dur_max;}
void Doctor::setIni( const Hour & i ){inicio = i;}
void Doctor::setFim( const Hour & f ){fim = f;}

Doctor * Doctor::find ( const std::vector<Doctor *> & v )
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

Doctor * Doctor::find ( unsigned long id ,  const std::vector<Doctor *> & v )
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

int Doctor::findPos ( unsigned long ced , const vector<Doctor *> & v )
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

int Doctor::findPos ( const vector<Doctor *> & v )
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

std::vector<Doctor *>::iterator Doctor::insOrd ( std::vector<Doctor *> & list_med )
{
  std::vector<Doctor *>::iterator it = list_med.begin();
  for ( int i = 0 ; i < (int) list_med.size() ; i++ )
  {
    if ( list_med.at( i )->getId() >= this->getId() )
    {
      list_med.insert( it , this );
      it++;
      return it;
    }
    it++;
  }
  list_med.push_back( this );
  return it;
} 


ostream & operator<<(ostream & os, Doctor &m)
{
  os << m.id <<"|"<< m.name << "|" << m.tel << "|" << m.specialty->getName()<< "|"  << m.inicio << "|" << m.fim << "|" << m.duracao << "|" << m.dur_max << "|" << m.system; 
 return os;
}
