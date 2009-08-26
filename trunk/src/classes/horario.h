#ifndef HORARIO_H
#define HORARIO_H
#include "consulta.h" 
#include <vector>



template <class Person, class Time>
class Horario{
  private:
  Person * person;
  Time time;
  bool type; // 0 para médico, 1 para utente
  public:
    Horario( Person * , const Time &	, bool );
    void print( std::ostream & , const std::vector<Consulta *> & );
    void printMrc( std::ostream & , const std::vector<Consulta *> & );
    void printFrc( std::ostream & , const std::vector<Consulta *> & );
    std::vector<Consulta *> get( const std::vector<Consulta *> & );  
};

#endif
