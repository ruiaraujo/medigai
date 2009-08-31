#ifndef MEDICO_H
#define MEDICO_H
#include <iostream>
#include "person.h"
#include "hour.h"
#include "specialty.h"

class Doctor : public Person {
  Specialty * specialty;
  unsigned int duracao;
  unsigned int dur_max;
  Hour inicio;
  Hour fim;
  public:
    Doctor ( const Person &, Specialty *, unsigned int);
    Doctor ( const Person &, Specialty *, Hour, Hour, unsigned int);
    Doctor (std::string, std::string, unsigned int, unsigned long);
    Doctor (const Doctor &);
    Doctor() {};
    ~Doctor() {}
    Specialty * getEspe() const;
    Hour getIni() const;
    Hour getFim() const;
    unsigned int getDur()const;
    unsigned int getDurM()const;
    void setIni( const Hour &);
    void setFim( const Hour &);
    void setEspe(Specialty *);
    void setDurM(unsigned int);
    void setDur(unsigned int);
    Doctor * find ( unsigned long ,  const std::vector<Doctor *> & );
    Doctor * find ( const std::vector<Doctor *> & );
    int findPos( unsigned long , const std::vector<Doctor *> & );
    int findPos( const std::vector<Doctor *> & );
    std::vector<Doctor *>::iterator insOrd ( std::vector<Doctor *> & );
    Doctor & operator=( const Doctor & );
    friend std::ostream & operator<<(std::ostream &, Doctor &);
};

#endif

