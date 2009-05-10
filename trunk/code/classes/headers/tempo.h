#include <iostream>
#include "hora.h"
#include "data.h"

class Tempo{
  Data data;
  Hora hora;
  public:
    Tempo();
    Tempo(Tempo &);
    Tempo(Data &, Hora&);
    Tempo(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
    Tempo & getTempo();
    Data & getData();
    Hora & getHora();
    void setHora(unsigned int,unsigned int);
    void setHora(Hora &);
    void setData(unsigned int,unsigned int, unsigned int);
    void setData(Data &);
    friend ostream & operator<<(ostream &, Tempo &);
};


