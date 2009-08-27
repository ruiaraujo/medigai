#ifndef MEDICO_H
#define MEDICO_H
#include <iostream>
#include "person.h"
#include "hour.h"
#include "specialty.h"

class Medico : public Person {
  Specialty * specialty;
  unsigned int duracao;
  unsigned int dur_max;
  Hour inicio;
  Hour fim;
  public:
    Medico ( const Person &, Specialty *, unsigned int);
    Medico ( const Person &, Specialty *, Hour, Hour, unsigned int);
    Medico (std::string, std::string, unsigned int, unsigned long);
    Medico (const Medico &);
    Medico() {};
    ~Medico() {}
    Specialty * getEspe() const;
    Hour getIni() const;
    Hour getFim() const;
    unsigned int getDur()const;
    unsigned int getDurM()const;
    unsigned long getCed()const;
    void setIni( const Hour &);
    void setFim( const Hour &);
    void setEspe(Specialty *);
    void setDurM(unsigned int);
    void setDur(unsigned int);
    Medico * find ( unsigned long ,  const std::vector<Medico *> & );
    Medico * find ( const std::vector<Medico *> & );
    int findPos( unsigned long , const std::vector<Medico *> & );
    int findPos( const std::vector<Medico *> & );
    std::vector<Medico *>::iterator insOrd ( std::vector<Medico *> & );
    Medico & operator=( const Medico & );
    friend std::ostream & operator<<(std::ostream &, Medico &);
};

#endif

