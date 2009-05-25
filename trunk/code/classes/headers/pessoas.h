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

class Utente : public Pessoa {
  string morada;
  Convencao seguro;
  static unsigned long UltimoNumero;
  public:
    Utente(string, string, string , Convencao);
    Utente(string, string , string, string, float, unsigned long);
    Utente(string, string , string, string, float, unsigned long , unsigned long);
    Utente(const Utente &);
    ~Utente() {}
    void setMor(string);
    void setSeg(string, float);
    void setSeg(float);
    void setSeg(string);
    void setUN(unsigned long);
    long getUN() const ;
    string getMor()const;
    Convencao getSeg()const;
    Utente & operator=(Utente &u);
    friend ostream & operator<<(ostream &, Utente &);
};

#endif

