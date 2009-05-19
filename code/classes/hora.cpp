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
Hora::Hora(const Hora &h) : hora(h.hora), min(h.min) {}
Hora::Hora(): hora(0), min(0) {}
void Hora::setHor(unsigned int h){if (h<24) hora = h;else throw HoraImpossivel();}
void Hora::setMin(unsigned int m){if (m<60) min = m;else throw MinImpossivel();}
void Hora::setHora(const Hora &h){setHora(h.hora,h.min);}
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
unsigned int Hora::getHor()const {return hora;}
unsigned int Hora::getMin()const {return min;}
Hora & Hora::getHora() {return *this;}
Hora operator+( const Hora & h , int extra)
{
  Hora a(h);
  if (extra!=0)
  {
    a.min += extra%60;
    extra -= extra%60;
    if  (a.min >59)
    {
      a.hora += a.min/60;
      a.min = a.min%60;
    }
    a.hora += extra/60;
    if (a.hora>23)
      a.hora = a.hora%24;
  }
  return a;
}
int Hora::operator-(Hora &h){return ((int)hora-(int)h.hora)*60 + ((int)min-(int)h.min);}// diferença em minutos entre duas datas (se negativo hora )
bool Hora::operator<( const Hora & h )
{
 if (h.hora == hora )
 {
  if (min < h.min)
    return true;
  else
    return false;
 }
 else
   if (hora < h.hora) return true;
   else return false;
}
bool Hora::operator<=( const Hora &h)
{
 if ( h.hora == hora && h.min == min ) return true; 
 if (h.hora == hora )
 {
  if (min < h.min)
    return true;
  else
    return false;
 }
 else
   if (hora < h.hora) return true;
   else return false;
}
bool Hora::operator>( const Hora &h)
{
 if (h.hora == hora )
 {
  if (min < h.min)
    return false;
  else
    return true;
 }
 else
   if (hora < h.hora) return false;
   else return true;
}
bool Hora::operator>=( const Hora &h )
{
 if ( h.hora == hora && h.min == min ) return true; 
 if (h.hora == hora )
 {
  if (min < h.min)
    return false;
  else
    return true;
 }
 else
   if (hora < h.hora) return false;
   else return true;
}
Hora & Hora::operator=( const Hora & h )
{
  if (this != &h)
  {
    hora = h.hora;
    min = h.min;
  }
  return *this;
}
bool Hora::operator==( const Hora &h){return (hora==h.hora && min==h.min );}

ostream & operator << (ostream & os, Hora & h)
{
  os << h.hora << ":" << h.min;
  return os;
}
