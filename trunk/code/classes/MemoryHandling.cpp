#include "headers/MemoryHandling.h"

void delCon( vector<Medico *> & v, vector<Utente *> & u , vector<Consulta *> & c , Utente * pac ,
             Medico * med , Hora h , Data d )
{
  
}

int insPac ( vector<Utente *> & u)
{
  string nome, tel, seg, mor , tmp;
  float des;
  long apo;
  getline( cin, nome ); //limpar o cin;
  cout << "Insira o nome do utente: ";
  getline( cin , nome );
  cout << "Insira o telefone do utente: ";
  getline( cin , tel );
  while ( ! isNum( tel )  )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tel );
  } 
  cout << "Insira a morada: ";
  getline( cin , mor );
  cout << "Insira a seguradora: ";
  getline( cin , seg );
  cout << "Insira o desconto ( em prercentagem ) : ";
  getline ( cin , tmp );
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  } 
  istringstream ss( tmp );
  ss >> des; 
  cout << "Insira o número da apólice : ";
  getline ( cin , tmp );
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  }
  istringstream s( tmp );
  s >> apo; 
  Utente *ptr = new Utente ( nome , tel , mor , seg , des , apo );
  insPacOrd( ptr , u );
  return findPos ( *ptr , u );  
}


int insMed( vector<Medico *>  & v , vector<Especialidade *> & e )
{
  string nome,tel,espe;
  int duracao;
  int hora_i , hora_f , min_i , min_f;
  getline( cin, nome ); //limpar o cin;
  cout << "Insira o nome do(a) médico(a): ";
  long cedula;
  getline( cin , nome );
  cout << "Insira o telefone do(a) médico(a): ";
  getline( cin , tel );
  while ( ! isNum( tel )  )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tel );
  } 
  cout << "Insira a especialidade do(a) médico(a): ";
  getline( cin , espe );
  Especialidade *esp = findEsp ( espe , e );
  if ( esp == NULL )
  {
    esp = new Especialidade;
    esp->setNom( espe );  
  } 
  cout << "Insira a cédula do(a) médico(a): ";
  cin >> cedula;
  cout << "Insira a duracao média da consulta do(a) médico(a): ";
  cin >> duracao;
  char espaco;
  cout << "Insira a hora do início do trabalho do(a) médico(a) separado por um caracter: ";
  cin >> hora_i >> espaco >> min_i;
  cout << "Insira a hora do final do trabalho  do(a) médico(a) separado por um caracter: ";
  cin >> hora_f >> espaco >> min_f;
  Hora inicio ( hora_i , min_i );
  Hora fim ( hora_f , min_f );
  Medico a ( nome , tel , duracao , cedula );
  a.setEspe( esp );
  Medico *ptr = find( a , v );
  if (ptr == NULL)
  {
    ptr = new Medico ( nome , tel , duracao , cedula );
    ptr->setIni( inicio );
    ptr->setFim( fim );
    ptr->setEspe( esp );
    insMedOrd( ptr , v );
    return findPos( cedula , v );
  }
  else
  {
    cout << "Já existe um médico com esse dados deseja alterá-los? (S/N)\n";
    char resposta;
    while ( resposta != 'S' && resposta != 'N' && resposta != 'n' && resposta != 's' )
    {
      cin >> resposta;
      cout << "Insira uma resposta válida. S para sim e N para não.\n";
    }
    if ( resposta == 'S' || resposta == 's' )
    {
      int pos = findPos( a , v );
      v.at( pos )->setNome( nome );
      v.at( pos )->setTel( tel );
      v.at( pos )->setDur( duracao );
      v.at( pos )->setIni( inicio );
      v.at( pos )->setFim( fim );
      v.at( pos )->setEspe( esp );
      cout << "Dados actualizados\n\n";
    }
    return findPos ( cedula , v );
  }
}
vector<Medico *>::iterator insMedOrd ( Medico * m , vector<Medico *> & v )
{
  vector<Medico *>::iterator it = v.begin();
  for ( int i = 0 ; i < (int) v.size() ; i++ )
  {
    if ( ( *v.at( i ) ).getId() >= ( *m ).getId() )
    {
      v.insert( it , m );
      it++;
      return it;
    }
    it++;
  }
  v.push_back( m );
  return it;
} 

vector<Utente *>::iterator insPacOrd ( Utente * m , vector<Utente *> & v )
{
  vector<Utente *>::iterator it = v.begin();
  for ( int i = 0 ; i < (int) v.size() ; i++ )
  {
    if ( ( *v.at( i ) ).getId() >= ( *m ).getId() )
    {
      v.insert( it , m );
      it++;
      return it;
    }
    it++;
  }
  v.push_back( m );
  return it;
} 

template <class Comparable>int findPos ( unsigned long ced , vector<Comparable *> & v )
{
  int left = 0, right = v.size() - 1;
  while (left <= right)
  {
    int middle = (left + right) / 2;
    if ( ced == (*v.at(middle)).getId() ) return middle;
    else if ( ced < (*v.at(middle)).getId() ) right = middle - 1;
    else left = middle + 1;
  }
  return -1;
}
template <class Comparable> int findPos ( const Comparable & m , vector<Comparable *> & v )
{
  int left = 0, right = v.size() - 1;
  while (left <= right)
  {
    int middle = (left + right) / 2;
    if ( m.getId() == (*v.at(middle)).getId() ) return middle;
    else if ( m.getId() < (*v.at(middle)).getId() ) right = middle - 1;
    else left = middle + 1;
  }
  return -1;
}
template <class Comparable > Comparable * find ( const Comparable & m , vector<Comparable *> & v )
{
  int left = 0 , right = v.size() - 1;
  while ( left <= right )
  {
    int middle = ( left + right ) / 2;
    if ( m.getId() == ( *v.at( middle ) ).getId() ) return v.at( middle );
    else if ( m.getId() < ( *v.at( middle ) ).getId() ) right = middle - 1;
    else left = middle + 1;
  }
  return NULL;
}
template <class Comparable> Comparable * find ( unsigned long ced, vector<Comparable *> & v )
{
  int left = 0 , right = v.size() - 1;
  while ( left <= right )
  {
    int middle = ( left + right )  / 2;
    if ( ced == ( *v.at( middle ) ).getCed() ) return v.at( middle );
    else if ( ced < ( *v.at( middle ) ).getCed() ) right = middle - 1;
    else left = middle + 1;
  }
  return NULL;
}
Especialidade * findEsp ( string m , vector<Especialidade *> & v )
{
  for( int i = 0 ; i < (int) v.size() ; i++ )
  {
    if ( m == v.at( i )->getNom() )
      return v.at( i );
  }
  return NULL;
}

bool carregaEsp( string m , vector<Especialidade *> & v )
{
  ifstream fin( m.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
    string line;
    while ( ! fin.eof() )
    {
      getline( fin, line );
      if ( ! line.empty() )
        if ( findEsp ( m , v ) == NULL )
        {
          Especialidade * a = new Especialidade( line );
          v.push_back( a );
          a->setNom( m );
        }
    }
  return true;
}

bool carregaMed ( string m , vector<Medico *> & v , vector<Especialidade *> & e )
{
  string nome, tel, espe, tmp;
  int duracao;
  int hora_i,hora_f, min_i, min_f;
  long ced=-1;
  char espaco;
  ifstream fin( m.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
    while ( !fin.eof() )
    {
      getline( fin , tmp , '|' );
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> ced;
      }
      getline( fin, nome, '|' );
      getline( fin, tel, '|' );
      getline( fin, espe, '|' );
      Especialidade *esp = findEsp( espe , e );
      if ( esp == NULL )
      {
        esp = new Especialidade;
        esp->setNom(espe);
        e.push_back( esp );
      } 
      getline( fin, tmp , '|' );
      if (!tmp.empty())
      {
        istringstream ss( tmp );
        char espaco;
        ss >> hora_i >> espaco >> min_i;

      }
      getline( fin , tmp , '|' );
      if (!tmp.empty())
      {
        istringstream ss ( tmp );
        ss >> hora_f >> espaco >> min_f;
      }
      getline(fin, tmp );
      if (!tmp.empty())
      {
        istringstream ss(tmp);
        ss >> duracao;
        Medico *ptr;
        ptr = new Medico ( nome , tel , duracao , ced );
        Hora fim( hora_f , min_f );
        Hora inicio( hora_i , min_i );
        ptr->setIni( inicio );
        ptr->setFim( fim );
        ptr->setEspe( esp );
        insMedOrd( ptr, v );
      }
    }
  return true;
}

bool carregaPac( string m , vector<Utente *> & u )
{
  string nome, tel, seg, mor, tmp;
  int desconto;
  long id, apolice, ultimo=0;
  ifstream fin( m.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  while ( !fin.eof() )
  {
    getline( fin , tmp , '|' ); 
    if (!fin.eof())
    {
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> id;
        if ( id >= ultimo ) ultimo = id+1;
      }
      getline( fin , nome , '|' );
      getline( fin , tel , '|' );
      getline( fin , mor , '|' );
      getline( fin , seg , '|' );    
      getline( fin , tmp , '|' );
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> desconto;
      }
      getline( fin , tmp );
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> apolice;
        Utente *ptr = new Utente ( nome , tel , mor, seg, desconto, apolice, id);
        (*ptr).setUN(ultimo);
        insPacOrd( ptr , u );
      }
    }
  }
  return true;
}


bool delMed( const Medico &  )
{

return false;

}
bool delMed( unsigned long  )
{
return false;


}

void listar ( const vector<Especialidade *> & v )
{
  for ( int i = 0; i< (int) v.size() ; i++ )
   cout << (* v.at( i ) ).getNom() << endl;
}

bool isNum( string s )
{
  if ( ! s.empty() )
  {
    for (int i = 0 ; i < (int) s.size() ; i++)
      if ( !isdigit( s.at( i ) ) )
        return false;
    return true;
  }
  else return false;
}
