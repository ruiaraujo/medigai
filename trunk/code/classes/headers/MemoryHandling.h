#ifndef MEMORY_H
#define MEMORY_H
#include "FileHandling.h"
#include "horario.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;


Especialidade * findEsp ( string , vector<Especialidade *> & );
int insMed( vector<Medico *> &, vector<Especialidade *> & );
int insPac( vector<Utente *> & );
int insCon ( vector<Medico *> &, vector<Utente *> & , vector<Consulta *> &);
bool delCon( vector<Consulta *> & , Medico * & , Hora & , Data & );
bool delCon( vector<Medico *> & , vector<Consulta *> & );
bool altCon( vector<Consulta *> & , vector<Utente *> & , vector<Medico * > & );
bool carregaEsp( string , vector<Especialidade *> & );
bool carregaPac( string , vector<Utente *> & );
bool carregaMed( string , vector<Medico *> & , vector<Especialidade *> & );
bool carregaCon( string , vector<Medico *> & , vector<Utente *> & , vector<Consulta *> & );
template <class Comparable> Comparable * find ( unsigned long , vector<Comparable *> & );
bool delMed( const Medico & );
template <class Comparable> Comparable * find ( const Comparable & , vector<Comparable *> & );
template <class Comparable> int findPos( unsigned long , vector<Comparable *> & );
template <class Comparable> int findPos( const Comparable & , vector<Comparable *> & );
template <class Comparable> void listar( const vector<Comparable *> & );
int findPos ( Consulta * , vector<Consulta *> & );
void listar ( const vector<Especialidade *> & v );
vector<Consulta *>::iterator insConOrd ( Consulta * , vector<Consulta *> & );
vector<Medico *>::iterator insMedOrd( Medico * , vector<Medico *> & );
vector<Utente *>::iterator insPacOrd ( Utente * , vector<Utente *> & );
bool isNum( string );
bool isDat( string );
bool isHor( string );
bool delMed( unsigned long , vector<Medico *> & );
long getLong();
bool horNCol ( vector<Consulta *> & , Hora & , const int & , const Hora & , const Hora & );
Hora getHora();
unsigned long find_id_ut ( vector<Utente *> & u );
unsigned long find_id_med ( vector<Medico *> & v );
bool alt_Pac( vector<Utente *> & u );
bool delPac( vector<Utente *> & u );
bool ver_Con( vector<Consulta *> & c , vector<Medico * > & v );
#endif
