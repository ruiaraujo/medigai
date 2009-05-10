#include "headers/hora.h"

Hora::Hora(unsigned int h,unsigned  int m) {
  try
  {
    setHor(h);
    setMin(m);
  }
  catch(HoraImpossivel & horaImpossivel)
  {
    setHora(0,0);
    cout << "Ocorreu um erro: Hora Impossível. Hora alterada para omissão: 0:0" << endl;  
  }
  catch(MinImpossivel & moraImpossivel)
  {
    setHora(0,0);
    cout << "Ocorreu um erro: Hora Impossível. Hora alterada para omissão: 0:0" << endl;  
  }
}
Hora::Hora(Hora &h) : hora(h.hora), min(h.min) {}
Hora::Hora(): hora(0), min(0) {}
void Hora::setHor(unsigned int h){if (h<24) hora = h;else throw HoraImpossivel();}
void Hora::setMin(unsigned int m){if (m<60) min = m;else throw MinImpossivel();}
void Hora::setHora(unsigned int h, unsigned int m)
{
  try
  {
    setHor(h);
    setMin(m);
  }
  catch(HoraImpossivel & horaImpossivel)
  {
    throw HoraImpossivel();  
  }
  catch(MinImpossivel & moraImpossivel)
  {
    throw HoraImpossivel();  
  }
}
unsigned int Hora::getHor(){return hora;}
unsigned int Hora::getMin(){return min;}
Hora & Hora::getHora(){return *this;}
Hora & Hora::operator+(int extra)
{
  if (extra!=0)
  {
    min += extra%60;
    extra -= extra%60;
    if  (min >59)
    {
      hora += min/60;
      min = min%60;
    }
    hora += extra/60;
    if (hora>23)
      hora = hora%24;
  }
  return *this;
}
int Hora::operator-(Hora &h){return ((int)hora-(int)h.hora)*60 + ((int)min-(int)h.min);}// diferença em minutos entre duas datas (se negativo hora )
Hora & Hora::operator=(Hora &h)
{
  if (this != &h)
  {
    hora = h.hora;
    min = h.min;
  }
  return *this;
}
bool Hora::operator==(Hora &h){return (hora==h.hora && min==h.min );}

ostream & operator << (ostream & os, Hora & h)
{
  os << h.hora << ":" << h.min;
  return os;
}
