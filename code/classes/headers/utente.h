#include "pessoa.h"
#include "convencao.h"
#include <string>
#include <cstring>
#include <iostream>


class Utente : public Pessoa {
  string morada;
  Convencao seguro;
};
