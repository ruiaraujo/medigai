#include "consulta.h"

Consulta::Consulta(const Consulta &c):  med(c.med) , pac(c.pac), data(c.data), hora(c.hora) , duracao(c.duracao), preco(c.preco) , estado('m') {}
Consulta::Consulta(Medico *m , Utente *u , Data & d , Hora & h , float p ) : med(m),  pac(u) , data(d), hora(h), duracao( m->getDur() ), preco(p) , estado('m') {}
Medico * Consulta::getMed() const{return med;}
Utente * Consulta::getUte() const{return pac;}
Data Consulta::getDat() const{return data;}
Hora Consulta::getHor() const{return hora;}
unsigned int Consulta::getDur() const { return duracao; }
float Consulta::getPre() const { return preco;}
void Consulta::setPre( float p ) { preco = p; }
void Consulta::setDur( unsigned int d ) { duracao = d; }
void Consulta::setMed( Medico * m ) { med = m; }
void Consulta::setUte( Utente * u ) { pac = u; }
void Consulta::setHor(unsigned int h, unsigned int m){hora.setHora(h,m);}
void Consulta::setHor(const Hora &h){hora.setHora(h);}
void Consulta::setDat(unsigned int d, unsigned int m , unsigned int a ){data.setData( d , m , a );}
void Consulta::setDat( const Data &d){ data.setData( d );}
char Consulta::getEst() const {return estado;}
void Consulta::setEst( char c ) { estado = c;}
ostream & operator<< ( ostream & os , Consulta & c )
{
  os << c.med->getCed() << "|" << c.pac->getId() << "|" << c.data << "|" << c.hora << "|" << c.preco << "|" << c.duracao << "|" << c.estado;
  return os;
}
