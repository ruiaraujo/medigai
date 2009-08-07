#include "utente.h"

unsigned long Utente::UltimoNumero = 1;
Utente::Utente (const Utente &u): Pessoa (u.nome,u.tel, u.id), morada(u.morada), seguro(u.seguro) {}
Utente::Utente(string n, string t, string m, Convencao p): Pessoa(n,t, UltimoNumero++), morada(m), seguro(p) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0): Pessoa(n,t, UltimoNumero++),morada(m),seguro(seg,d,a){}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0, unsigned long i=0): Pessoa(n,t, i),morada(m),seguro(seg,d,a){}
void Utente::setMor(string m ){morada = m;}
void Utente::setSeg(string s, float d){seguro.setSeg(s);seguro.setDes(d);}
void Utente::setSeg(string s, float d , unsigned long a){seguro.setSeg(s);seguro.setDes(d);seguro.setApo(a);}
void Utente::setSeg(float d){seguro.setDes(d);}
void Utente::setSeg(string s){seguro.setSeg(s);}
string Utente::getMor() const {return morada;}
Convencao Utente::getSeg() const {return seguro;}
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



ostream & operator<<(ostream & os, Utente &u)
{
  os << u.id << "|" << u.nome << "|" << u.tel << "|" << u.morada << "|" << u.seguro.getSeg() << "|" << u.seguro.getDes() << "|" << u.seguro.getApo() << "|" << u.sistema; 
 return os;
}
