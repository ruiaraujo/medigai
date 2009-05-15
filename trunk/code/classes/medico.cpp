#include "headers/medico.h"

Medico::Medico (Pessoa &p, Especialidade *e, Hora i, Hora f, unsigned int d=0) : Pessoa(p), espe(e), duracao(d), fim (f), inicio(i) {}
Medico::Medico (Pessoa &p, Especialidade *e, unsigned int d=0): Pessoa(p), espe(e), duracao(d) {}
Medico::Medico (string n, string t="", unsigned int d=0, unsigned long c=0): Pessoa(n,t,c), espe(), duracao(d) {}
Medico::Medico (const Medico &m): Pessoa(m.nome,m.tel, 0), espe(m.espe), duracao(m.duracao) {}
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
void Medico::setEspe(Especialidade *e){espe = e;}
Especialidade * Medico::getEspe() const{return espe;}
unsigned long Medico::getCed() const {return id;}
unsigned int Medico::getDur() const {return duracao;}
void Medico::setIni(Hora &i){inicio = i;}
void Medico::setFim(Hora &f){fim = f;}


ostream & operator<<(ostream & os, Medico &m)
{
  os << m.id <<"|"<< m.nome << "|" << m.tel << "|" << m.espe->getNom()<< "|"   << endl; 
 return os;
}
