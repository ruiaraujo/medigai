#ifndef HORARIO_H
#define HORARIO_H
#include "consulta.h" 
#include <vector>


using std::vector;
using std::cout;
using std::endl;

template <class Person, class Time>
class Horario{
  private:
  Person * person;
  Time time;
  bool type; // 0 para médico, 1 para utente
  public:
    Horario( Person * , const Time &	, bool );
    void print( ostream & , const vector<Consulta *> & );
    void printMrc( ostream & , const vector<Consulta *> & );
    void printFrc( ostream & , const vector<Consulta *> & );
    vector<Consulta *> get( const vector<Consulta *> & );  
};


template <class Person, class Time > Horario<Person, Time>::Horario ( Person * p , const Time & t , bool s) : person(p) , time(t) , type(s) {}

template <class Person, class Time>
void Horario< Person , Time >::print(ostream & os, const vector<Consulta *> & c )
{
  if ( person != NULL )
  {
    cout << endl << endl << "Lista de Consulta do ";
    if (type)  cout << "Sr.(a)" << person->getNome() << ":\n";
    else  cout << "Dr.(a)" << person->getNome() << " no dia " << time << endl;
    if ( type )
    {
      for ( int i = 0 ; i < (int) c.size(); i++ )
        if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
        {
          Hora h( c.at( i )->getHor() );
          os << h << " , com o Dr.(a) " << c.at(i)->getMed()->getNome();
          os << ", consulta de " << c.at(i)->getMed()->getEspe()->getNom()<< endl;
        }
    }
    else
    {
      vector<Consulta *> horario = get( c );
      if ( !horario.empty() )
      {
        if ( !(horario.at(0)->getHor() == person->getIni()) )
        {
          Hora h( person->getIni() ), h0 = horario.at(0)->getHor();
          if ( ( h - h0 ) < (int) person->getDur() && ( h - h0) != 0 )
            os << "| " << h << " - " << h0 << " | " << "Intervalo" << endl;
          else
            if ( ( h - h0) != 0 )
              os << "| " << h << " - " << h0 << " | " << "Livre" << endl;
          Hora ho =  horario.at(0)->getHor() + horario.at( 0 )->getDur();
          os << "| " << h0 << " - " << ho << " | " << horario.at( 0 )->getUte()->getNome() << endl;
          for ( int i = 1 ;  i < (int) horario.size() ; i++ )
          {
            Hora h1 = horario.at( i )->getHor() , h2 = horario.at( i - 1 )->getHor() + horario.at( i - 1 )->getDur();
            if ( (h1 - h2) < (int) person->getDur() && ( h1 - h2 ) != 0 )
              os << "| " << h2 << " - " << h1 << " | " << "Intervalo" << endl;
            else
              if ( ( h1 - h2 ) != 0 )
                os << "| " << h2 << " - " << h1 << " | " << "Livre" << endl;
            Hora h11 = h1 + horario.at( i )->getDur();
            os << "| " << h1 << " - " << h11 << " | ";
            os << horario.at( i )->getUte()->getNome() << endl;
          }
          if ( !(( horario.at( horario.size() - 1 )->getHor()  + horario.at(0)->getDur() ) == person->getFim()) )
          {
            Hora h4 = person->getFim();
            Hora h3 = horario.at( horario.size() - 1 )->getHor() + horario.at( horario.size() - 1 )->getDur();
            if ( ( h4 - h3) < (int) person->getDur() && ( h4 - h3) != 0 )
              os << "| " << h3 << " - " << h4 << " | " << "Intervalo" << endl;
            else
              if ( ( h4 - h3) != 0 )
                os << "| " << h3 << " - " << h4 << " | " << "Livre" << endl;
          }
        }
        else
        {
          Hora h( person->getIni() ), h0 = h + horario.at(0)->getDur();
          os << "| " << h << " - " << h0 << " | " << horario.at( 0 )->getUte()->getNome() << endl;
          for ( int i = 1 ;  i < (int) horario.size() ; i++ )
          {
            Hora h1 = horario.at( i )->getHor() , h2 = horario.at( i - 1 )->getHor() + horario.at( i - 1 )->getDur();
            if ( h1  - h2 < (int) person->getDur() && ( h1 - h2 ) != 0 )
              os << "| " << h2 << " - " << h1 << " | " << "Intervalo" << endl;
            else
              if ( ( h1 - h2) != 0 )
                os << "| " << h2 << " - " << h1 << " | " << "Livre" << endl;
             Hora h11 = h1 + horario.at( i )->getDur();
            os << "| " << h1 << " - " << h11 << " | ";
            os << horario.at( i )->getUte()->getNome() << endl;
          }
          if ( !(( horario.at( horario.size() - 1 )->getHor()  + horario.at(horario.size() - 1 )->getDur() ) == person->getFim()) )
          {
            Hora h4 = person->getFim();
            Hora h3 = (horario.at( horario.size() - 1 )->getHor() + horario.at( horario.size() - 1 )->getDur());
            if ( (h4 - h3) <  (int) person->getDur() && ( h4 - h3) != 0 )
              os << "| " << h3 << " - " << h4 << " | " << "Intervalo" << endl;
            else
              if ( ( h4 - h3) != 0 )
                os << "| " << h3 << " - " << h4 << " | " << "Livre" << endl;
          }
        }
      }
      else os << "Não há consultas marcadas para o dia " << time << "." << endl;
    }
  } 
}

template <class Person, class Time>
void Horario< Person , Time >::printMrc(ostream & os, const vector<Consulta *> & c)
{
  if ( person != NULL )
  {
    cout << "Lista de Consulta do ";
    if (type)  cout << "Sr.(a)" << person->getNome() << ":\n";
    else  cout << "Dr.(a)" << person->getNome() << " no dia " << time << endl;
    if ( type )
    {
      for ( int i = 0 ; i < (int) c.size(); i++ )
        if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
        {
          if ( c.at( i )->getEst() == 'm' )
          {
          Hora h( c.at( i )->getHor() );
            os << h << " , com o Dr.(a) " << c.at(i)->getMed()->getNome();
            os << " de " << c.at(i)->getMed()->getEspe()->getNom()<< endl;
          }
        }
    }
    else
    {
    for ( int i = 0 ; i < (int) c.size(); i++ )
        if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
        {
          if ( c.at( i )->getEst() == 'm' )
          {
            Hora h( c.at( i )->getHor() );
            os << h << " , com o Sr.(a) " << c.at(i)->getUte()->getNome() << endl;
          }
        }
    }
  }
} 

template <class Person, class Time>
void Horario< Person , Time >::printFrc(ostream & , const vector<Consulta *> & c)
{
  if ( person != NULL )
  {
    cout << "Horário Actual do ";
    if (type)  cout << "Sr.(a)" << person->getNome() << ":\n";
    else  cout << "Dr.(a) " << person->getNome() << " no dia " << time << endl;
    if ( type )
    {
      for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
        {
          if ( c.at( i )->getEst() == 'f' )
          {
            Hora h( c.at( i )->getHor() );
            cout << h << " , com o Dr.(a) " << c.at(i)->getMed()->getNome();
            cout << " de " << c.at(i)->getMed()->getEspe()->getNom()<< endl;
          }
        }
    }
    else
    {
      for ( int i = 0 ; i < (int) c.size(); i++ )
        if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
        {
          if ( c.at( i )->getEst() == 'f' )
          {
            Hora h( c.at( i )->getHor() );
            cout << h << " , com o Sr.(a) " << c.at(i)->getUte()->getNome() << endl;
          }
        }
    }
  }
}
 
template <class Person, class Time>
vector<Consulta *> Horario< Person , Time >::get( const vector<Consulta *> & c)
{


  vector<Consulta *> lista;
  if ( person != NULL )
  {
    if ( type )
    {
      for ( int i = 0 ; i < (int) c.size(); i++ )
        if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
        {
          lista.push_back( c.at( i ) );
        }
    }
    else
    {
      for ( int i = 0 ; i < (int) c.size(); i++ )
        if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
        {
          lista.push_back( c.at( i ) );
        }
    }
  }
  return lista;
} 
#endif
