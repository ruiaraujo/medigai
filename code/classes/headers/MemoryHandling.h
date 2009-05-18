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
void delCon( vector<Medico *> & , vector<Utente *> & , vector<Consulta *> & , Utente * , Medico * , Hora , Data );
bool carregaEsp( string , vector<Especialidade *> & );
bool carregaPac( string , vector<Utente *> & );
bool carregaMed( string , vector<Medico *> & , vector<Especialidade *> & );
template <class Comparable> Comparable * find ( unsigned long , vector<Comparable *> & );
//Medico * findMed( unsigned long , vector<Medico *> & );
bool delMed( const Medico & );
bool delMed( unsigned long );
template <class Comparable> Comparable * find ( const Comparable & , vector<Comparable *> & );
template <class Comparable> int findPos( unsigned long , vector<Comparable *> & );
template <class Comparable> int findPos( const Comparable & , vector<Comparable *> & );
template <class Comparable> void listar( const vector<Comparable *> & );
void listar ( const vector<Especialidade *> & v );
vector<Medico *>::iterator insMedOrd( Medico * , vector<Medico *> & );
vector<Utente *>::iterator insPacOrd ( Utente * , vector<Utente *> & );
bool isNum( string );
