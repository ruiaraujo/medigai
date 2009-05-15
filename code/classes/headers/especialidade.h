#ifndef ESPE_H
#define ESPE_H


#include <iostream>

using namespace std;

class Especialidade {
  string nome;
  public:
  Especialidade() {};
  Especialidade (string);
  Especialidade (Especialidade &);
  void setNom(string);
  string getNom() const;
};

#endif
