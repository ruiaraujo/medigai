
#include "pessoa.h"
#include "convencao.h"



class Utente : public Pessoa {
  string morada;
  Convencao seguro;
  static long UltimoNumero;
  public:
    Utente(string, string, string , Convencao);
    Utente(string, string , string, string, float, unsigned long);
    Utente(const Utente &);
    void setMor(string);
    void setSeg(string, float);
    void setSeg(float);
    void setSeg(string);
    string getMor()const;
    Convencao getSeg()const;
    Utente & operator=(Utente &u);
    friend ostream & operator<<(ostream &, Utente &);
};

