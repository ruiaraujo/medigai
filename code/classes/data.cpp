#include "headers/data.h"

bool bissexto(int ano)
{
  return ((ano%4==0 && ano%100!=0)||ano%400==0);
}

Data::Data (unsigned int d = 1,unsigned  int m = 1,unsigned int a = 1970) : dia(d), mes(m), ano(a) {}
Data::Data (Data &d) : dia(d.dia), mes(d.mes), ano(d.ano) {} 
void Data::setDia(unsigned int d)
{
  if (mes < 8)
  {
    if ((mes%2)!= 0 )
    {
      if (d > 0 && d <= 31)
        dia=d;
      else
      {
        if (mes == 2)
        {
          if (bissexto(ano))
          {
            if (d > 0 && d <= 29)
              dia=d;
          }
          else
            if (d > 0 && d <= 28)
              dia=d;            
        }
        else
        {
          if (d > 0 && d <= 31)
            dia=d;     
        }
      }
    }
  }
  else
  {
    if ((mes%2)!= 0 )
    {
      if (d > 0 && d <= 31)
        dia=d;
      else
      {
        if (d > 0 && d <= 30)
          dia=d;
      }
    }
  }
}
void Data::setMes(unsigned int m){mes=m;setDia(dia);}
void Data::setAno(unsigned int a){ano=a;}
void Data::setData(unsigned int, unsigned int, unsigned int){}
void Data::imprimeData (ostream & os){os <<dia<<"/"<<mes<<"/"<<ano;}
Data Data::getData(){Data d(dia,mes,ano);return d;}
unsigned int Data::getDia(){return dia;}
unsigned int Data::getMes(){return mes;}
unsigned int Data::getAno(){return ano;}
unsigned int Data::operator-(Data &d){return d.dia-dia;} // diferença em dias entre duas datas{}
bool Data::operator==(Data &d){return (d.getDia()==dia && d.getMes() == mes && d.getAno() == ano);}
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
