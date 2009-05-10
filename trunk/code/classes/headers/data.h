#include <iostream>
#include "DataExceptions.h"

using namespace std;

class Data {
  unsigned int dia;
  unsigned int mes;
  unsigned int ano;
  public:
    Data();
    Data(Data &);
    Data(unsigned int,unsigned int,unsigned int);
    void setDia(unsigned int);
    void setMes(unsigned int);
    void setAno(unsigned int);
    void setData(unsigned int, unsigned int, unsigned int);
    void imprimeData (ostream & os);
    Data & getData();
    unsigned int getDia();
    unsigned int getMes();
    unsigned int getAno();
    int operator-(Data &); // diferença em dias entre duas datas;
    bool operator==(Data &);
    Data & operator+(int);
    Data & operator=(Data &);
    friend ostream & operator<<(ostream & os, Data &);
};

