#include "headers/hora.h"

Hora::Hora(unsigned int,unsigned  int){}
Hora::Hora(Hora &){}
Hora::Hora(){}
void Hora::setHor(unsigned int){}
void Hora::setMin(unsigned int){}
void Hora::setHora(unsigned int){}
unsigned int Hora::getHor(){}
unsigned int Hora::getMin(){}
Hora Hora::getHora(){}
unsigned int Hora::operator-(Hora &){}// diferença em minutos entre duas datas{}
Hora & Hora::operator=(Hora &){}
bool Hora::operator==(Hora &){}   
