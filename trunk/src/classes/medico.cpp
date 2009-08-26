#include "medico.h"

using std::string;
using std::vector;
using std::ostream;

Medico::Medico ( const Person &p, Especialidade *e, Hour i, Hour f, unsigned int d=0) : 
                                                    Person(p), espe(e), duracao(d) , dur_max(0), inicio(i), fim (f) {}
Medico::Medico ( const Person & p, Especialidade *e, unsigned int d=0): Person(p), espe(e), duracao(d) , 
                                                                      dur_max(0) , inicio(0,0) , fim (0,0){}
Medico::Medico (string n, string t="", unsigned int d=0, unsigned long c=0): Person(n,t,c), espe(NULL) ,  duracao(d) , dur_max(0), inicio(0,0) , fim (0,0){}
Medico::Medico (const Medico &m): Person(m.name,m.tel, 0), espe(m.espe), duracao(m.duracao) , dur_max(m.dur_max) , inicio(m.inicio) , fim(m.fim){}
Medico & Medico::operator=( const Medico & m)
{
  if (this != &m)
  {
    name = m.name;
    tel= m.tel;
    espe = m.espe;
  }
  return *this;
}
Hour Medico::getIni() const {return inicio;}
Hour Medico::getFim() const {return fim;}
void Medico::setDur(unsigned int d){duracao = d;}
void Medico::setDurM(unsigned int d){dur_max = d;}
void Medico::setEspe(Especialidade *e){espe = e;}
Especialidade * Medico::getEspe() const{return espe;}
unsigned long Medico::getCed() const {return id;}
unsigned int Medico::getDur() const {return duracao;}
unsigned int Medico::getDurM() const {return dur_max;}
void Medico::setIni( const Hour & i ){inicio = i;}
void Medico::setFim( const Hour & f ){fim = f;}

Medico * Medico::find ( const std::vector<Medico *> & v )
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

Medico * Medico::find ( unsigned long id ,  const std::vector<Medico *> & v )
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

int Medico::findPos ( unsigned long ced , const vector<Medico *> & v )
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

int Medico::findPos ( const vector<Medico *> & v )
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

std::vector<Medico *>::iterator Medico::insOrd ( std::vector<Medico *> & list_med )
{
  std::vector<Medico *>::iterator it = list_med.begin();
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


ostream & operator<<(ostream & os, Medico &m)
{
  os << m.id <<"|"<< m.name << "|" << m.tel << "|" << m.espe->getNom()<< "|"  << m.inicio << "|" << m.fim << "|" << m.duracao << "|" << m.dur_max << "|" << m.system; 
 return os;
}
