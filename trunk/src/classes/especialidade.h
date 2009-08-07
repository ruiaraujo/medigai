#ifndef ESPE_H
#define ESPE_H


#include <iostream>

using namespace std;

class Especialidade {
  string nome;
  public:
  Especialidade();
  Especialidade ( const string);
  Especialidade ( const Especialidade &);
  void setNom(string);
  string getNom() const;
  bool operator==( const Especialidade & );
  bool operator!=( const Especialidade & );
  Especialidade & operator= ( const Especialidade & );
};

#endif
