#include "horario.h"
#include <vector>


using std::vector;
using std::cerr;
using std::endl;
using std::ostream;

template<> vector<Consulta *> Horario< Patient , Date >::get( const vector<Consulta *> & );
template<> vector<Consulta *> Horario< Doctor , Date >::get( const vector<Consulta *> & );
template<> void Horario< Patient , Date >::print(ostream & , const vector<Consulta *> & );
template<> void Horario< Doctor , Date >::print(ostream & , const vector<Consulta *> & );
template<> void Horario< Patient , Date >::printFrc(ostream & , const vector<Consulta *> & );
template<> void Horario< Doctor , Date>::printMrc(ostream & os, const vector<Consulta *> & );
template<> void Horario< Patient , Date>::printMrc(ostream & os, const vector<Consulta *> & );

template <class Person, class Time > Horario<Person, Time>::Horario ( Person * p , const Time & t ) : person(p) , time(t) {}

template <class Person, class Time>
void Horario< Person , Time >::print(ostream & os, const vector<Consulta *> & c ){}
template<>
void Horario< Patient , Date >::print(ostream & os, const vector<Consulta *> & c )
{
  if ( person != NULL )
  {
    os << endl << endl << "Lista de Consulta do ";
    os << "Sr.(a)" << person->getName() << ":\n";
   

    for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
      {
        Hour h( c.at( i )->getHor() );
        os << h << " , com o Dr.(a) " << c.at(i)->getMed()->getName();
        os << ", consulta de " << c.at(i)->getMed()->getEspe()->getName()<< endl;
      }
  }
}
template<>
void Horario< Doctor , Date >::print(ostream & os, const vector<Consulta *> & c )
{
  if ( person != NULL )
  {
      os << endl << endl << "Lista de Consulta do ";
      os << "Dr.(a)" << person->getName() << " no dia " << time << endl;
      vector<Consulta *> horario = get( c );
      if ( !horario.empty() )
      {
        if ( !(horario.at(0)->getHor() == person->getIni()) )
        {
          Hour h( person->getIni() ), h0 = horario.at(0)->getHor();
          if ( ( h - h0 ) < (int) person->getDur() && ( h - h0) != 0 )
            os << "| " << h << " - " << h0 << " | " << "Intervalo" << endl;
          else
            if ( ( h - h0) != 0 )
              os << "| " << h << " - " << h0 << " | " << "Livre" << endl;
          Hour ho =  horario.at(0)->getHor() + horario.at( 0 )->getDur();
          os << "| " << h0 << " - " << ho << " | " << horario.at( 0 )->getUte()->getName() << endl;
          for ( int i = 1 ;  i < (int) horario.size() ; i++ )
          {
            Hour h1 = horario.at( i )->getHor() , h2 = horario.at( i - 1 )->getHor() + horario.at( i - 1 )->getDur();
            if ( (h1 - h2) < (int) person->getDur() && ( h1 - h2 ) != 0 )
              os << "| " << h2 << " - " << h1 << " | " << "Intervalo" << endl;
            else
              if ( ( h1 - h2 ) != 0 )
                os << "| " << h2 << " - " << h1 << " | " << "Livre" << endl;
            Hour h11 = h1 + horario.at( i )->getDur();
            os << "| " << h1 << " - " << h11 << " | ";
            os << horario.at( i )->getUte()->getName() << endl;
          }
          if ( !(( horario.at( horario.size() - 1 )->getHor()  + horario.at(0)->getDur() ) == person->getFim()) )
          {
            Hour h4 = person->getFim();
            Hour h3 = horario.at( horario.size() - 1 )->getHor() + horario.at( horario.size() - 1 )->getDur();
            if ( ( h4 - h3) < (int) person->getDur() && ( h4 - h3) != 0 )
              os << "| " << h3 << " - " << h4 << " | " << "Intervalo" << endl;
            else
              if ( ( h4 - h3) != 0 )
                os << "| " << h3 << " - " << h4 << " | " << "Livre" << endl;
          }
        }
        else
        {
          Hour h( person->getIni() ), h0 = h + horario.at(0)->getDur();
          os << "| " << h << " - " << h0 << " | " << horario.at( 0 )->getUte()->getName() << endl;
          for ( int i = 1 ;  i < (int) horario.size() ; i++ )
          {
            Hour h1 = horario.at( i )->getHor() , h2 = horario.at( i - 1 )->getHor() + horario.at( i - 1 )->getDur();
            if ( h1  - h2 < (int) person->getDur() && ( h1 - h2 ) != 0 )
              os << "| " << h2 << " - " << h1 << " | " << "Intervalo" << endl;
            else
              if ( ( h1 - h2) != 0 )
                os << "| " << h2 << " - " << h1 << " | " << "Livre" << endl;
             Hour h11 = h1 + horario.at( i )->getDur();
            os << "| " << h1 << " - " << h11 << " | ";
            os << horario.at( i )->getUte()->getName() << endl;
          }
          if ( !(( horario.at( horario.size() - 1 )->getHor()  + horario.at(horario.size() - 1 )->getDur() ) == person->getFim()) )
          {
            Hour h4 = person->getFim();
            Hour h3 = (horario.at( horario.size() - 1 )->getHor() + horario.at( horario.size() - 1 )->getDur());
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

template <class Person, class Time>
void Horario< Person , Time >::printMrc(ostream & os, const vector<Consulta *> & c){}

template <>
void Horario< Patient , Date>::printMrc(ostream & os, const vector<Consulta *> & c)
{
  if ( person != NULL )
  {
    os << "Lista de Consultas Marcadas do ";
    os << "Sr.(a)" << person->getName() << ":\n";
    for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
        if ( c.at( i )->getEst() == 'm' )
        {
          Hour h( c.at( i )->getHor() );
          os << h << " , com o Dr.(a) " << c.at(i)->getMed()->getName();
          os << " de " << c.at(i)->getMed()->getEspe()->getName()<< endl;
        }
  }
}

template <>
void Horario< Doctor , Date>::printMrc(ostream & os, const vector<Consulta *> & c)
{
  if ( person != NULL )
  {
    os << "Lista de Consulta Marcadas do ";
    os << "Dr.(a)" << person->getName() << " no dia " << time << endl;
    for ( int i = 0 ; i < (int) c.size(); i++ )
     if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
       if ( c.at( i )->getEst() == 'm' )
       {
         Hour h( c.at( i )->getHor() );
         os << h << " , com o Sr.(a) " << c.at(i)->getUte()->getName() << endl;
       }
  }
} 

template <class Person, class Time>
void Horario< Person , Time >::printFrc(ostream & os , const vector<Consulta *> & c){}

template <>
void Horario< Patient , Date >::printFrc(ostream & os , const vector<Consulta *> & c)
{
  if ( person != NULL )
  {
    os << "Consultas efectuadas do ";
    os << "Sr.(a)" << person->getName() << ":\n";
    for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
        if ( c.at( i )->getEst() == 'f'  || c.at( i )->getEst() == 'p')
        {
          Hour h( c.at( i )->getHor() );
          os << h << " , com o Dr.(a) " << c.at(i)->getMed()->getName();
          os << " de " << c.at(i)->getMed()->getEspe()->getName()<< endl;
        }
    
  }
}

template <>
void Horario< Doctor , Date >::printFrc(ostream & os , const vector<Consulta *> & c)
{
  if ( person != NULL )
  {
    os << "Consultas efectuadas do ";
    os << "Dr.(a) " << this->person->getName() << " no dia " << this->time << endl;
    for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
        if ( c.at( i )->getEst() == 'f' || c.at( i )->getEst() == 'p' )
        {
          Hour h( c.at( i )->getHor() );
          os << h << " , com o Sr.(a) " << c.at(i)->getUte()->getName() << endl;
        }
  }
}
 
template <class Person, class Time>
vector<Consulta *> Horario< Person , Time >::get( const vector<Consulta *> & c){}

template <>
vector<Consulta *> Horario< Doctor , Date >::get( const vector<Consulta *> & c)
{
  vector<Consulta *> lista;
  if ( person != NULL )
   for ( int i = 0 ; i < (int) c.size(); ++i )
     if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
       lista.push_back( c.at( i ) );
  return lista;
}

template <>
vector<Consulta *> Horario< Patient , Date >::get( const vector<Consulta *> & c)
{
  vector<Consulta *> lista;
  if ( person != NULL )
   for ( int i = 0 ; i < (int) c.size(); ++i )
     if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
       lista.push_back( c.at( i ) );
  return lista;
}



template class Horario<Doctor, Date>;
template class Horario<Patient, Date>;


