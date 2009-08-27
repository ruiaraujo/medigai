#ifndef MEMORY_H
#define MEMORY_H
#include "FileHandling.h"
#include "horario.h"
#include <vector>

template<class Comparable> std::vector <Comparable *> find_Id( const std::vector<Comparable *> & );
template <class Comparable> void listar( const std::vector<Comparable *> & );
void listar( const std::vector<Consulta *> & );
bool isNum( std::string );
bool isDat( std::string );
bool isHor( std::string );
Hour getHour();
long getLong();

class Clinic{
  std::vector<Medico *> list_med;
  std::vector<Utente *> list_pac;
  std::vector<Specialty *> list_esp;
  std::vector<Consulta *> list_con;
  FileHandling files;
  public:
    Clinic( std::string = "" ,std::string = "" , std::string = "" , std::string = "" );
    std::vector<Medico *> getListMed() const;
    std::vector<Utente *> getListPac() const;
    std::vector<Specialty *> getListEsp() const;
    std::vector<Consulta *> getListCon() const;
    int insMed();
    int insPac();
    int insCon();
    void load();
    void save();
    bool verCon();
    bool delCon( std::vector<Consulta *> & , Medico * & , Hour & , Date & );
    bool delCon();
    bool altCon();
    bool altPac();
    bool delPac();
    bool delMed( unsigned long );
    bool pagarCon();
    float precoMedioP();
    float precoMedio();
    bool horario_med();
    bool horNCol ( std::vector<Consulta *> & , Hour & , const int & , const Hour & , const Hour & );
    std::vector<Medico *>  listEsp( Specialty * );
};


class EOI : public runtime_error{
  public:
    EOI(): runtime_error( "Detectado fim do input" ) {}
};
#endif
