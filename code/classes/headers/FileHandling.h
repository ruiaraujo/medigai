#include "consulta.h"
#include <fstream>
#include <iostream>
#include <sstream>


bool addMed(fstream &,const Medico &);
bool delMed(fstream &, const Medico &);
bool delMed(fstream &, unsigned long);
bool addPac(fstream &, const Utente &);
bool delPac(fstream &, const Utente &);
bool delPac(fstream &, unsigned long);
bool addCon(fstream &, const Consulta &);
bool delCon(fstream &, const Consulta &);

