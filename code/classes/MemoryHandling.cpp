#include "headers/MemoryHandling.h"
/*
TO DO:
Extra:::
acabar o delMed
impletar Horario
acabar de proteger contra eof
*/

vector<Consulta *>::iterator find ( Consulta * con, vector<Consulta *> & c )
{
  vector<Consulta *>::iterator it = c.begin();
  for ( int i = 0 ; i < (int) c.size() ; i++ ,it++)
  {
    if ( c.at( i )->getMed()->getId() == con->getMed()->getId() )
    {
        for ( ;  i < (int) c.size()  ; i++ , it++ )
        {
          if ( c.at( i )->getDat() == con->getDat() )
          {
            for ( ;  i < (int) c.size() ; i++, it++)
            {
              if ( c.at( i )->getHor() == con->getHor() )
              {
                return it;
              }
            }
          }
        }
    }
  }
  it = c.end();
  return it;

}

bool delCon( vector<Consulta *> & c , Medico * & med , Hora & h , Data & d )
{
  Consulta *ptr =  new Consulta (med , NULL , d , h , 0);
  vector<Consulta *>::iterator it = find ( ptr, c );
  if ( it == c.end() )
  {
    cout << "Não foi encontrada uma consulta com estas características. Logo não foi desmarcada nenhuma consulta.\n";
    return false;
  }
  c.erase ( it );
  return true;
}

bool delCon( vector<Medico *> & v , vector<Consulta *> & c)
{
  unsigned long ced;
  int dia, mes, ano , hora , min;
  char espaco;
  string tmp;
  cin.get();
  cout << "Insira a cédula do Médico : ";
  try
  {
    ced = getLong();
  }
  catch (EOI &)
  {
    return false;
  }
  Medico *ptr_med = find ( ced , v );
  while ( ptr_med == NULL )
  {
    cout << "Médico Inexistente.\nInsira a cédula do Médico : ";
    try
    {
      ced = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    ptr_med = find ( ced , v );
  }
  cout << "Insira a data da consulta separadas por um caracter (no formato dd/mm/aaaa): ";
  getline( cin , tmp );
  while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Data d( dia , mes , ano );
  cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm : ";
  getline( cin , tmp );
  while (!isHor( tmp ) )
  {
    cout << "Hora inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream sss(tmp);
  sss >> hora >> espaco >> min;
  Hora h( hora , min ); 
  if ( delCon ( c , ptr_med , h , d ) )
    return true;
  else
    return false;
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
  while ( ! isNum( tel ) || tel.size() > 9 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 10 algarismos)\nInsira outro: ";
    getline ( cin , tel );
  } 
  cout << "Insira a morada: ";
  getline( cin , mor );
  cout << "Insira a seguradora (escreva ""Sem"" para indicar sem seguro): ";
  getline( cin , seg );
  if ( seg=="Sem" || seg == "sem" )
  {
    des = 0;
    apo = 0;
  }
  else
  {
    if ( seg == "Caixa" )
    {
      cout << "Insira a taxa moderadora que o utente paga : ";
      getline ( cin , tmp );
      while ( ! isNum( tmp ) || tmp.size() > 10 )
      {
        cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
        getline ( cin , tmp );
      } 
      istringstream ss( tmp );
      ss >> des; 
      cout << "Insira o número de beneficiario : ";
      getline ( cin , tmp );
      while ( ! isNum( tmp ) || tmp.size() > 10 )
      {
        cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
        getline ( cin , tmp );
      }
      istringstream s( tmp );
      s >> apo;
    }
    else
    {
      cout << "Insira a percentagem que o utente paga : ";
      getline ( cin , tmp );
      while ( ! isNum( tmp ) || tmp.size() > 2 )
      {
        cout << "Número inválido ou demasiado grande (tem que ser menor de 3 algarismos)\nInsira outro: ";
        getline ( cin , tmp );
      } 
      istringstream ss( tmp );
      ss >> des; 
      cout << "Insira o número da apólice : ";
      getline ( cin , tmp );
      while ( ! isNum( tmp ) || tmp.size() > 10 )
      {
        cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
        getline ( cin , tmp );
      }
      istringstream s( tmp );
      s >> apo;
    }
  }
  Utente *ptr = new Utente ( nome , tel , mor , seg , des , apo );
  ptr->setSis( true );
  insPacOrd( ptr , u );
  return findPos ( *ptr , u );  
}

vector<Consulta *>::iterator insConOrd ( Consulta * con , vector<Consulta *> & c )
{
  vector<Consulta *>::iterator it = c.begin();
  vector<Consulta *>::iterator it_f = c.end();
  it_f--;
  for (int i = c.size()-1 ; i >= 0 ; i--,it_f--)
  {
    if ( c.at( i )->getMed()->getId() == con->getMed()->getId() )
    {
      break;
    }
  }
  for ( int i = 0 ; i < (int) c.size() ; i++ ,it++)
  {
    if ( c.at( i )->getMed()->getId() >= con->getMed()->getId() )
    {
        for ( ; it < it_f ; it++,it_f--)
        {
          if ( c.at( i )->getDat() >= con->getDat() )
          {
            for ( ; it < it_f; it++)
            {
              if ( c.at( i )->getHor() >= con->getHor() )
              {
                c.insert( it , con );
                it++;
                return it;
              }
            }
            c.insert( it , con );
            it++;
            return it;
          }
        }
        c.insert( it , con);
        it++;
        return it;
    }
  }
  c.push_back(con);
  it_f = c.end();
  it_f--;
  return it_f;
}

int insCon ( vector<Medico *> & v , vector<Utente *> & u , vector<Consulta *> &c )
{
  string tmp;
  int hora , min , dia, mes , ano , duracao;
  long ced, id;
  float preco;
  cout << "Insira a cédula do Médico: ";
  try
  {
    ced = getLong();
  }
  catch (EOI &)
  {
    return false;
  }
  Medico *ptr_m = find( ced , v );
  while (ptr_m == NULL )
  {
    cout << "Médico Inesxistente. Insira a cédula do Médico: ";
    try
    {
      ced = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    ptr_m = find( ced , v );
  }
  cout << "Insira o identificador do utente: ";
  try
  {
    id = getLong();
  }
  catch (EOI &)
  {
    return false;
  }
  Utente *ptr_u = find( id , u );
  while ( ptr_u == NULL )
  {
    cout << "Utente Inesxistente. Insira a cédula do utente: ";
    try
    {
      id = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    ptr_u = find( id , u );
  }
  char espaco;
  cout << "Insira a Data separadas por um caracter (no formato dd/mm/aaaa): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    } 
  }
  istringstream s(tmp);
  s >> dia >> espaco >> mes >> espaco >> ano;
  cout << "Insira a hora: ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while (!isHor( tmp ) )
  {
    cout << "Hora inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }  
  }
  istringstream ss(tmp);
  ss >> hora >> espaco >> min;
  if ( ptr_u->getSeg().getSeg() == "Caixa")
  {
    preco = ptr_u->getSeg().getDes();
  }
  else
  {
    cout << "Insira o preço: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
    while ( ! isNum( tmp ) && tmp.size() < 10 )
    {
      cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
    }
    istringstream sss( tmp );
    sss  >> preco;
  }
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
  int duracao, dur_max;
  int hora_i , hora_f , min_i , min_f;
  getline( cin, nome ); //limpar o cin;
  cout << "Insira o nome do(a) médico(a): ";
  long cedula;
  getline( cin , nome );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  cout << "Insira o telefone do(a) médico(a): ";
  getline( cin , tel );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( ! isNum( tel )  )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tel );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  } 
  cout << "Insira a especialidade do(a) médico(a): ";
  getline( cin , espe );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  Especialidade *esp = findEsp ( espe , e );
  if ( esp == NULL )
  {
    esp = new Especialidade;
    esp->setNom( espe );  
  } 
  cout << "Insira a cédula do(a) médico(a): ";
  getline ( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  istringstream ss( tmp );
  ss  >> cedula;
  cout << "Insira a duracao média da consulta do(a) médico(a): ";
  getline ( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  istringstream s( tmp );
  s >> duracao;
  while ( duracao <= 0 )
  {
    cout << "Duração das consultas tem de ser superior a zero. Insira outra: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
    while ( ! isNum( tmp ) && tmp.size() < 10 )
    {
      cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
    }
    istringstream sss( tmp );
    sss >> duracao;  
  }
  cout << "Insira a duracao máxima da consulta do(a) médico(a): ";
  getline ( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  istringstream sss( tmp );
  sss >> dur_max;
    while ( dur_max <= 0 || dur_max <= duracao )
  {
    cout << "Duração das consultas tem de ser superior a zero e superior à duração média . Insira outra: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
    while ( ! isNum( tmp ) && tmp.size() < 10 )
    {
      cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
    }
    istringstream sss( tmp );
    sss >> dur_max;  
  }
  char espaco;
  cout << "Insira a hora do início do trabalho do(a) médico(a) separado por um caracter: ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while (!isHor( tmp ) )
  {
    cout << "Hora inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }  
  }
  istringstream sssss(tmp);
  sssss >> hora_i >> espaco >> min_i;
  cout << "Insira a hora do final do trabalho  do(a) médico(a) separado por um caracter: ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while (!isHor( tmp ))
  {
    cout << "Hora inválida. Insira outra: " << endl;
    getline( cin , tmp );  
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  istringstream ssss(tmp);
  ssss >> hora_f >> espaco >> min_f;
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
    ptr->setDurM( dur_max );
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
    if ( ced == v.at( middle )->getId() ) return v.at( middle );
    else if ( ced < v.at( middle )->getId() ) right = middle - 1;
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

bool carregaCon( string f , vector<Medico *> & v , vector<Utente *> & u , vector<Consulta *> & c )
{
  unsigned long ced , id;
  int dia, mes , ano, duracao , preco , hora , min;
  char estado;
  string tmp;
  ifstream fin( f.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  c.clear();
  while ( !fin.eof() )
  {
    getline( fin , tmp , '|' );
    if ( !tmp.empty() )
    {
      istringstream ss ( tmp );
      ss >> ced;
    }
    getline( fin , tmp , '|' );
    if ( !tmp.empty() )
    {
      istringstream ss ( tmp );
      ss >> id;
    }
    getline( fin , tmp , '|' );
    if ( !tmp.empty() )
    {
      char espaco;
      istringstream ss ( tmp );
      ss >> dia >> espaco >> mes >> espaco >> ano;
    }
    getline( fin , tmp , '|' );
    if ( !tmp.empty() )
    {
      char espaco;
      istringstream ss ( tmp );
      ss >> hora >> espaco >> min;
    }
    getline( fin , tmp , '|' );
    if ( !tmp.empty() )
    {
      istringstream ss ( tmp );
      ss >> preco;
    }
    getline( fin , tmp , '|' );
    if ( !tmp.empty() )
    {
      istringstream ss ( tmp );
      ss >> duracao;
    }
    getline( fin , tmp );
    if ( !tmp.empty() )
    {
      istringstream ss ( tmp );
      ss >> estado;
      Medico *ptr_m = find ( ced , v );
      Utente *ptr_u = find ( id , u );
      Data d( dia , mes , ano );
      Hora h( hora , min );
      Consulta *ptr = new Consulta( ptr_m , ptr_u , d , h , preco );
      ptr->setEst( estado );
      c.push_back(ptr);
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
  else {cout << "s="<<s << endl;return false;}
}

bool isDat ( string s )
{
  Data d;
  int dia,mes,ano;
  char espaco;
  if ( ! s.empty()  && s.size() <= 10 && s.size() >= 8 ) 
  {
    if ( s.size() == 10 )
    {
      for (int i = 0 ; i < (int) s.size() ; i++)
      {
        if ( i != 2 && i != 5 )
        {
          if (!isdigit( s.at( i ) ) ) return false;      
        }
        else
        {
          if (isdigit( s.at( i ) ) ) return false;
        }
      }
      istringstream ss( s );
      ss >> dia >> espaco >> mes >> espaco >> ano;
      try
      {
        d.setData( dia , mes , ano );
      }
      catch(DataImpossivel & d)
      {
        return false;
      }
      return true;
    }
    else
    {
      if ( s.size() == 8 )
      {
        for (int i = 0 ; i < (int) s.size() ; i++)
        {
          if ( i != 1 && i!= 3 )
          {
            if (!isdigit( s.at( i ) ) ) return false;   
          }
          else
          {
             if (isdigit( s.at( i ) ) ) return false;   
          }
        }
        istringstream ss( s );
        ss >> dia >> espaco >> mes >> espaco >> ano;
        try
        {
          d.setData( dia , mes , ano );
        }
        catch(DataImpossivel & d)
        {
          return false;
        }
        return true;
      }
      else
      {
        if ( !isdigit( s.at(1) ) )
        {
          for (int i = 0 ; i < (int) s.size() ; i++)
          {
            if ( i != 1 && i!= 4 )
            {
              if (!isdigit( s.at( i ) ) ) return false;
            }
            else
            {
             if ( isdigit( s.at( i ) ) ) return false;
            }
          }
          istringstream ss( s );
          ss >> dia >> espaco >> mes >> espaco >> ano;
          try
          {
            d.setData( dia , mes , ano );
          }
          catch(DataImpossivel & d)
          {
            return false;
          }
          return true;
        }
        else
        {
          for (int i = 0 ; i < (int) s.size() ; i++)
          {
            if ( i != 2 && i!= 4 )
            {
              if (!isdigit( s.at( i ) ) ) return false;   
            }
            else
            {
             if (isdigit( s.at( i ) ) ) return false;                 
            }
          }
          istringstream ss( s );
          ss >> dia >> espaco >> mes >> espaco >> ano;
          try
          {
            d.setData( dia , mes , ano );
          }
          catch(DataImpossivel & d)
          {
            return false;
          }
          return true;
        }
      }
    }
  }
  else return false;
}

bool isHor( string s)
{
  Hora h;
  int hora,min;
  char espaco;
  if ( ! s.empty()  && s.size() <= 5 && s.size() >= 3 ) 
  {
    if ( s.size() == 5 )
    {
      for (int i = 0 ; i < (int) s.size() ; i++)
      {
        if ( i != 2 )
        {
          if (!isdigit( s.at( i ) ) ) return false;      
        }
        else
        {
          if (isdigit( s.at( i ) ) ) return false;
        }
      }
      istringstream ss( s );
      ss >> hora >> espaco >> min;
      try
      {
        h.setHora( hora , min );
      }
      catch(HoraImpossivel & d)
      {
        return false;
      }
      return true;
    }
    else
    {
      if ( s.size() == 3 )
      {
        for (int i = 0 ; i < (int) s.size() ; i++)
        {
          if ( i != 1 )
          {
            if (!isdigit( s.at( i ) ) ) return false;   
          }
          else
          {
             if (isdigit( s.at( i ) ) ) return false;   
          }
        }
        istringstream ss( s );
        ss >> hora >> espaco >> min;
        try
        {
          h.setHora( hora , min );
        }
        catch(HoraImpossivel & d)
        {
          return false;
        }
        return true;
      }
      else
      {
        if ( !isdigit( s.at(1) ) )
        {
          for (int i = 0 ; i < (int) s.size() ; i++)
          {
            if ( i != 1)
            {
              if (!isdigit( s.at( i ) ) ) return false;
            }
            else
            {
             if (isdigit( s.at( i ) ) ) return false;
            }
          }
          istringstream ss( s );
          ss >> hora >> espaco >> min;
          try
          {
            h.setHora( hora , min );
          }
          catch(HoraImpossivel & d)
          {
            return false;
          }
          return true;
        }
        else
        {
          for (int i = 0 ; i < (int) s.size() ; i++)
          {
            if ( i != 2 )
            {
              if (!isdigit( s.at( i ) ) ) return false;   
            }
            else
            {
             if (isdigit( s.at( i ) ) ) return false;                 
            }
          }
          istringstream ss( s );
          ss >> hora >> espaco >> min;
          try
          {
            h.setHora( hora , min );
          }
          catch(HoraImpossivel & d)
          {
            return false;
          }
          return true;
        }
      }
    }
  }
  else return false;
}

long getLong()
{
  long id;
  string tmp;
  getline ( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    throw EOI();
  }
  while ( ! isNum( tmp ) && tmp.size() < 10 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 11 algarismos)\nInsira outro: ";
    getline ( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      throw EOI();
    }
  }
  istringstream s( tmp );
  s  >> id;
  return id;
}
