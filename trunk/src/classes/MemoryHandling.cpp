#include "MemoryHandling.h"
/*
TO DO:
Polish everything
*/

float precoMedioP( vector<Utente *> & v , vector<Consulta *> & c)
{
  long ced;
  cout << "Insira o identificador do utente: ";
  try
  {
    ced = getLong();
  }
  catch (EOI &)
  {
    return false;
  }
  Utente *ptr_u = find( ced , v );
  while (ptr_u == NULL )
  {
    cout << "Utente Inesxistente. Insira o identificador do utente: ";
    try
    {
      ced = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    ptr_u = find( ced , v );
  }
  float total = 0.0;
  int dur_total = 0;
  for ( int i = 0 ; i < (int) c.size() ; i++ )
  {
    if ( c.at( i )->getUte()->getId() == ptr_u->getId() )
    {
      total += c.at( i )->getPre();
      dur_total += c.at( i )->getDur();
    }  
  }
  total /= (float)dur_total;
  if ( dur_total != 0 )
    cout << "Preço médio que o Sr.(a) " << ptr_u->getNome() << " paga por minuto é " << total << "€." << endl;
  else 
    cout << "Este utente ainda não efectou consultas logo não sabemos quanto é a sua média." << endl;
  return total;
}


float precoMedio( vector<Medico *> & v , vector<Consulta *> & c)
{
  long ced;
  cout << "Insira a cédula do médico: ";
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
  float total = 0.0;
  int dur_total = 0;
  for ( int i = 0 ; i < (int) c.size() ; i++ )
  {
    if ( c.at( i )->getMed()->getCed() == ptr_m->getCed() )
    {
      total += c.at( i )->getPre();
      dur_total += c.at( i )->getDur();
    }  
  }
  total /= (float)dur_total;
  if ( dur_total != 0 )
    cout << "Preço médio por minuto que o Dr.(a) " << ptr_m->getNome() << " cobra é " << total << "€." << endl;
  else 
    cout << "Este médico ainda não efectou consultas logo não sabemos quanto é a sua média." << endl;
  return total;
}

int findPos ( Consulta * con, vector<Consulta *> & c )
{
  for ( int i = 0 ; i < (int) c.size() ; i++ )
  {
    if ( c.at( i )->getMed()->getId() == con->getMed()->getId() )
    {
        for ( ;  i < (int) c.size()  ; i++  )
        {
          if ( c.at( i )->getDat() == con->getDat() )
          {
            for ( ;  i < (int) c.size() ; i++)
            {
              if ( c.at( i )->getHor() == con->getHor() )
              {
                return i;
              }
            }
          }
        }
    }
  }
  return -1;
}

vector<Medico *> listEsp( Especialidade * esp, vector<Medico *> & m )
{
  vector<Medico *> lista;
  for (int i = 0 ; i < (int) m.size() ; i++)
    if ( *esp == ( *m.at( i )->getEspe() ) )
      lista.push_back( m.at( i ) );
  return lista;
}

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
  delete c.at( findPos( ptr , c ) );
  delete ptr;
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
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Data d( dia , mes , ano );
  cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm ): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
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
  //getline( cin, nome ); //limpar o cin;
  cout << "Insira o nome do utente: ";
  getline( cin , nome );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( nome.empty() )
  {
    cout << "O nome não deve estar em branco." << endl << "Insira outra vez: ";
    getline( cin , nome );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  cout << "Insira o telefone do utente: ";
  getline( cin , tel );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( ! isNum( tel ) || tel.size() > 9 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 10 algarismos)\nInsira outro: ";
    getline ( cin , tel );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  } 
  cout << "Insira a morada: ";
  getline( cin , mor );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  cout << "Insira a seguradora (escreva ""Sem"" para indicar sem seguro): ";
  getline( cin , seg );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  if ( seg=="Sem" || seg == "sem" || seg.empty() )
  {
    seg = "Sem";
    des = 0;
    apo = 0;
  }
  else
  {
    if ( seg == "Caixa" )
    {
      cout << "Insira a taxa moderadora que o utente paga : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 10 )
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
      ss >> des; 
      cout << "Insira o número de beneficiario : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 10 )
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
      s >> apo;
    }
    else
    {
      cout << "Insira a percentagem que o utente paga : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 2 )
      {
        cout << "Número inválido ou demasiado grande (tem que ser menor de 3 algarismos)\nInsira outro: ";
        getline ( cin , tmp );
        if ( cin.eof() )
        {
          cin.clear();
          return -1;
        }
      }
      istringstream ss( tmp );
      ss >> des; 
      cout << "Insira o número da apólice : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 10 )
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
  it_f++;
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
  int dia, mes , ano , duracao;
  long ced, id;
  float preco;
  getline(cin, tmp);
  cout << "Insira a cédula do Médico: ";
  try
  {
    ced = getLong();
  }
  catch (EOI &)
  {
    return -1;
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
      return -1;
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
    return -1;
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
      return -1;
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
  Data d( dia , mes , ano );
  Horario< Medico , Data > timetable ( ptr_m , d , 0 );
  vector<Consulta *> tt = timetable.get( c );
  cout << "Insira a hora: ";
  Hora h;
  try
  {
      h = getHora();
  }
  catch (EOI &)
  {
    return -1;
  }
  while ( !horNCol ( tt , h , ptr_m->getDur() , ptr_m->getIni() , ptr_m->getFim() ) )
  {
    Hora ini(ptr_m->getIni()), fim(ptr_m->getFim());
    if ( h < ini || h > fim )
      cout << "Hora fora do Horário de trabalho do médico. Deve ser entre as  "<< ini << " e as " << fim << endl;
    else
    {
      cout << "Consulta incompatível com o horário existente!" << endl;
      timetable.print( cout , c);
    }
    cout  << "Insira outra: ";
    try
    {
      h = getHora();
    }
    catch (EOI &)
    {
      return -1;
    }
  }
  if ( ptr_u->getSeg().getSeg() == "Caixa")
  {
    preco = ptr_u->getSeg().getDes();
  }
  else
  {
    cout << "Insira o preço sem desconto: ";
    cin >> preco;
    while ( !cin.good() )
    {
      if ( cin.eof() )
      {
        cin.clear();
        cout << endl;
        return -1;
      }
      string lixo;
      cin.clear();
      getline ( cin , lixo );
      cout << "Input inválido. Insira outro preço: ";
      cin >> preco;
    }
    if ( ptr_u->getSeg().getDes() != 0 )
      preco *= (float)(ptr_u->getSeg().getDes()/100.0);
  }
  cout << "Preço a ser usado devido ao desconto do utente: " << preco << endl;
  getline ( cin , tmp);
  cout << "Insira a duração: ";
  try
  {
      duracao = getLong();
  }
  catch (EOI &)
  {
      return -1;
  }
  while ( duracao > (int) ptr_m->getDurM() || duracao <(int) ptr_m->getDur() || !horNCol ( tt , h , duracao , ptr_m->getIni() , ptr_m->getFim() ) )
  {
    if ( duracao > (int) ptr_m->getDurM() )
    {
      cout << "Duração acima da duração máxima do médico. Insira outra duração entre" << ptr_m->getDur() << " e ";
      cout << ptr_m->getDurM() << ": ";
      try
      {
        duracao = getLong();
      }
      catch (EOI &)
      {
        return -1;
      }
    }
    if ( duracao < (int) ptr_m->getDur() )
    {
      cout << "Duração abaixo da duração média do médico. Insira outra duração entre" << ptr_m->getDur() << " e ";
      cout << ptr_m->getDurM() << ": ";
      try
      {
        duracao = getLong();
      }
      catch (EOI &)
      {
        return -1;
      }
    } 
    if ( !horNCol ( tt , h , duracao , ptr_m->getIni() , ptr_m->getFim() ) )
    {
      cout << "Duração incompatível com o horário existente." << endl << "Este é o horário existente:" << endl;
      timetable.print( cout , c );
      cout << "Insira outra duração: ";
      try
      {
        duracao = getLong();
      }
      catch (EOI &)
      {
        return -1;
      }
    }
  }
  Consulta *con = new Consulta ( ptr_m , ptr_u  , d , h , preco );
  con->setDur( duracao );
  insConOrd( con , c );
  return findPos ( con , c );
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
    if ( inicio <= fim )
    {
      ptr->setIni( inicio );
      ptr->setFim( fim );
    }
    else
    {
      cout << "Hora final anterior à inicial. A trocar automaticamente... Porque o sistema não está preparado para médicos que trabalhem à noite." << endl;
      ptr->setIni( fim );
      ptr->setFim( inicio );    
    }
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
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
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

bool horario_med( vector<Medico *> & v , vector<Consulta *> & c )
{
  string tmp;
  int dia, mes , ano;
  char espaco;
  long ced;
  cin.get();
  cout << "Insira a cédula do médico: ";
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
  cout << "Insira a Data separadas por um caracter (no formato dd/mm/aaaa): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: ";
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    } 
  }
  istringstream s(tmp);
  s >> dia >> espaco >> mes >> espaco >> ano;
  Data d( dia , mes , ano );
  Horario <Medico , Data> horario (ptr_m , d , 0);
  horario.print( cout , c );
  return true;
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
    if ( m.getId() == v.at(middle)->getId() ) return middle;
    else if ( m.getId() < v.at(middle)->getId() ) right = middle - 1;
    else left = middle + 1;
  }
  return -1;
}
template <class Comparable > Comparable * find ( const Comparable & m , vector<Comparable *> & v )
{
  if ( !v.empty() )
  {
    int left = 0 , right = v.size() - 1;
    while ( left <= right )
    {
      int middle = ( left + right ) / 2;
      if ( m.getId() == v.at( middle )->getId() ) return v.at( middle );
      else if ( m.getId() < v.at( middle )->getId() ) right = middle - 1;
      else left = middle + 1;
    }
  }
  return NULL;
}
template <class Comparable> Comparable * find ( unsigned long ced, vector<Comparable *> & v )
{
  if ( !v.empty() )
  {
    int left = 0 , right = v.size() - 1;

    while ( left <= right )
    {
      int middle = ( left + right )  / 2;
      if ( ced == v.at( middle )->getId() ) return v.at( middle );
      else if ( ced < v.at( middle )->getId() ) right = middle - 1;
      else left = middle + 1;
    }
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
      if ( findEsp ( line , v ) == NULL )
      {
        Especialidade * a = new Especialidade( line );
        v.push_back( a );
      }
  }
  return true;
}

bool carregaCon( string f , vector<Medico *> & v , vector<Utente *> & u , vector<Consulta *> & c )
{
  unsigned long ced , id;
  int dia, mes , ano, duracao , hora , min;
  float preco;
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
      ptr->setDur( duracao );
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

bool delMed( unsigned long  ced , vector<Medico *> & v , vector<Consulta *> & c)
{
  int pos = findPos( ced , v );
  vector<Medico *> eq = listEsp ( v.at( pos )->getEspe() , v );
  vector<Medico *>::iterator it = eq.begin();
  for ( int i = 0  ; i < (int) eq.size(); i++ , it++)
    if ( ced == eq.at( i )->getCed() )
     eq.erase ( it );
  
  if ( pos == -1) return false; 
  bool consulta = false;
  for (int i = 0; i < (int) c.size() ; i++ )
  {
    if ( c.at(i)->getMed()->getCed() == ced && c.at(i)->getEst() == 'm' )
      consulta = true;
  }
  if (consulta)
  {
    cout << "Este médico que deseja eliminar tem consultas marcadas." << endl;
    cout << "Deseja cancelá-las (S para confirmar, N para mudar o médico responsável, U para cancelar ):" << endl;
    bool wrong = true;
    while ( wrong )
    {
      char opcao;
      cin.get();
      cin >> opcao;
      if ( cin.eof() )
      {
        cin.clear();
        return false;
      }
      switch ( opcao )
      {
        case 'S':
        case 's': v.at( pos )->setSis( false );
                  for (int i = 0; i < (int) c.size() ; i++ )
                  {
                    if ( c.at(i)->getMed()->getCed() == ced && c.at(i)->getEst() == 'm' )
                    {
                      Hora h( c.at( i )->getHor() );
                      Data d( c.at( i )->getDat() );
                      Medico * ptr = find ( ced , v );
                      delCon( c , ptr , h , d );
                      i--;
                    }
                  }
                  wrong = false;
                  break;
        case 'U':
        case 'u': wrong = false; 
                  break;
        case 'N':
        case 'n': if ( !eq.empty() )
                  {
                    cout << "Estes são os médicos com a mesma especialidade do médico que quer eliminar.";
                    cout << "Escolha um:"<< endl;
                    listar ( eq );
                    unsigned long id;
                    Medico * ptr_m;
                    ptr_m = NULL;
                    while (ptr_m == NULL )
                    {                
                      try
                      {
  id = getLong();
                      }
                      catch (EOI &)
                      {
  return false;
                      }
                      if ( ( ptr_m = find( id , eq ) ) == NULL )
  cout << "Médico inesxistente na lista de equivalência. Insira a cédula doutro médico: ";
                    }
                      v.at( pos )->setSis( false );
                    for (int i = 0; i < (int) c.size() ; i++ )
                    {
                      if ( c.at(i)->getMed()->getCed() == ced && c.at(i)->getEst() == 'm' )
 c.at( i )->setMed ( ptr_m );
                    }
                  }
                  else
                  {
                  cout << "Não há médicos com uma especialidade equivalente. Insira outra opção: " << endl;
                  }
                  break;
        default:  cout << "Opção desconhecida. Insira outra: ";
                  wrong = false;
                  break;
      }
    }            
  }
  else v.at( pos )->setSis( false );
  return true;
}

void listar ( const vector<Especialidade *> & v )
{
  for ( int i = 0; i< (int) v.size() ; i++ )
   cout << (* v.at( i ) ).getNom() << endl;
}

void listar ( const vector<Consulta *> & v )
{
  for ( int i = 0; i< (int) v.size() ; i++ )
    cout << *( v.at( i ) ) << endl;
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

bool altCon( vector<Consulta *> & c ,vector<Utente * > & u , vector<Medico * > & v )
{
  unsigned long ced;
  int dia, mes, ano , hora , min;
  char espaco;
  string tmp;
  cout << "Insira os dados da consulta que deseja alterar: " << endl;
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
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    }  
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Data d( dia , mes , ano );
  Horario <Medico , Data > horario ( ptr_med , d , 0 );
  horario.print(cout , c );
  cout << endl << "Insira a hora de início da consulta separadas por um caracter (no formato hh:mm ): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isHor( tmp ) )
  {
    cout << "Hora inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    }
  }
  istringstream sss(tmp);
  sss >> hora >> espaco >> min;
  Hora h( hora , min );
  Consulta *ptr =  new Consulta ( ptr_med , NULL , d , h , 0);
  int pos = findPos( ptr , c );
  if ( pos == -1 )
  {
    cout << "Não foi encontrada uma consulta com estas características. A abortar..." << endl;
    delete ptr;
    return false;
  }
  cout << "Insira os novos dados: " << endl;
  cin.putback('\n');
  if ( insCon( v , u, c ) == -1 )
  {
    cout << "Erro na actualização da consulta. A abortar..." << endl;
    delete ptr;
    return false;
  }
  delCon( c , ptr_med , h , d );
  delete ptr;
  return true;
}

bool ver_Con( vector<Consulta *> & c , vector<Medico * > & v )
{
  unsigned long ced;
  int dia, mes, ano;
  char espaco;
  string tmp;
  cout << "Insira os dados da consulta que visualizar: " << endl;
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
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: " << endl;
    getline( cin , tmp );  
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    }
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Data d( dia , mes , ano );
  cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm ): ";
  Hora h;
  try
  {
    h = getHora();
  }
  catch (EOI &)
  {
    return false;
  }
  Consulta *ptr =  new Consulta ( ptr_med , NULL , d , h , 0);
  int pos = findPos( ptr , c );
  if ( pos == -1 )
  {
    cout << "Não foi encontrada uma consulta com estas características. A abortar..." << endl;
    delete ptr;
    return false;
  }
	Hora h1 = h + c.at( pos )->getDur();
	cout << endl << "Dr.(ª) " << c.at( pos )->getMed()->getNome() << " no dia " <<  d << " às " << h << " até ";
	cout << h1  << "com o Sr.(ª) " << c.at( pos )->getUte()->getNome() << endl;
	delete ptr;
  return true;
}

bool delPac( vector<Utente *> & u , vector<Consulta *> & c)
{
	unsigned long int id;
	cin.clear();
	cout<<"Introduza o id do utente:";
  try
  {
    id = getLong();
  }
  catch (EOI &)
  {
    return false;
  }
  int pos = findPos( id , u );
  while ( pos == -1 )
  {
    cout << "Utente Inexistente.\nInsira o número identificativo do utente : ";
    try
    {
      id = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    pos = findPos ( id , u );
  }
  bool consulta = false;
  for (int i = 0; i < (int) c.size() ; i++ )
  {
    if ( c.at(i)->getUte()->getId() == id && c.at(i)->getEst() == 'm' )
      consulta = true;
  }
  if (consulta)
  {
    cout << "Este utente tem consultas marcadas. A desmarcar..."  << endl;
    u.at( pos )->setSis( false );
    for (int i = 0; i < (int) c.size() ; i++ )
    {
      if ( c.at(i)->getUte()->getId() == id && c.at(i)->getEst() == 'm' )
      {
        Hora h( c.at( i )->getHor() );
        Data d( c.at( i )->getDat() );
        Medico * ptr = c.at(i)->getMed();
        delCon( c , ptr , h , d );
        i--;
      }
    }
  }
  else u.at( pos )->setSis( false );
  
/*  if ( pos > (int)( u.size() / 2 ) )
  {
    vector<Utente *>::iterator it = u.end();
    it--;
    for ( int i = u.size()-1 ; i > pos ; i-- )
      it--;
    u.erase(it);
  }
  else
  {
    vector<Utente *>::iterator it = u.begin();
    for ( int i = 0 ; i < pos ; i++ )
      it++;
    u.erase(it);
  }
  return true;*/
  
  return true;
}
bool alt_Pac( vector<Utente *> & u )
{
  string nome, tel, seg, mor , tmp;
  float des;
  long apo;
	unsigned long int id;
	cin.get();
	cin.clear();
	cout<<"Introduza o id do utente:";
  try
  {
    id = getLong();
  }
  catch (EOI &)
  {
    return false;
  }
  int pos = findPos( id , u );
  while ( pos == -1 )
  {
    cout << "Utente Inexistente.\nInsira o número identificativo do utente : ";
    try
    {
      id = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    pos = findPos ( id , u );
  }
  
 /* vector<Utente *>::iterator it = u.begin();
  for ( int i = 0 ; i < pos ; i++ , it++ ) ;
  int n =  insPac( u );
	if ( n != -1 )
	{
	  u.at( n )->setUN( id );
	  u.erase(it);
  }*/
  cout << "Insira o nome do utente: ";
  getline( cin , nome );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( nome.empty() )
  {
    cout << "O nome não deve estar em branco." << endl << "Insira outra vez: ";
    getline( cin , nome );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  cout << "Insira o telefone do utente: ";
  getline( cin , tel );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while ( ! isNum( tel ) || tel.size() > 9 )
  {
    cout << "Número inválido ou demasiado grande (tem que ser menor de 10 algarismos)\nInsira outro: ";
    getline ( cin , tel );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  } 
  cout << "Insira a morada: ";
  getline( cin , mor );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  cout << "Insira a seguradora (escreva ""Sem"" para indicar sem seguro): ";
  getline( cin , seg );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  if ( seg=="Sem" || seg == "sem" || seg.empty() )
  {
    seg = "Sem";
    des = 0;
    apo = 0;
  }
  else
  {
    if ( seg == "Caixa" )
    {
      cout << "Insira a taxa moderadora que o utente paga : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 10 )
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
      ss >> des; 
      cout << "Insira o número de beneficiario : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 10 )
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
      s >> apo;
    }
    else
    {
      cout << "Insira a percentagem que o utente paga : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 2 )
      {
        cout << "Número inválido ou demasiado grande (tem que ser menor de 3 algarismos)\nInsira outro: ";
        getline ( cin , tmp );
        if ( cin.eof() )
        {
          cin.clear();
          return -1;
        }
      }
      istringstream ss( tmp );
      ss >> des; 
      cout << "Insira o número da apólice : ";
      getline ( cin , tmp );
      if ( cin.eof() )
      {
        cin.clear();
        return -1;
      }
      while ( ! isNum( tmp ) || tmp.size() > 10 )
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
      s >> apo;
    }
  }
  u.at( pos )->setNome( nome );
  u.at( pos )->setMor( mor ) ;
  u.at( pos )->setTel( tel );
  u.at( pos )->setSeg( seg , des , apo );
  return true;
}

Hora getHora()
{
  int hora, min;
  char espaco;
  string tmp;
  getline( cin , tmp );
  if ( cin.eof() )
	{
	  cin.clear();
	  throw EOI();
	}
  while (!isHor( tmp ) )
  {
    cout << "Hora inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream s(tmp);
  s >> hora >> espaco >> min;
  Hora h( hora , min ); 
  return h;
}



bool horNCol ( vector<Consulta *> & c , Hora & h , const int & duracao , const Hora & ini ,const Hora & fim )
{
  vector<Consulta *>::iterator it = c.begin();
  Hora h0 = h + duracao;
  if (h > fim || h < ini  || h0 > fim ) return false;
  for (int i = 0 ; i < (int) c.size() ; i++ , it++ )
  {
    if ( c.at( i )->getHor() + c.at( i )->getDur() > h &&  c.at( i )->getHor() < h )
      return false;
    if (  c.at( i )->getHor() < h + duracao &&  c.at( i )->getHor() > h  )
      return false;
  }
  return true;
}
bool pagarCon(vector<Consulta *> & c , vector<Medico * > & v )
{
  unsigned long ced;
  int dia, mes, ano;
  char espaco;
  string tmp;
  cout << "Insira os dados da consulta a pagar: " << endl;
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
  if ( cin.eof() )
  {
    cerr << "Detectado fim de input..." << endl;
    cin.clear();
    return false;
  }
	while (!isDat( tmp ) )
  {
    cout << "Data inválida. Insira outra: " << endl;
    getline( cin , tmp );  
    if ( cin.eof() )
    {
      cerr << "Detectado fim de input..." << endl;
      cin.clear();
      return false;
    }
  }
  istringstream s(tmp);
  s >> dia >> espaco >> mes >> espaco >> ano;
  Data d( dia , mes , ano );
	cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm ): ";
  Hora h;
  try
 	{
 	  h = getHora();
  }
  catch (EOI &)
  {
    return false;
  }
	Consulta *ptr =  new Consulta ( ptr_med , NULL , d , h , 0);
  int pos = findPos( ptr , c );
 	if ( pos == -1 )
  {
    cout << "Não foi encontrada uma consulta com estas características. A abortar..." << endl;
    delete ptr;
    return false;
  }
  if (  c.at( pos )->getEst() != 'p' || c.at( pos )->getEst() != 'P' )
  {
    c.at( pos )->setEst('p' );
    cout << "Consulta Efectuada e paga." << endl;
  }
  else cout << "Esta consulta já foi paga anteriormente." << endl;
  return true;
}

template<class C> vector <C *> find_Id( vector<C *> & u)
{
  string nome;
  vector<C *> lista;
	cout<<"Introduza o nome do utente:";
	getline( cin , nome );	
	if ( cin.eof() )
	{
	  cin.clear();
	  return lista;
	}
	for ( int i = 0; i < (int) u.size(); i++ )
	  if  ( u.at( i )->getNome() == nome )
      lista.push_back( u.at( i ) );
  return lista;
}

template <class Comparable>void listar( const vector<Comparable *> & v)
{
  for ( int i = 0; i< (int) v.size() ; i++ )
   if ( v.at( i )->getSis() )
    cout << *( v.at( i ) ) << endl;
}


