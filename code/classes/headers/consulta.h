#include "pessoas.h"
#include "data.h"
#include "hora.h"
#include <iostream>

class Consulta {
  Medico * med;
  Utente * pac;
  Data data;
  Hora hora;
  unsigned int duracao;
  float preco;
  char estado;
  public:
    Consulta( const Consulta & );
    Consulta( Medico * , Utente * , Data  & , Hora & , float );
    Medico * getMed() const;
    Utente * getUte() const;
    Data getDat() const;
    Hora getHor() const;
    unsigned int getDur() const;
    char getEst() const;
    void setEst( char );
    void setDur( unsigned int );
    void setHor( unsigned int , unsigned int );
    void setHor( const Hora & );
    void setDat( unsigned int , unsigned int , unsigned int );
    void setDat( const Data &);
};
