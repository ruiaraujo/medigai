#ifndef UTENTE_H
#define UTENTE_H
#include <iostream>
#include "pessoa.h"
#include "convencao.h"

class Utente : public Pessoa {
  std::string morada;
  Convencao seguro;
  static unsigned long UltimoNumero;
  public:
    Utente(std::string, std::string, std::string , Convencao);
    Utente(std::string, std::string , std::string, std::string, float, unsigned long);
    Utente(std::string, std::string , std::string, std::string, float, unsigned long , unsigned long);
    Utente(const Utente &);
    ~Utente() {}
    void setMor(std::string);
    void setSeg(std::string, float);
    void setSeg(std::string, float , unsigned long);
    void setSeg(float);
    void setSeg(std::string);
    void setUN(unsigned long);
    long getUN() const ;
    std::string getMor()const;
    Convencao getSeg()const;
    Utente & operator=(Utente &u);
    friend std::ostream & operator<<(std::ostream &, Utente &);
};

#endif

