#include "headers/tempo.h"


Tempo::Tempo(){}
Tempo::Tempo(Tempo &t): data(t.data), hora(t.hora) {}
Tempo::Tempo(Data &d, Hora &h) : data(d),hora(h){}
Tempo::Tempo(unsigned int d, unsigned int m , unsigned int a, unsigned int h, unsigned int mn ){Data(d,m ,a);Hora(h,mn);}
//int Tempo::operator-(Tempo &){}
Tempo & Tempo::getTempo(){return *this;}
Data & Tempo::getData(){return data;}
Hora & Tempo::getHora(){return hora;}
void Tempo::setHora(unsigned int h, unsigned int m){hora.setHora(h,m);}
void Tempo::setHora(Hora &h){hora.setHora(h.getHor(),h.getMin());}
void Tempo::setData(unsigned int d,unsigned int m , unsigned int a){data.setData(d,m,a);}
void Tempo::setData(Data &d){data.setData(d.getDia(),d.getMes(),d.getAno());}
ostream & operator<<(ostream &os, Tempo &t){os << t.data << " , " << t.hora;return os;}
