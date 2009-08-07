#include "pessoa.h"


Pessoa::Pessoa (string n, string t, unsigned long i) : nome(n), tel(t), sistema(1) , id(i) {}
Pessoa::Pessoa (const Pessoa & p) : nome(p.nome), tel(p.tel), sistema(1) , id(p.id){}
void Pessoa::setNome(string n){nome=n;}
void Pessoa::setTel(string t){tel=t;}
string Pessoa::getNome() const {return nome;}
string Pessoa::getTel() const{return tel;}
unsigned long Pessoa::getId() const {return id;}
bool Pessoa::getSis() const {return sistema;}
void Pessoa::setSis( bool e ) { sistema = e; }
Pessoa::~Pessoa() {}
Pessoa & Pessoa::operator=(Pessoa &p)
{
  if (this != &p)
  {
    nome = p.nome;
    tel= p.tel;
  }
  return *this; 
}

ostream & operator<<(ostream & os, Pessoa & p)
{
  os << p.id << "|" << p.nome << "|" << p.tel << "|" << p.sistema; 
 return os;
}
