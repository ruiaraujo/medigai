#include "convencao.h"

Convencao::Convencao(string s, float d, unsigned long a): seguro(s),desconto(d), apolice (a) {}
Convencao::Convencao() : seguro(""), desconto(0), apolice (0) {}
Convencao::Convencao (const Convencao & s ) : seguro(s.seguro), desconto(s.desconto), apolice(s.apolice) {}
void Convencao::setSeg(string s){seguro = s;}
void Convencao::setDes(float d){desconto = d;}
void Convencao::setApo(unsigned long a) {apolice = a;}
unsigned long Convencao::getApo() const {return apolice;}
string Convencao::getSeg() const {return seguro;}
float Convencao::getDes() const {return desconto;}
Convencao & Convencao::operator=(Convencao & s)
{
  if (this != &s )
  {
   seguro = s.seguro;
   desconto = s.desconto;
    apolice = s.apolice;
  }
  return *this;
}
bool Convencao::operator<(Convencao &s){return desconto<s.desconto?true:false;}
bool Convencao::operator>(Convencao &s){return desconto>s.desconto?true:false;}

ostream & operator<<(ostream & os, Convencao &c)
{
  os << c.getSeg() << "|" << c.getDes() << "|" << c.getApo();
  return os;
}
