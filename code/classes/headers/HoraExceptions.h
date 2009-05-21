#ifndef HORAEXCEP_H
#define HORAEXCEP_H


#include <stdexcept>
#include <exception>
using std::runtime_error;

class HoraImpossivel : public runtime_error{
  public:
    HoraImpossivel(): runtime_error( "Hora impossível" ) {}
};

class MinImpossivel : public runtime_error{
  public:
    MinImpossivel(): runtime_error( "Minuto impossível" ) {}
};

class EOI : public runtime_error{
  public:
    EOI(): runtime_error( "Detectado fim do input" ) {}
};

#endif

