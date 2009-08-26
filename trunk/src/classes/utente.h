#ifndef UTENTE_H
#define UTENTE_H
#include <iostream>
#include "person.h"
#include "convention.h"

class Utente : public Person {
  std::string morada;
  Convention insurance;
  static unsigned long UltimoNumero;
  public:
    Utente() {}
    Utente(std::string, std::string, std::string , Convention);
    Utente(std::string, std::string , std::string, std::string, float, unsigned long);
    Utente(std::string, std::string , std::string, std::string, float, unsigned long , unsigned long);
    Utente(const Utente &);
    ~Utente() {}
    void setMor(std::string);
    void setIns(std::string, float);
    void setIns(std::string, float , unsigned long);
    void setIns(float);
    void setIns(std::string);
    void setUN(unsigned long);
    long getUN() const ;
    std::string getMor()const;
    Convention getIns()const;
    Utente * find ( const std::vector<Utente *> & );
    Utente * find ( unsigned long , const std::vector<Utente *> & );
    int findPos( unsigned long , const std::vector<Utente *> & );
    int findPos( const std::vector<Utente *> & );
    std::vector<Utente *>::iterator insOrd ( std::vector<Utente *> & );
    Utente & operator=( const Utente &u);
    friend std::ostream & operator<<(std::ostream &, Utente &);
};

#endif

