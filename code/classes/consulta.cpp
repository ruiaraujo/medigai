#include "headers/consulta.h"

Consulta::Consulta(const Consulta &){}
Consulta::Consulta(Medico *, Utente *, Data *, Hora *, float){}
Medico * Consulta::getMed() const{return med;}
Utente * Consulta::getUte() const{return pac;}
Data Consulta::getDat() const{return data;}
Hora Consulta::getHor() const{return inicio;}
void Consulta::setHor(unsigned int, unsigned int){}
void Consulta::setHor(Hora &){}
void Consulta::setDat(unsigned int, unsigned int, unsigned int){}
void Consulta::setDat(Data &){}
