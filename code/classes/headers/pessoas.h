#include "convencao.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

class Pessoa {
  protected:
    string nome;
    string tel; 
  public:
    Pessoa (string, string);
    Pessoa (Pessoa &);
    virtual ~Pessoa();
    void setNome(string);
    void setTel(string);
    string getNome();
    string getTel();
    Pessoa & operator=(Pessoa &);
};

ostream & operator<<(ostream &, Pessoa &);

class Medico : public Pessoa {
  string especialidade;
  float custo;
  static vector<string> lista_med;
  public:
    Medico (string, string, string ,int);
    Medico (Medico &);
   ~Medico();
    string getEspe();
    float getCos();
    void setEspe(string);
    void setCos(float);
    Medico & operator=(Medico &);
};

ostream & operator<<(ostream &, Medico &);

class Utente : public Pessoa {
  string morada;
  Convencao seguro;
  public:
    Utente(string, string, string , Convencao );
    Utente(string, string , string, string, float);
    void setMor(string);
    void setSeg(string, float);
    void setSeg(float);
    void setSeg(string);
    string getMor();
    Convencao getSeg();
    Utente & operator=(Utente &u);
};
ostream & operator<<(ostream &, Utente &);
