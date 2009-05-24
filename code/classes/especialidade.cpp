#include "headers/especialidade.h"

Especialidade::Especialidade() : nome("") {}
Especialidade::Especialidade ( const string e ): nome(e) {}
Especialidade::Especialidade ( const Especialidade & e ) : nome(e.nome) {}
void Especialidade::setNom(string e) {nome = e;}
string Especialidade::getNom() const {return nome;}
bool Especialidade::operator==( const Especialidade & e){ return e.nome == nome; }
bool Especialidade::operator!=( const Especialidade & e){ return !(e.nome == nome); }
Especialidade & Especialidade::operator=( const Especialidade & e)
{
  if ( this != &e )
    nome = e.nome;
  return *this;
}
