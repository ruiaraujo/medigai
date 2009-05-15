#ifndef CONVENCAO_H
#define CONVENCAO_H
#include <iostream>

using namespace std;

class Convencao{
   string seguro;
   float desconto;
   unsigned long apolice;
   public:
      Convencao(); 
     Convencao(string, float, unsigned long);
     Convencao (const Convencao &);
     void setSeg(string);
     void setDes(float);
     void setAPo(unsigned long);
     unsigned long getApo() const;
     string getSeg() const;
     float getDes() const;
     Convencao & operator=(Convencao &);
     bool operator<(Convencao &);
     bool operator>(Convencao &);
     friend ostream & operator<<(ostream &, Convencao &);
};



#endif
