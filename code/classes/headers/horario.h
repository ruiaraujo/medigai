#include "MemoryHandling.h" 

template <class Person, class Time>
class Horario{
  private:
  Person * person;
  Time time;
  public:
    Horario(const Person * , const Time &	);
    void print( ostream & , const vector<Consulta *> & );
    void print( ostream & , const vector<Consulta *> & , Time & );
    void printMrc( ostream & , const vector<Consulta *> & );
    void printMrc( ostream & , const vector<Consulta *> & , Time & );
    void printFrc( ostream & , const vector<Consulta *> & );
    void printFrc( ostream & , const vector<Consulta *> & , Time &);
    vector<Consulta *> get( const vector<Consulta *> & );  
};
