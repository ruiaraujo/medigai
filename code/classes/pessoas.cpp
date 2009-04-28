#include "headers/pessoas.h"

Pessoa::Pessoa (string n, string t) : nome(n), tel(t) {}
Pessoa::Pessoa (Pessoa & p) : nome(p.nome), tel(p.tel) {}
Pessoa::~Pessoa(){}
void Pessoa::setNome(string n){nome=n;}
void Pessoa::setTel(string t){tel=t;}
string Pessoa::getNome(){return nome;}
string Pessoa::getTel(){return tel;}
Pessoa & Pessoa::operator=(Pessoa &p)
{
nome = p.nome;
tel= p.tel;
return *this; 
}

vector<string> Medico:: lista_med;
Medico::Medico (string n, string t="", string e="", int c=0): Pessoa(n,t), especialidade(e),custo(c) {}
Medico::~Medico ()
{
  vector<string>::iterator it=lista_med.begin();
  for (int i=0;i<(int)lista_med.size();it++,i++)
    if (getNome() == lista_med.at(i))
      lista_med.erase(it);
}
Medico & Medico::operator=(Medico &m)
{
  nome = m.nome;
  tel= m.tel;
  especialidade = m.especialidade;
  custo = m.custo;
  return *this;
}
void Medico::setEspe(string e){especialidade = e;}
void Medico::setCos(float c){custo = c;}
string Medico::getEspe() {return especialidade;}
float Medico::getCos() {return custo;}


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

ostream & operator<<(ostream & os, Medico &m)
{
  os << m.getNome() << "|" << m.getTel() << "|" << m.getEspe() << "|" << m.getCos() << endl; 
 return os;
}

ostream & operator<<(ostream & os, Utente &u)
{
  os << u.getNome() << "|" << u.getTel() << "|" << u.getMor() << "|" << u.getSeg().getSeg() << "|" << u.getSeg().getDes() << endl; 
 return os;
}

ostream & operator<<(ostream & os, Pessoa & p)
{
  os << p.getNome() << "|" << p.getTel() << endl; 
 return os;
}
