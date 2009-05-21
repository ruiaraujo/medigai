#include "FileHandling.h"
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
void listar ( const vector<Especialidade *> & v );
vector<Consulta *>::iterator insConOrd ( Consulta * , vector<Consulta *> & );
vector<Medico *>::iterator insMedOrd( Medico * , vector<Medico *> & );
vector<Utente *>::iterator insPacOrd ( Utente * , vector<Utente *> & );
bool isNum( string );
bool isDat( string );
bool isHor( string );
bool delMed( unsigned long , vector<Medico *> & );
long getLong();
