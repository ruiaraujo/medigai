#include "consulta.h"
#include "medico.h"
#include "utente.h"
#include "date.h"
#include "hour.h"
#include <iostream>


using std::vector;
using std::ostream;
using std::string;
using std::endl;

Consulta::Consulta(const Consulta & c):  med(c.med) , pac(c.pac), data(c.data), hora(c.hora) , duracao(c.duracao), 
                                        preco(c.preco) , estado('m') {}
Consulta::Consulta(Medico *m , Utente *u ,const Date & d , const Hour & h , float p ) : med(m),  pac(u) , data(d), 
                                                        hora(h), duracao( m->getDur() ), preco(p) , estado('m') {}
Medico * Consulta::getMed() const {return this->med;}
Utente * Consulta::getUte() const {return this->pac; }
Date Consulta::getDat() const{return data;}
Hour Consulta::getHor() const{return hora;}
unsigned int Consulta::getDur() const { return duracao; }
float Consulta::getPre() const { return preco;}
void Consulta::setPre( float p ) { preco = p; }
void Consulta::setDur( unsigned int d ) { duracao = d; }
void Consulta::setMed( Medico * m ) { med = m; }
void Consulta::setUte( Utente * u ) { pac = u; }
void Consulta::setHor(unsigned int h, unsigned int m){hora.setHour(h,m);}
void Consulta::setHor(const Hour &h){hora.setHour(h);}
void Consulta::setDat(unsigned int d, unsigned int m , unsigned int a ){data.setDate( d , m , a );}
void Consulta::setDat( const Date &d){ data.setDate( d );}
char Consulta::getEst() const {return estado;}
void Consulta::setEst( char c ) { estado = c;}
ostream & operator<< ( ostream & os , Consulta & c )
{
  os << c.med->getCed() << "|" << c.pac->getId() << "|" << c.data << "|" << c.hora << "|" << c.preco << "|" << c.duracao << "|" << c.estado;
  return os;
}

vector<Consulta *>::iterator Consulta::insOrd ( vector<Consulta *> & c )
{
  vector<Consulta *>::iterator it = c.begin();
  vector<Consulta *>::iterator it_f = c.end();
  it_f--;
  for (int i = c.size()-1 ; i >= 0 ; i--,it_f--)
  {
    if ( c.at( i )->getMed()->getId() == this->getMed()->getId() )
    {
      break;
    }
  it_f++;
  }
  for ( int i = 0 ; i < (int) c.size() ; i++ ,it++)
  {
    if ( c.at( i )->getMed()->getId() >= this->getMed()->getId() )
    {
        for ( ; it < it_f ; it++,it_f--)
        {
          if ( c.at( i )->getDat() >= this->getDat() )
          {
            for ( ; it < it_f; it++)
            {
              if ( c.at( i )->getHor() >= this->getHor() )
              {
                c.insert( it , this );
                it++;
                return it;
              }
            }
            c.insert( it , this );
            it++;
            return it;
          }
        }
        c.insert( it , this);
        it++;
        return it;
    }
  }
  c.push_back(this);
  it_f = c.end();
  it_f--;
  return it_f;
}

int Consulta::findPos ( const vector<Consulta *> & c ) const
{
  for ( int i = 0 ; i < (int) c.size() ; i++ )
  {
    if ( c.at( i )->getMed()->getId() == this->getMed()->getId() )
    {
        for ( ;  i < (int) c.size()  ; i++  )
        {
          if ( c.at( i )->getDat() == this->getDat() )
          {
            for ( ;  i < (int) c.size() ; i++)
            {
              if ( c.at( i )->getHor() == this->getHor() )
              {
                return i;
              }
            }
          }
        }
    }
  }
  return -1;
}

vector<Consulta *>::iterator Consulta::find (  vector<Consulta *> & c )
{
  vector<Consulta *>::iterator it = c.begin();
  for ( int i = 0 ; i < (int) c.size() ; i++ ,it++)
  {
    if ( c.at( i )->getMed()->getId() == this->getMed()->getId() )
    {
        for ( ;  i < (int) c.size()  ; i++ , it++ )
        {
          if ( c.at( i )->getDat() == this->getDat() )
          {
            for ( ;  i < (int) c.size() ; i++, it++)
            {
              if ( c.at( i )->getHor() == this->getHor() )
              {
                return it;
              }
            }
          }
        }
    }
  }
  it = c.end();
  return it;

}

