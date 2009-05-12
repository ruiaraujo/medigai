#include "headers/pessoas.h"

Pessoa::Pessoa (string n, string t) : nome(n), tel(t) {}
Pessoa::Pessoa (Pessoa & p) : nome(p.nome), tel(p.tel) {}
Pessoa::~Pessoa(){}
void Pessoa::setNome(string n){nome=n;}
void Pessoa::setTel(string t){tel=t;}
string Pessoa::getNome() const {return nome;}
string Pessoa::getTel() const{return tel;}
Pessoa & Pessoa::operator=(Pessoa &p)
{
  if (this != &p)
  {
    nome = p.nome;
    tel= p.tel;
  }
  return *this; 
}

vector<string> Medico:: lista_med;
Medico::Medico (string n, string t="", string e="", unsigned int d=0, unsigned int c=0): Pessoa(n,t), especialidade(e), duracao(d), cedula(c) {}
Medico::Medico (Medico &m): Pessoa(m.nome,m.tel), especialidade(m.especialidade), duracao(m.duracao), cedula(m.cedula) {}
Medico::~Medico ()
{
  vector<string>::iterator it=lista_med.begin();
  for (int i=0;i<(int)lista_med.size();it++,i++)
    if (getNome() == lista_med.at(i))
      lista_med.erase(it);
}
Medico & Medico::operator=(Medico &m)
{
  if (this != &m)
  {
    nome = m.nome;
    tel= m.tel;
    especialidade = m.especialidade;
    cedula = m.cedula;
  }
  return *this;
}
void Medico::setCed(unsigned int c){cedula = c;}
void Medico::setDur(unsigned int d){duracao = d;}
void Medico::setEspe(string e){especialidade = e;}
string Medico::getEspe() const{return especialidade;}
unsigned int Medico::getCed() const {return cedula;}
unsigned int Medico::getDur() const {return duracao;}

Utente::Utente (Utente &u): Pessoa (u.nome,u.tel), morada(u.morada), seguro(u.seguro) {}
Utente::Utente(string n, string t, string m, Convencao * p): Pessoa(n,t), morada(m), seguro(p) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0): Pessoa(n,t), morada(m)
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
  os << m.getNome() << "|" << m.getTel() << "|" << m.getEspe() << "|"  << endl; 
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
