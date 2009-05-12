#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class Convencao{
   string seguro;
   float desconto;
   public:
      Convencao(); 
     Convencao(string, float);
     Convencao (Convencao &);
     void setSeg(string);
     void setDes(float);
     string getSeg();
     float getDes();
     Convencao & operator=(Convencao &);
     bool operator<(Convencao &);
     bool operator>(Convencao &);
};

ostream & operator<<(ostream &, Convencao &);
