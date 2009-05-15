#include "convencao.h"
#include "especialidade.h"
#include "hora.h"
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
    friend ostream & operator<<(ostream &, Pessoa &);
};



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

