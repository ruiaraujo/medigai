#ifndef PESSOAS_H
#define PESSOAS_H
#include "convencao.h"
#include "especialidade.h"
#include "hora.h"
#include <iostream>

using namespace std;

class Pessoa {
  protected:
    string nome;
    string tel;
    bool sistema;
    const unsigned long id;
  public:
    Pessoa (string, string, unsigned long );
    Pessoa (const Pessoa &);
    void setNome(string);
    void setTel(string);
    virtual ~Pessoa() = 0;
    string getNome() const;
    string getTel() const;
    void setSis(bool);
    bool getSis() const;
    unsigned long getId() const;
    Pessoa & operator=(Pessoa &);
    friend ostream & operator<<(ostream &, Pessoa &);
};


#endif

