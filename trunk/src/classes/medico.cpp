#include "medico.h"

using std::string;
using std::ostream;

Medico::Medico (Pessoa &p, Especialidade *e, Hora i, Hora f, unsigned int d=0) : Pessoa(p), espe(e), duracao(d) , dur_max(0), inicio(i), fim (f) {}
Medico::Medico (Pessoa &p, Especialidade *e, unsigned int d=0): Pessoa(p), espe(e), duracao(d) , dur_max(0) , inicio(0,0) , fim (0,0){}
Medico::Medico (string n, string t="", unsigned int d=0, unsigned long c=0): Pessoa(n,t,c), espe(NULL) ,  duracao(d) , dur_max(0), inicio(0,0) , fim (0,0){}
Medico::Medico (const Medico &m): Pessoa(m.nome,m.tel, 0), espe(m.espe), duracao(m.duracao) , dur_max(m.dur_max) , inicio(m.inicio) , fim(m.fim){}
Medico & Medico::operator=(Medico &m)
{
  if (this != &m)
  {
    nome = m.nome;
    tel= m.tel;
    espe = m.espe;
  }
  return *this;
}
Hora Medico::getIni() const {return inicio;}
Hora Medico::getFim() const {return fim;}
void Medico::setDur(unsigned int d){duracao = d;}
void Medico::setDurM(unsigned int d){dur_max = d;}
void Medico::setEspe(Especialidade *e){espe = e;}
Especialidade * Medico::getEspe() const{return espe;}
unsigned long Medico::getCed() const {return id;}
unsigned int Medico::getDur() const {return duracao;}
unsigned int Medico::getDurM() const {return dur_max;}
void Medico::setIni( const Hora & i ){inicio = i;}
void Medico::setFim( const Hora & f ){fim = f;}

ostream & operator<<(ostream & os, Medico &m)
{
  os << m.id <<"|"<< m.nome << "|" << m.tel << "|" << m.espe->getNom()<< "|"  << m.inicio << "|" << m.fim << "|" << m.duracao << "|" << m.dur_max << "|" << m.sistema; 
 return os;
}
