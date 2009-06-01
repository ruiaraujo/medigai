#include "headers/data.h"

bool bissexto(unsigned int ano){return ((ano%4==0 && ano%100!=0)||ano%400==0);}
Data::Data() : dia(1) , mes(1) , ano(1970) {}
Data::Data (unsigned int d = 1,unsigned  int m = 1,unsigned int a = 1970): dia(1) , mes(1) , ano(1970)
{
  try
  {
    setData(d,m,a);
  }
  catch ( DataImpossivel & dImpossivel) 
  {
     dia=1; mes = 1; ano = 1970;
     cout << "Ocorreu um erro: Data Impossível. Data alterada para omissão: 1/1/1970" << endl;
  }
 }
Data::Data (const Data &d) : dia(d.dia), mes(d.mes), ano(d.ano) {} 
void Data::setData( const Data & d) { setData(d.dia, d.mes , d.ano);}
void Data::setDia(unsigned int d)
{
  if ( d == 0 ) throw DiaInesxistente();
  if (mes < 8)
  {
    if ((mes%2)!= 0 )
    {
      if (d <= 31){ dia=d;}
      else {throw DiaInesxistente();}
    }
      else
      {
        if (mes == 2)
        {
          if (bissexto(ano))
          {
            if (d <= 29) {dia=d;}
            else {throw DiaInesxistente();}
          }
          else
          {
            if (d <= 28)  {dia=d;}
            else {throw DiaInesxistente();}         
          }
        }
        else
        {
          if (d <= 30)  {dia=d;}
          else {throw DiaInesxistente();}     
        }
      }
  }
  else
  {
    if ((mes%2)!= 0 )
    {
      if (d <= 31)  {dia=d;}
      else {throw DiaInesxistente();}
    }
      else
      {
        if (d <= 30)  {dia=d;}
        else {throw DiaInesxistente();}  
      }
    }
}
void Data::setMes(unsigned int m)
{
  int tmp = mes;
  mes=m;
  try
  {
    setDia(dia);
  }
  catch(DiaInesxistente & diaInesxistente)
  {
    mes = tmp;
    throw MesImpossivel();
  }
}
void Data::setAno(unsigned int a)
{
  int tmp = ano;
  ano = a;
  try
  {
    setDia(dia);
  }
  catch(DiaInesxistente & diaInesxistente)
  {
    ano = tmp;
    throw AnoImpossivel();
  }
}
void Data::setData(unsigned int d, unsigned int m, unsigned int a)
{
  int tmp = dia, tmp2 = mes , tmp3 = ano;
  ano = a;
  mes = m;
  try
  {
    setDia(d);
  }
  catch(DiaInesxistente & diaInesxistente)
  {
    ano = tmp3;
    dia = tmp;
    mes = tmp2;
    throw DataImpossivel();
  }
}
void Data::imprimeData (ostream & os){os <<dia<<"/"<<mes<<"/"<<ano;}
Data & Data::getData(){return *this;}
unsigned int Data::getDia() const {return dia;}
unsigned int Data::getMes() const {return mes;}
unsigned int Data::getAno() const {return ano;}
bool Data::operator==( const Data & d ){return ( d.getDia()==dia && d.getMes() == mes && d.getAno() == ano);}
bool Data::operator<( const Data & d )
{
 if ( *this == d ) return false;
 if ( ano < d.ano )
   return true;
 else
   if ( ano > d.ano )
      return false;
   else
   {
      if ( mes < d.mes )
        return true;
      else
        if ( mes > d.mes )
          return false;
        else
          if (dia < d.dia )
            return true;
          else
            return false;
   }
}
bool Data::operator>( const Data & d )
{
 if ( *this == d ) return false;
 if ( ano < d.ano )
   return false;
 else
   if ( ano > d.ano )
      return true;
   else
   {
      if ( mes < d.mes )
        return false;
      else
        if ( mes > d.mes )
          return true;
        else
          if (dia < d.dia )
            return false;
          else
            return true;
    }
}
bool Data::operator<=( const Data & d )
{
 if ( *this == d ) return true;
 if ( ano < d.ano )
   return true;
 else
   if ( ano > d.ano )
      return false;
   else
   {
      if ( mes < d.mes )
        return true;
      else
        if ( mes > d.mes )
          return false;
        else
          if (dia < d.dia )
            return true;
          else
            return false;
    }
}
bool Data::operator>=( const Data & d )
{
 if ( *this == d ) return true;
 if ( ano < d.ano )
   return false;
 else
   if ( ano > d.ano )
      return true;
   else
   {
      if ( mes < d.mes )
        return false;
      else
        if ( mes > d.mes )
          return true;
        else
          if (dia < d.dia )
            return false;
          else
            return true;
    }
}
Data & Data::operator=(Data &a)
{
  if (this!=&a)
  {
    dia=a.getDia();
    mes=a.getMes();
    ano=a.getAno();
  }
  return *this;
}
ostream & operator<<(ostream & os, Data &d)
{
  os << setfill('0') << setw(2) << d.dia << "/" << setfill('0') << setw(2) << d.mes;
  os << "/" << setfill('0') << setw(4)  << d.ano;
  return os;
}

