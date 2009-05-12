#include "headers/convencao.h"

Convencao::Convencao(string s, float d): seguro(s),desconto(d) {}
Convencao::Convencao() : seguro(""), desconto(0) {}
Convencao::Convencao (Convencao & s ) : seguro(s.seguro), desconto(s.desconto) {}
void Convencao::setSeg(string s){seguro = s;}
void Convencao::setDes(float d){desconto = d;}
string Convencao::getSeg(){return seguro;}
float Convencao::getDes(){return desconto;}
Convencao & Convencao::operator=(Convencao & s)
{
  seguro = s.seguro;
  desconto = s.desconto;
  return *this;
}
bool Convencao::operator<(Convencao &s){return desconto<s.desconto?true:false;}
bool Convencao::operator>(Convencao &s){return desconto>s.desconto?true:false;}

ostream & operator<<(ostream & os, Convencao &c)
{
  os << c.getSeg() << "|" << c.getDes();
  return os;
}
