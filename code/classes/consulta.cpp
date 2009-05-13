#include "headers/consulta.h"

Consulta::Consulta(const Consulta &c): pac(c.pac), med(c.med), data(c.data), hora(c.hora) , preco(c.preco) {}
Consulta::Consulta(Medico *m, Utente *u, Data d, Hora h, float p ) : pac(u), med(m), data(d), hora(h), preco(p) {}
Medico * Consulta::getMed() const{return med;}
Utente * Consulta::getUte() const{return pac;}
Data Consulta::getDat() const{return data;}
Hora Consulta::getHor() const{return hora;}
void Consulta::setHor(unsigned int h, unsigned int m){hora.setHora(h,m);}
void Consulta::setHor(const Hora &h){hora.setHora(h);}
void Consulta::setDat(unsigned int, unsigned int, unsigned int){}
void Consulta::setDat(Data &){}
