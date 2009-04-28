#include "headers/medico.h"

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

ostream & operator<<(ostream & os, Medico &m)
{
  os << m.getNome() << "|" << m.getTel() << "|" << m.getEspe() << "|" << m.getCos() << endl; 
 return os;
}
