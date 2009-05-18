#include "consulta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool criaFile(string);
bool addMed(fstream &,const Medico &);
bool delMed(fstream &, const Medico &);
bool delMed(fstream &, unsigned long);
bool addPac(fstream &, const Utente &);
bool delPac(fstream &, const Utente &);
bool delPac(fstream &, unsigned long);
bool addCon(fstream &, const Consulta &);
bool delCon(fstream &, const Consulta &);
bool savPac ( string , const vector<Utente *> & );
bool savEsp ( string , const vector<Especialidade *> & );
bool savMed ( string , const vector<Medico *> & );
