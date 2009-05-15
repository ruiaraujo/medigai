#ifndef MEDICO_H
#define MEDICO_H

#include "pessoa.h"
#include "especialidade.h"

class Medico : public Pessoa {
  Especialidade * espe;
  unsigned int duracao;
  Hora inicio;
  Hora fim;
  public:
    Medico (Pessoa &, Especialidade *, unsigned int);
    Medico (Pessoa &, Especialidade *, Hora, Hora, unsigned int);
    Medico (string, string, unsigned int, unsigned long);
    Medico (const Medico &);
    Especialidade * getEspe() const;
    Hora getIni() const;
    Hora getFim() const;
    unsigned int getDur()const;
    unsigned long getCed()const;
    void setIni(Hora &);
    void setFim(Hora &);
    void setEspe(Especialidade *);
    void setDur(unsigned int);
    Medico & operator=(Medico &);
    friend ostream & operator<<(ostream &, Medico &);
};

