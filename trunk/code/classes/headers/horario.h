#ifndef HORARIO_H
#define HORARIO_H
#include "MemoryHandling.h" 

using namespace std;

template <class Person, class Time>
class Horario{
  private:
  Person * person;
  Time time;
  bool type; // 0 para médico, 1 para utente
  public:
    Horario( Person * , const Time &	, bool );
    void print( ostream & , const vector<Consulta *> & );
    void print( ostream & , const vector<Consulta *> & , Time & );
    void printMrc( ostream & , const vector<Consulta *> & );
    void printMrc( ostream & , const vector<Consulta *> & , Time & );
    void printFrc( ostream & , const vector<Consulta *> & );
    void printFrc( ostream & , const vector<Consulta *> & , Time &);
    vector<Consulta *> get( const vector<Consulta *> & );  
};


template <class Person, class Time > Horario<Person, Time>::Horario ( Person * p , const Time & t , bool s) : person(p) , time(t) , type(s) {}

template <class Person, class Time>
void Horario< Person , Time >::print(ostream & os, const vector<Consulta *> & c , Time & ) 
{


}

template <class Person, class Time>
void Horario< Person , Time >::print(ostream & os, const vector<Consulta *> & c )
{
  cout << "Lista de Consulta do ";
  if (type)  cout << "Sr.(a)" << person->getNome() << ":\n";
  else  cout << "Dr.(a)" << person->getNome() << " no dia " << time << endl;
  if ( type )
  {
    for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getUte()->getId() && time == c.at( i )->getDat() )
      {
        Hora h( c.at( i )->getHor() );
        cout << h << " , com o Dr.(a) " << c.at(i)->getMed()->getNome();
        cout << " de " << c.at(i)->getMed()->getEspe()->getNom()<< endl;
      }
  }
  else
  {
    for ( int i = 0 ; i < (int) c.size(); i++ )
      if ( person->getId() == c.at( i )->getMed()->getId() && time == c.at( i )->getDat() )
      {
        Hora h( c.at( i )->getHor() );
        cout << h << " , com o Sr.(a) " << c.at(i)->getUte()->getNome() << endl;
      }
  }
}

template <class Person, class Time>
void Horario< Person , Time >::printMrc(ostream & os, const vector<Consulta *> & c)
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


template <class Person, class Time>
void Horario< Person , Time >::printMrc(ostream & os, const vector<Consulta *> & , Time & t ){}

template <class Person, class Time>
void Horario< Person , Time >::printFrc(ostream & , const vector<Consulta *> & , Time & ) {}

template <class Person, class Time>
void Horario< Person , Time >::printFrc(ostream & , const vector<Consulta *> & c)
{
  cout << "Lista de Consulta do ";
  if (type)  cout << "Sr.(a)" << person->getNome() << ":\n";
  else  cout << "Dr.(a)" << person->getNome() << " no dia " << time << endl;
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

template <class Person, class Time>
vector<Consulta *> Horario< Person , Time >::get( const vector<Consulta *> & c)
{
  vector<Consulta *> lista;
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
  return lista;
} 

 

#endif


