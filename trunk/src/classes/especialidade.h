#ifndef ESPE_H
#define ESPE_H
#include <iostream>
#include <vector>

class Especialidade {
  std::string nome;
  public:
  Especialidade();
  Especialidade ( const std::string & );
  Especialidade ( const Especialidade & );
  void setNom( std::string );
  std::string getNom() const;
  bool operator==( const Especialidade & );
  bool operator!=( const Especialidade & );
  Especialidade * find ( const std::vector<Especialidade *> & );
  Especialidade & operator= ( const Especialidade & );
};

#endif
