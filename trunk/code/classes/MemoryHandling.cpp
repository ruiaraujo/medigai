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
  while ( ! isNum( tmp ) || tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  } 
  istringstream ss( tmp );
  ss >> des; 
  cout << "Insira o número da apólice : ";
  getline ( cin , tmp );
  while ( ! isNum( tmp ) || tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  }
  istringstream s( tmp );
  s >> apo; 
  Utente *ptr = new Utente ( nome , tel , mor , seg , des , apo );
  ptr->setSis( true );
  insPacOrd( ptr , u );
  return findPos ( *ptr , u );  
}

vector<Consulta *>::iterator insConOrd ( Consulta * con , vector<Consulta *> & c )
{
  int i;
  vector<Consulta *>::iterator it = c.begin();
  for ( i = 0 ; i < (int) c.size() ; i++ )
  {
    if ( c.at( i )->getMed()->getId() == con->getMed()->getId() )
    {
      for ( ; i < (int) c.size() ; i++ )
      {
        if ( c.at( i )->getDat() == con->getDat() )
        {
          for ( ; i < (int) c.size() ; i++ )
          {
            if ( c.at( i )->getHor() == con->getHor() )
            {
              c.insert( it , con );
              return it;
            }
            it++;
          }
        }
        it++;
      }
    }
    it++;
  }
}

int insCon ( vector<Medico *> & v , vector<Utente *> & u , vector<Consulta *> &c )
{
  string tmp;
  int hora , min , dia, mes , ano , duracao;
  long ced, id;
  float preco;
  cout << "Insira a cédula do Médico: ";
  cin >> ced;
  Medico *ptr_m = find( ced , v );
  while (ptr_m == NULL )
  {
    cout << "Médico Inesxistente. Insira a cédula do Médico: ";
    cin >> ced;
    ptr_m = find( ced , v );
  }
  cout << "Insira o identificador do utente: ";
  cin >> id;
  Utente *ptr_u = find( ced , u );
  while ( ptr_u == NULL )
  {
    cout << "Utente Inesxistente. Insira a cédula do utente: ";
    cin >> id;
    ptr_u = find( ced , u );
  }
  char espaco;
  cout << "Insira a Data separadas por um caracter: ";
  cin >> dia >> espaco >> mes >> espaco >> ano;
  cout << "Insira a hora: ";
  cin >> hora >> espaco >> min;
  cout << "Insira o preço: ";
  cin >> preco;
  cout << "Insira a duração: ";
  cin >> duracao;
  while ( duracao >(int) ptr_m->getDurM() || duracao <(int) ptr_m->getDur() )
  {
    if ( duracao > (int) ptr_m->getDurM() )
    {
      cout << "Duração acima da duração máxima do médico. Insira outra duração: ";
      cin >> duracao;    
    }
    if ( duracao < (int) ptr_m->getDur() )
    {
      cout << "Duração abaixo da duração mínima do médico. Insira outra duração: ";
      cin >> duracao;    
    } 
  }
  Hora h( hora , min );
  Data d ( dia , mes , ano );
  Consulta *con = new Consulta ( ptr_m , ptr_u  , d , h , preco );
  con->setDur( duracao );
  insConOrd( con , c );
  return 1;
}

int insMed( vector<Medico *>  & v , vector<Especialidade *> & e )
{
  string nome, tel, espe, tmp;
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
  getline ( cin , tmp );
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  }
  istringstream ss( tmp );
  ss  >> cedula;
  cout << "Insira a duracao média da consulta do(a) médico(a): ";
  getline ( cin , tmp );
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  }
  istringstream s( tmp );
  s >> duracao;
  cout << "Insira a duracao máxima da consulta do(a) médico(a): ";
  getline ( cin , tmp );
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
  }
  istringstream sss( tmp );
  sss >> duracao;
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
    if ( ced == ( *v.at( middle ) ).getId() ) return v.at( middle );
    else if ( ced < ( *v.at( middle ) ).getId() ) right = middle - 1;
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
  v.clear();
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
  int duracao, dur_max;
  int hora_i,hora_f, min_i, min_f;
  long ced=-1;
  char espaco;
  ifstream fin( m.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  v.clear();
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
      getline(fin, tmp , '|' );
      if (!tmp.empty())
      {
        istringstream ss(tmp);
        ss >> duracao;
      }
      getline(fin, tmp );      
      if (!tmp.empty())
      {
        istringstream ss ( tmp );
        ss >> dur_max;
        Medico *ptr;
        ptr = new Medico ( nome , tel , duracao , ced );
        Hora fim( hora_f , min_f );
        Hora inicio( hora_i , min_i );
        ptr->setDurM( dur_max );
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
  bool sistema;
  ifstream fin( m.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  u.clear();
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
      getline( fin , tmp , '|' );
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> apolice;
      }
      getline( fin , tmp );
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> sistema;
        Utente *ptr = new Utente ( nome , tel , mor, seg, desconto, apolice, id);
        ptr->setUN( ultimo );
        ptr->setSis( sistema );
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
bool delMed( unsigned long  ced , vector<Medico *> & v )
{
  int pos = findPos( ced , v );
  if ( pos == -1) return false;
  if ( pos > (int)( v.size() / 2 ) )
  {
    vector<Medico *>::iterator it = v.end();
    it--;
    for ( int i = v.size()-1 ; i > pos ; i-- )
      it--;
    v.erase(it);
  }
  else
  {
    vector<Medico *>::iterator it = v.begin();
    for ( int i = 0 ; i < pos ; i++ )
      it++;
    v.erase(it);
  }
  return true;
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
