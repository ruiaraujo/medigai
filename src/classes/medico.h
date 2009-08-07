#ifndef MEDICO_H
#define MEDICO_H
#include <iostream>
#include "pessoa.h"
#include "hora.h"
#include "especialidade.h"

class Medico : public Pessoa {
  Especialidade * espe;
  unsigned int duracao;
  unsigned int dur_max;
  Hora inicio;
  Hora fim;
  public:
    Medico (Pessoa &, Especialidade *, unsigned int);
    Medico (Pessoa &, Especialidade *, Hora, Hora, unsigned int);
    Medico (string, string, unsigned int, unsigned long);
    Medico (const Medico &);
    ~Medico() {}
    Especialidade * getEspe() const;
    Hora getIni() const;
    Hora getFim() const;
    unsigned int getDur()const;
    unsigned int getDurM()const;
    unsigned long getCed()const;
    void setIni( const Hora &);
    void setFim( const Hora &);
    void setEspe(Especialidade *);
    void setDurM(unsigned int);
    void setDur(unsigned int);
    Medico & operator=(Medico &);
    friend ostream & operator<<(ostream &, Medico &);
};

#endif

