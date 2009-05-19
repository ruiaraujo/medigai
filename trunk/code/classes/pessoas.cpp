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

Medico::Medico (Pessoa &p, Especialidade *e, Hora i, Hora f, unsigned int d=0) : Pessoa(p), espe(e), duracao(d), inicio(i), fim (f) {}
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
void Medico::setDurM(unsigned int d){dur_max = d;}
void Medico::setEspe(Especialidade *e){espe = e;}
Especialidade * Medico::getEspe() const{return espe;}
unsigned long Medico::getCed() const {return id;}
unsigned int Medico::getDur() const {return duracao;}
unsigned int Medico::getDurM() const {return dur_max;}
void Medico::setIni( const Hora & i ){inicio = i;}
void Medico::setFim( const Hora & f ){fim = f;}

unsigned long Utente::UltimoNumero = 1;
Utente::Utente (const Utente &u): Pessoa (u.nome,u.tel, u.id), morada(u.morada), seguro(u.seguro) {}
Utente::Utente(string n, string t, string m, Convencao p): Pessoa(n,t, UltimoNumero++), morada(m), seguro(p) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0): Pessoa(n,t, UltimoNumero++),morada(m),seguro(seg,d,a){}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0, unsigned long i=0): Pessoa(n,t, i),morada(m),seguro(seg,d,a){}
void Utente::setMor(string m ){morada = m;}
void Utente::setSeg(string s, float d){seguro.setSeg(s);seguro.setDes(d);}
void Utente::setSeg(float d){seguro.setDes(d);}
void Utente::setSeg(string s){seguro.setSeg(s);}
string Utente::getMor() const {return morada;}
Convencao Utente::getSeg() const {return seguro;}
bool Utente::getSis() const {return sistema;}
void Utente::setSis( bool e ) { sistema = e; }
void Utente::setUN(unsigned long u ) { UltimoNumero = u; }
long Utente::getUN() const { return UltimoNumero; }
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
  os << m.id <<"|"<< m.nome << "|" << m.tel << "|" << m.espe->getNom()<< "|"  << m.inicio << "|" << m.fim << "|" << m.duracao << "|" << m.dur_max; 
 return os;
}

ostream & operator<<(ostream & os, Utente &u)
{
  os << u.id << "|" << u.nome << "|" << u.tel << "|" << u.morada << "|" << u.seguro.getSeg() << "|" << u.seguro.getDes() << "|" << u.seguro.getApo()<<"|"<<u.sistema; 
 return os;
}

ostream & operator<<(ostream & os, Pessoa & p)
{
  os << p.id << "|" << p.nome << "|" << p.tel; 
 return os;
}
