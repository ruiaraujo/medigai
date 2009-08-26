#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include "consulta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool addMed( std::fstream & ,const Medico & );
bool delMed( std::fstream & , const Medico & );
bool delMed( std::fstream & , unsigned long );
bool addPac( std::fstream & , const Utente & );
bool delPac( std::fstream & , const Utente & );
bool delPac( std::fstream & , unsigned long );

class FileHandling{
  std::string file_med;
  std::string file_pac;
  std::string file_esp;
  std::string file_con;
  public:
    FileHandling( std::string = "" ,std::string = "" , std::string = "" , std::string = "" );
    char existFile( std::string );
    bool loadEsp( std::vector<Especialidade *> & );
    bool loadPac( std::vector<Utente *> & );
    bool loadMed( std::vector<Medico * > & , std::vector<Especialidade *> & );
    bool loadCon( std::vector<Consulta * > & , std::vector<Utente *> & , std::vector<Medico * > & );
    void savPac ( const std::vector<Utente *> & );
    void savEsp ( const std::vector<Especialidade *> & );
    void savMed ( const std::vector<Medico *> & );
    void savCon ( const std::vector<Consulta *> &);
};



#endif

