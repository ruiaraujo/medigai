#include <iostream>
#include "DataExceptions.h"

using namespace std;

class Data {
  unsigned int dia;
  unsigned int mes;
  unsigned int ano;
  public:
    Data();
    Data(const Data &);
    Data(unsigned int,unsigned int,unsigned int);
    void setDia(unsigned int);
    void setMes(unsigned int);
    void setAno(unsigned int);
    void setData(unsigned int, unsigned int, unsigned int);
    void setData ( const Data & );
    void imprimeData (ostream & os);
    Data & getData();
    unsigned int getDia() const;
    unsigned int getMes() const;
    unsigned int getAno() const;
    int operator-(Data &); // diferença em dias entre duas datas;
    bool operator==( const Data & );
    bool operator<( const Data & );
    bool operator>( const Data & );
    bool operator<=( const Data & );
    bool operator>=( const Data & );
    Data & operator+(int);
    Data & operator=(Data &);
    friend ostream & operator<<(ostream & os, Data &);
};


