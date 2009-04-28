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
    
};
