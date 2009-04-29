#include "pessoas.h"
#include "tempo.h"
#include <iostream>

class Consulta {
  Medico med;
  Utente pac;
  Tempo duracao;
  float preco;
  public:
    Consulta(Consulta &);
    Consulta(Medico &, Utente &, Tempo &);
    
};
