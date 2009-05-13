#include "convencao.h"
#include <iostream>

using namespace std;

class Pessoa {
  protected:
    string nome;
    string tel;
    const unsigned long id;
  public:
    Pessoa (string, string, unsigned long );
    Pessoa (const Pessoa &);
    void setNome(string);
    void setTel(string);
    string getNome() const;
    string getTel() const;
    unsigned long getId() const;
    Pessoa & operator=(Pessoa &);
};

ostream & operator<<(ostream &, Pessoa &);

class Medico : public Pessoa {
  string especialidade;
  unsigned int duracao;
  public:
    Medico (string, string, string ,unsigned int, unsigned long);
    Medico (const Medico &);
    string getEspe()const;
    unsigned int getDur()const;
    unsigned long getCed()const;
    void setEspe(string);
    void setDur(unsigned int);
    Medico & operator=(Medico &);
};

ostream & operator<<(ostream &, Medico &);

class Utente : public Pessoa {
  string morada;
  Convencao * seguro;
  static long UltimoNumero;
  public:
    Utente(string, string, string , Convencao *);
    Utente(string, string , string, string, float);
    Utente(const Utente &);
    void setMor(string);
    void setSeg(string, float);
    void setSeg(float);
    void setSeg(string);
    string getMor()const;
    Convencao * getSeg()const;
    Utente & operator=(Utente &u);
};
ostream & operator<<(ostream &, Utente &);
