#include "headers/horario.h"


template <class Person, class Time > Horario<Person, Time>::Horario ( const Person * p , const Time & t ) : person(p) , time(t) {}

template <class Person, class Time>
void Horario< Person , Time >::print(ostream & , const vector<Consulta *> & , Time & ) {}

template <class Person, class Time>
void Horario< Person , Time >::print(ostream & , const vector<Consulta *> &) {}

template <class Person, class Time>
void Horario< Person , Time >::printMrc(ostream & , const vector<Consulta *> & , Time & ) {}

template <class Person, class Time>
void Horario< Person , Time >::printMrc(ostream & , const vector<Consulta *> &) {}

template <class Person, class Time>
void Horario< Person , Time >::printFrc(ostream & , const vector<Consulta *> & , Time & ) {}

template <class Person, class Time>
void Horario< Person , Time >::printFrc(ostream & , const vector<Consulta *> &) {}

template <class Person, class Time>
vector<Consulta *> Horario< Person , Time >::get( const vector<Consulta *> & ){} 

