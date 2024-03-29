#ifndef CONSULTA_H
#define CONSULTA_H
#include "medico.h"
#include "patient.h"
#include "date.h"
#include "hour.h"
#include <iostream>

class Consulta {
  Doctor * med;
  Patient * pac;
  Date data;
  Hour hora;
  unsigned int duracao;
  float preco;
  char estado;
  public:
    Consulta( const Consulta & );
    Consulta( Doctor * , Patient * , const Date  & , const Hour & , float );
    Doctor * getMed() const;
    Patient * getUte() const;
    Date getDat() const;
    Hour getHor() const;
    unsigned int getDur() const;
    char getEst() const;
    float getPre() const;
    void setEst( char );
    void setDur( unsigned int );
    void setHor( unsigned int , unsigned int );
    void setHor( const Hour & );
    void setDat( unsigned int , unsigned int , unsigned int );
    void setDat( const Date &);
    void setMed( Doctor * );
    void setUte( Patient * ); 
    void setPre( float );
    std::vector<Consulta *>::iterator insOrd ( std::vector<Consulta *> & );
    std::vector<Consulta *>::iterator find ( std::vector<Consulta *> & );
    int findPos ( const std::vector<Consulta *> & ) const;
    friend std::ostream & operator<<( std::ostream & , Consulta &);
    
};

#endif
