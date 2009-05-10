#include <stdexcept>
#include <exception>
using std::runtime_error;

class DiaInesxistente : public runtime_error{
  public:
    DiaInesxistente(): runtime_error( "Dia inexistente" ) {}
};

class MesImpossivel : public runtime_error{
  public:
    MesImpossivel(): runtime_error( "Mês Impossível com o dia actual!" ) {}
};

class AnoImpossivel : public runtime_error{
  public:
    AnoImpossivel(): runtime_error( "Ano Impossível com o dia ou mês actual!" ) {}
};

class DataImpossivel : public runtime_error{
  public:
    DataImpossivel(): runtime_error( "Data Impossível!" ) {}
};
