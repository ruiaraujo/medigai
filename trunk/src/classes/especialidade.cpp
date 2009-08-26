#include "especialidade.h"

using std::vector;
using std::string;

Especialidade::Especialidade() : nome("") {}
Especialidade::Especialidade ( const string & e ): nome(e) {}
Especialidade::Especialidade ( const Especialidade & e ) : nome(e.nome) {}
void Especialidade::setNom( string e ) { nome = e; }
string Especialidade::getNom() const {return nome;}
bool Especialidade::operator==( const Especialidade & e){ return e.nome == nome; }
bool Especialidade::operator!=( const Especialidade & e){ return !(e.nome == nome); }
Especialidade * Especialidade::find ( const vector<Especialidade *> & list_esp )
{
  for( int i = 0 ; i < (int) list_esp.size() ; i++ )
  {
    if ( this->nome == list_esp.at( i )->getNom() )
      return list_esp.at( i );
  }
  return NULL;
}
Especialidade & Especialidade::operator=( const Especialidade & e)
{
  if ( this != &e )
    nome = e.nome;
  return *this;
}

