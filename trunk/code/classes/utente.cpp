#include "headers/utente.h"


Utente::Utente(string n, string t, string m, Convencao p): Pessoa(n,t), morada(m), seguro(p.getSeg(),p.getDes()) {}
Utente::Utente(string n, string t, string m , string seg = "", float d= 0.0): Pessoa(n,t), morada(m), seguro(seg, d) {}
void Utente::setMor(string m ){morada = m;}
void Utente::setSeg(string s, float d){seguro.setSeg(s);seguro.setDes(d);}
void Utente::setSeg(float d){seguro.setDes(d);}
void Utente::setSeg(string s){seguro.setSeg(s);}
string Utente::getMor(){return morada;}
Convencao Utente::getSeg(){return seguro;}
Utente & Utente::operator=(Utente &u)
{
  nome = u.nome;
  tel = u.tel;
  morada = u.morada;
  seguro = u.seguro;
  return *this;
}


ostream & operator<<(ostream & os, Utente &u)
{
  os << u.getNome() << "|" << u.getTel() << "|" << u.getMor() << "|" << u.getSeg().getSeg() << "|" << u.getSeg().getDes() << endl; 
 return os;
}
