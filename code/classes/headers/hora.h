#include <iostream>
#include "HoraExceptions.h"

using namespace std;

class Hora {
  unsigned int hora;
  unsigned int min;
  public:
    Hora(unsigned int,unsigned  int);
    Hora(Hora &);
    Hora();
    void setHor(unsigned int);
    void setMin(unsigned int);
    void setHora(unsigned int, unsigned int);
    unsigned int getHor();
    unsigned int getMin();
    Hora & getHora();
    Hora & operator+(int); 
    int operator-(Hora &);// diferença em minutos entre duas datas;
    Hora & operator=(Hora &);
    bool operator==(Hora &);
    friend ostream & operator<<(ostream & os, Hora &);
};


