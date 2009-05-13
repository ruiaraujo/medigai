#include "headers/pessoas.h"

Pessoa::Pessoa (string n, string t, unsigned long i) : nome(n), tel(t), id(i) {}
Pessoa::Pessoa (const Pessoa & p) : nome(p.nome), tel(p.tel), id(p.id) {}
void Pessoa::setNome(string n){nome=n;}
void Pessoa::setTel(string t){tel=t;}
string Pessoa::getNome() const {return nome;}
string Pessoa::getTel() const{return tel;}
unsigned long Pessoa::getId() const {return id;}
Pessoa & Pessoa::operator=(Pessoa &p)
{
  if (this != &p)
  {
    nome = p.nome;
    tel= p.tel;
  }
  return *this; 
}


Medico::Medico (string n, string t="", string e="", unsigned int d=0, unsigned long c=0): Pessoa(n,t,c), especialidade(e), duracao(d) {}
Medico::Medico (const Medico &m): Pessoa(m.nome,m.tel, 0), especialidade(m.especialidade), duracao(m.duracao) {}
Medico & Medico::operator=(Medico &m)
{
  if (this != &m)
  {
    nome = m.nome;
    tel= m.tel;
    especialidade = m.especialidade;
  }
  return *this;
}

void Medico::setDur(unsigned int d){duracao = d;}
void Medico::setEspe(string e){especialidade = e;}
string Medico::getEspe() const{return especialidade;}
unsigned long Medico::getCed() const {return id;}
unsigned int Medico::getDur() const {return duracao;}


long Utente::UltimoNumero = 0;
Utente::Utente (const Utente &u): Pessoa (u.nome,u.tel, UltimoNumero++), morada(u.morada), seguro(u.seguro) {}
Utente::Utente(string n, string t, string m, Convencao * p): Pessoa(n,t, UltimoNumero++), morada(m), seguro(p) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0): Pessoa(n,t, UltimoNumero++), morada(m)
{
  Convencao *a = new Convencao;
  a->setSeg(seg);
  a->setDes(d);
  seguro = a;
}
void Utente::setMor(string m ){morada = m;}
void Utente::setSeg(string s, float d){seguro->setSeg(s);seguro->setDes(d);}
void Utente::setSeg(float d){seguro->setDes(d);}
void Utente::setSeg(string s){seguro->setSeg(s);}
string Utente::getMor() const {return morada;}
Convencao * Utente::getSeg() const {return seguro;}
Utente & Utente::operator=(Utente &u)
{
  if (this != &u)
  {
    nome = u.nome;
    tel = u.tel;
    morada = u.morada;
    seguro = u.seguro;
  }
  return *this;
}

ostream & operator<<(ostream & os, Medico &m)
{
  os << m.getCed()<<"|"<< m.getNome() << "|" << m.getTel() << "|" << m.getEspe() << "|"   << endl; 
 return os;
}

ostream & operator<<(ostream & os, Utente &u)
{
  os << u.getNome() << "|" << u.getTel() << "|" << u.getMor() << "|" << u.getSeg()->getSeg() << "|" << u.getSeg()->getDes() << endl; 
 return os;
}

ostream & operator<<(ostream & os, Pessoa & p)
{
  os << p.getNome() << "|" << p.getTel() << endl; 
 return os;
}
