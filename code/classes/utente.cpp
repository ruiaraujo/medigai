#include "headers/utente.h"

long Utente::UltimoNumero = 0;
Utente::Utente (const Utente &u): Pessoa (u.nome,u.tel, UltimoNumero++), morada(u.morada), seguro(u.seguro) {}
Utente::Utente(string n, string t, string m, Convencao p): Pessoa(n,t, UltimoNumero++), morada(m), seguro(p) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0, unsigned long a=0): Pessoa(n,t, UltimoNumero++),morada(m),seguro(seg,d,a){}
void Utente::setMor(string m ){morada = m;}
void Utente::setSeg(string s, float d){seguro.setSeg(s);seguro.setDes(d);}
void Utente::setSeg(float d){seguro.setDes(d);}
void Utente::setSeg(string s){seguro.setSeg(s);}
string Utente::getMor() const {return morada;}
Convencao Utente::getSeg() const {return seguro;}
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
  os << u.id << "|" << u.nome << "|" << u.tel << "|" << u.morada << "|" << u.seguro.getSeg() << "|" << u.seguro.getDes() << "|" << u.seguro.getApo() <<endl; 
 return os;
}
