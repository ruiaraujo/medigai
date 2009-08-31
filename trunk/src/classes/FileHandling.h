#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include "consulta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool addMed( std::fstream & ,const Doctor & );
bool delMed( std::fstream & , const Doctor & );
bool delMed( std::fstream & , unsigned long );
bool addPac( std::fstream & , const Patient & );
bool delPac( std::fstream & , const Patient & );
bool delPac( std::fstream & , unsigned long );

class FileHandling{
  std::string file_med;
  std::string file_pac;
  std::string file_esp;
  std::string file_con;
  public:
    FileHandling( std::string = "" ,std::string = "" , std::string = "" , std::string = "" );
    char existFile( std::string );
    bool loadEsp( std::vector<Specialty *> & );
    bool loadPac( std::vector<Patient *> & );
    bool loadMed( std::vector<Doctor * > & , std::vector<Specialty *> & );
    bool loadCon( std::vector<Consulta * > & , std::vector<Patient *> & , std::vector<Doctor * > & );
    void savPac ( const std::vector<Patient *> & );
    void savEsp ( const std::vector<Specialty *> & );
    void savMed ( const std::vector<Doctor *> & );
    void savCon ( const std::vector<Consulta *> &);
};



#endif

