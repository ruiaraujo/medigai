#include "MemoryHandling.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <curses.h>

using std::vector;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;

Clinic::Clinic( std::string file_m , std::string file_p, std::string file_e, std::string file_c ) :
                                             list_med() , list_pac() , list_esp() , list_con() ,
                                             files( file_m , file_p , file_e , file_c ) {}

std::vector<Doctor *> Clinic::getListMed() const { return this->list_med; }
std::vector<Patient *> Clinic::getListPac() const { return this->list_pac; }
std::vector<Specialty *> Clinic::getListEsp() const { return this->list_esp; }
std::vector<Consulta *> Clinic::getListCon() const { return this->list_con; }

float Clinic::precoMedioP()
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
  Patient pac_tmp;
  Patient *ptr_u = pac_tmp.find( ced , this->list_pac );
  while (ptr_u == NULL )
  {
    cout << "Patient Inesxistente. Insira o identificador do utente: ";
    try
    {
      ced = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    ptr_u = pac_tmp.find( ced , this->list_pac );
  }
  float total = 0.0;
  int dur_total = 0;
  for ( int i = 0 ; i < (int) this->list_con.size() ; i++ )
  {
    if ( this->list_con.at( i )->getUte()->getId() == ptr_u->getId() )
    {
      total += this->list_con.at( i )->getPre();
      dur_total += this->list_con.at( i )->getDur();
    }  
  }
  if ( dur_total != 0 )
  {
    total /= (float)dur_total;
    cout << "Preço médio que o Sr.(a) " << ptr_u->getName() << " paga por minuto é " << total << "€." << endl;
  }
  else 
  {
    cout << "Este utente ainda não efectou consultas logo não sabemos quanto é a sua média." << endl;
    return 0;
  }
  return total;
}


float Clinic::precoMedio()
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
  Doctor med_tmp;
  Doctor *ptr_m = med_tmp.find( ced , this->list_med );
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
    ptr_m = med_tmp.find( ced , this->list_med );
  }
  float total = 0.0;
  int dur_total = 0;
  for ( int i = 0 ; i < (int) this->list_con.size() ; i++ )
  {
    if ( this->list_con.at( i )->getMed()->getId() == ptr_m->getId() )
    {
      total += this->list_con.at( i )->getPre();
      dur_total += this->list_con.at( i )->getDur();
    }  
  }

  if ( dur_total != 0 )
  {
    cout << "Preço médio por minuto que o Dr.(a) " << ptr_m->getName() << " cobra é " << total << "€." << endl;
    total /= (float)dur_total;
  }
  else 
  {
    cout << "Este médico ainda não efectou consultas logo não sabemos quanto é a sua média." << endl;
    return 0;
  }
  return total;
}

vector<Doctor *> Clinic::listEsp( Specialty * esp )
{
  vector<Doctor *> lista;
  for (int i = 0 ; i < (int) this->list_med.size() ; i++)
    if ( *esp == ( *this->list_med.at( i )->getEspe() ) )
      lista.push_back( this->list_med.at( i ) );
  return lista;
}


bool Clinic::delCon( vector<Consulta *> & c , Doctor * & med , Hour & h , Date & d )
{
  Consulta *ptr =  new Consulta (med , NULL , d , h , 0);
  vector<Consulta *>::iterator it = ptr->find ( c );
  if ( it == c.end() )
  {
    cout << "Não foi encontrada uma consulta com estas características. Logo não foi desmarcada nenhuma consulta.\n";
    return false;
  }
  delete c.at( ptr->findPos( c ) );
  delete ptr;
  c.erase ( it );
  return true;
}

bool Clinic::delCon()
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
  Doctor med_tmp;
  Doctor *ptr_med = med_tmp.find ( ced , this->list_med );
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
    ptr_med = med_tmp.find ( ced , this->list_med );
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
    cout << "Date inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Date d( dia , mes , ano );
  cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm ): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isHor( tmp ) )
  {
    cout << "Hour inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream sss(tmp);
  sss >> hora >> espaco >> min;
  Hour h( hora , min ); 
  if ( this->delCon ( this->list_con , ptr_med , h , d ) )
    return true;
  else
    return false;
}
int Clinic::insPac ()
{
  string nome, tel, seg, mor , tmp;
  float des;
  long apo;
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
  Patient *ptr = new Patient ( nome , tel , mor , seg , des , apo );
  ptr->setSis( true );
  ptr->insOrd( this->list_pac );
  return ptr->findPos ( this->list_pac );  
}


int Clinic::insCon ()
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
  Doctor med_tmp;
  Doctor *ptr_m = med_tmp.find( ced , this->list_med );
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
    ptr_m = med_tmp.find( ced , this->list_med );
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
  Patient pac_tmp;
  Patient *ptr_u = pac_tmp.find( id , this->list_pac );
  while ( ptr_u == NULL )
  {
    cout << "Patient Inesxistente. Insira a cédula do utente: ";
    try
    {
      id = getLong();
    }
    catch (EOI &)
    {
      return -1;
    }
    ptr_u = pac_tmp.find( id , this->list_pac );
  }
  char espaco;
  cout << "Insira a Date separadas por um caracter (no formato dd/mm/aaaa): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return -1;
  }
  while (!isDat( tmp ) )
  {
    cout << "Date inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    } 
  }
  istringstream s(tmp);
  s >> dia >> espaco >> mes >> espaco >> ano;
  Date d( dia , mes , ano );
  Horario< Doctor , Date > timetable ( ptr_m , d );
  vector<Consulta *> tt = timetable.get( this->list_con );
  cout << "Insira a hora: ";
  Hour h;
  try
  {
      h = getHour();
  }
  catch (EOI &)
  {
    return -1;
  }
  while ( !this->horNCol ( tt , h , ptr_m->getDur() , ptr_m->getIni() , ptr_m->getFim() ) )
  {
    Hour ini(ptr_m->getIni()), fim(ptr_m->getFim());
    if ( h < ini || h > fim )
    {
      cout << "Hour fora do Horário de trabalho do médico. Deve ser entre as  ";
      cout << ini << " e as " << fim << endl;
    }
    else
    {
      cout << "Consulta incompatível com o horário existente!" << endl;
      timetable.print( cout , this->list_con );
    }
    cout  << "Insira outra: ";
    try
    {
      h = getHour();
    }
    catch (EOI &)
    {
      return -1;
    }
  }
  if ( ptr_u->getIns().getIns() == "Caixa")
  {
    preco = ptr_u->getIns().getDis();
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
    if ( ptr_u->getIns().getDis() != 0 )
      preco *= (float)(ptr_u->getIns().getDis()/100.0);
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
      cout << "Duração acima da duração máxima do médico. Insira outra duração entre";
      cout << ptr_m->getDur() << " e ";
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
      timetable.print( cout , this->list_con );
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
  con->insOrd( this->list_con );
  return con->findPos ( this->list_con );
}

int Clinic::insMed()
{
  string nome, tel, espe, tmp;
  int duracao, dur_max;
  int hora_i , hora_f , min_i , min_f;
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
  
  Specialty espe_tmp(espe);
  Specialty *esp = espe_tmp.find( this->list_esp );
  if ( esp == NULL )
  {
    esp = new Specialty( espe );
  }
  this->list_esp.push_back(esp);
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
    cout << "Hour inválida. Insira outra: " << endl;
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
    cout << "Hour inválida. Insira outra: " << endl;
    getline( cin , tmp );  
    if ( cin.eof() )
    {
      cin.clear();
      return -1;
    }
  }
  istringstream ssss(tmp);
  ssss >> hora_f >> espaco >> min_f;
  Hour inicio ( hora_i , min_i );
  Hour fim ( hora_f , min_f );
  Doctor med ( nome , tel , duracao , cedula );
  med.setEspe( esp );
  Doctor *ptr = med.find( this->list_med );
  if (ptr == NULL)
  {
    ptr = new Doctor ( nome , tel , duracao , cedula );
    if ( inicio <= fim )
    {
      ptr->setIni( inicio );
      ptr->setFim( fim );
    }
    else
    {
      cout << "Hour final anterior à inicial. A trocar automaticamente... Porque o sistema não está preparado para médicos que trabalhem à noite." << endl;
      ptr->setIni( fim );
      ptr->setFim( inicio );    
    }
    ptr->setEspe( esp );
    ptr->setDurM( dur_max );
    ptr->insOrd( this->list_med );
    return ptr->findPos( this->list_med );
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
      int pos = med.findPos( this->list_med );
      this->list_med.at( pos )->setName( nome );
      this->list_med.at( pos )->setTel( tel );
      this->list_med.at( pos )->setDur( duracao );
      this->list_med.at( pos )->setIni( inicio );
      this->list_med.at( pos )->setFim( fim );
      this->list_med.at( pos )->setEspe( esp );
      cout << "Dados actualizados\n\n";
    }
    return med.findPos ( this->list_med );
  }
}



bool Clinic::horario_med()
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
  Doctor med_tmp;
  Doctor *ptr_m = med_tmp.find( ced , this->list_med );
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
    ptr_m = med_tmp.find( ced , this->list_med );
  }
  cout << "Insira a Date separadas por um caracter (no formato dd/mm/aaaa): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isDat( tmp ) )
  {
    cout << "Date inválida. Insira outra: ";
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    } 
  }
  istringstream s(tmp);
  s >> dia >> espaco >> mes >> espaco >> ano;
  Date d( dia , mes , ano );
  Horario <Doctor , Date> horario (ptr_m , d );
  horario.print( cout , this->list_con );
  return true;
}

bool Clinic::delMed( unsigned long  ced )
{
  Doctor med_tmp;
  int pos = med_tmp.findPos( ced , this->list_med );
  vector<Doctor *> eq = listEsp ( this->list_med.at( pos )->getEspe() );
  vector<Doctor *>::iterator it = eq.begin();
  for ( int i = 0  ; i < (int) eq.size(); i++ , it++)
    if ( ced == eq.at( i )->getId() )
     eq.erase ( it );
  
  if ( pos == -1) return false; 
  bool consulta = false;
  for (int i = 0; i < (int) this->list_con.size() ; i++ )
  {
    if ( this->list_con.at(i)->getMed()->getId() == ced && this->list_con.at(i)->getEst() == 'm' )
      consulta = true;
  }
  if (consulta)
  {
    cout << "Este médico que deseja eliminar tem consultas marcadas." << endl;
    cout << "Diseja cancelá-las (S para confirmar, N para mudar o médico responsável, U para cancelar ):" << endl;
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
        case 's': this->list_med.at( pos )->setSis( false );
                  for (int i = 0; i < (int) this->list_con.size() ; i++ )
                  {
                    if ( this->list_con.at(i)->getMed()->getId() == ced && this->list_con.at(i)->getEst() == 'm' )
                    {
                      Hour h( this->list_con.at( i )->getHor() );
                      Date d( this->list_con.at( i )->getDat() );
                      Doctor * ptr = med_tmp.find ( ced , this->list_med );
                      delCon( this->list_con , ptr , h , d );
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
                    Doctor * ptr_m;
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
                      if ( ( ptr_m = med_tmp.find( id , eq ) ) == NULL )
                        cout << "Médico inesxistente na lista de equivalência. Insira a cédula doutro médico: ";
                    }
                      this->list_med.at( pos )->setSis( false );
                    for (int i = 0; i < (int) this->list_con.size() ; i++ )
                    {
                      if ( this->list_con.at(i)->getMed()->getId() == ced && this->list_con.at(i)->getEst() == 'm' )
 this->list_con.at( i )->setMed ( ptr_m );
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
  else this->list_med.at( pos )->setSis( false );
  return true;
}

void listar ( const vector<Specialty *> & v )
{
  for ( int i = 0; i< (int) v.size() ; i++ )
   cout << v.at( i )->getName() << endl;
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
  Date d;
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
        d.setDate( dia , mes , ano );
      }
      catch(DateNonexistent & d)
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
          d.setDate( dia , mes , ano );
        }
        catch(DateNonexistent & d)
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
            d.setDate( dia , mes , ano );
          }
          catch(DateNonexistent & d)
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
            d.setDate( dia , mes , ano );
          }
          catch(DateNonexistent & d)
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
  Hour h;
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
        h.setHour( hora , min );
      }
      catch(HourNonexistent & d)
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
          h.setHour( hora , min );
        }
        catch(HourNonexistent & d)
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
            h.setHour( hora , min );
          }
          catch(HourNonexistent & d)
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
            h.setHour( hora , min );
          }
          catch(HourNonexistent & d)
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

bool Clinic::altCon()
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
  Doctor med_tmp;
  Doctor *ptr_med = med_tmp.find ( ced , this->list_med );
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
    ptr_med = med_tmp.find ( ced , this->list_med );
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
    cout << "Date inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    }  
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Date d( dia , mes , ano );
  Horario <Doctor , Date > horario ( ptr_med , d );
  horario.print(cout , this->list_con );
  cout << endl << "Insira a hora de início da consulta separadas por um caracter (no formato hh:mm ): ";
  getline( cin , tmp );
  if ( cin.eof() )
  {
    cin.clear();
    return false;
  }
  while (!isHor( tmp ) )
  {
    cout << "Hour inválida. Insira outra: " << endl;
    getline( cin , tmp );
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    }
  }
  istringstream sss(tmp);
  sss >> hora >> espaco >> min;
  Hour h( hora , min );
  Consulta *ptr =  new Consulta ( ptr_med , NULL , d , h , 0);
  int pos = ptr->findPos( this->list_con );
  if ( pos == -1 )
  {
    cout << "Não foi encontrada uma consulta com estas características. A abortar..." << endl;
    delete ptr;
    return false;
  }
  cout << "Insira os novos dados: " << endl;
  if ( this->insCon() == -1 )
  {
    cout << "Erro na actualização da consulta. A abortar..." << endl;
    delete ptr;
    return false;
  }
  delCon( this->list_con , ptr_med , h , d );
  delete ptr;
  return true;
}

bool Clinic::verCon()
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
  Doctor med_tmp;
  Doctor *ptr_med = med_tmp.find ( ced , this->list_med );
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
    ptr_med = med_tmp.find ( ced , this->list_med );
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
    cout << "Date inválida. Insira outra: " << endl;
    getline( cin , tmp );  
    if ( cin.eof() )
    {
      cin.clear();
      return false;
    }
  }
  istringstream ss(tmp);
  ss >> dia >> espaco >> mes >> espaco >> ano;
  Date d( dia , mes , ano );
  cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm ): ";
  Hour h;
  try
  {
    h = getHour();
  }
  catch (EOI &)
  {
    return false;
  }
  Consulta *ptr =  new Consulta ( ptr_med , NULL , d , h , 0);
  int pos = ptr->findPos( this->list_con );
  if ( pos == -1 )
  {
    cout << "Não foi encontrada uma consulta com estas características. A abortar..." << endl;
    delete ptr;
    return false;
  }
	Hour h1 = h + this->list_con.at( pos )->getDur();
	cout << endl << "Dr.(ª) " << this->list_con.at( pos )->getMed()->getName() << " no dia " <<  d << " às " << h << " até ";
	cout << h1  << "com o Sr.(ª) " << this->list_con.at( pos )->getUte()->getName() << endl;
	delete ptr;
  return true;
}

bool Clinic::delPac()
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
  Patient pac_tmp;
  int pos = pac_tmp.findPos( id , this->list_pac );
  while ( pos == -1 )
  {
    cout << "Patient Inexistente.\nInsira o número identificativo do utente : ";
    try
    {
      id = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    pos = pac_tmp.findPos ( id , this->list_pac );
  }
  bool consulta = false;
  for (int i = 0; i < (int) this->list_con.size() ; i++ )
  {
    if ( this->list_con.at(i)->getUte()->getId() == id && this->list_con.at(i)->getEst() == 'm' )
      consulta = true;
  }
  if (consulta)
  {
    cout << "Este utente tem consultas marcadas. A desmarcar..."  << endl;
    this->list_pac.at( pos )->setSis( false );
    for (int i = 0; i < (int) this->list_con.size() ; i++ )
    {
      if ( this->list_con.at(i)->getUte()->getId() == id && this->list_con.at(i)->getEst() == 'm' )
      {
        Hour h( this->list_con.at( i )->getHor() );
        Date d( this->list_con.at( i )->getDat() );
        Doctor * ptr = this->list_con.at(i)->getMed();
        delCon( this->list_con , ptr , h , d );
        i--;
      }
    }
  }
  else this->list_pac.at( pos )->setSis( false );
  
/*  if ( pos > (int)( u.size() / 2 ) )
  {
    vector<Patient *>::iterator it = u.end();
    it--;
    for ( int i = u.size()-1 ; i > pos ; i-- )
      it--;
    u.erase(it);
  }
  else
  {
    vector<Patient *>::iterator it = u.begin();
    for ( int i = 0 ; i < pos ; i++ )
      it++;
    u.erase(it);
  }
  return true;*/
  
  return true;
}
bool Clinic::altPac()
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
  Patient pac_tmp;
  int pos = pac_tmp.findPos( id , this->list_pac );
  while ( pos == -1 )
  {
    cout << "Patient Inexistente.\nInsira o número identificativo do utente : ";
    try
    {
      id = getLong();
    }
    catch (EOI &)
    {
      return false;
    }
    pos = pac_tmp.findPos ( id , this->list_pac );
  }
  
 /* vector<Patient *>::iterator it = u.begin();
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
  this->list_pac.at( pos )->setName( nome );
  this->list_pac.at( pos )->setAdd( mor ) ;
  this->list_pac.at( pos )->setTel( tel );
  this->list_pac.at( pos )->setIns( seg , des , apo );
  return true;
}

Hour getHour()
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
    cout << "Hour inválida. Insira outra: " << endl;
    getline( cin , tmp );  
  }
  istringstream s(tmp);
  s >> hora >> espaco >> min;
  Hour h( hora , min ); 
  return h;
}



bool Clinic::horNCol ( vector<Consulta *> & c , Hour & h , const int & duracao , const Hour & ini ,const Hour & fim )
{
  vector<Consulta *>::iterator it = c.begin();
  Hour h0 = h + duracao;
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
bool Clinic::pagarCon()
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
  Doctor med_tmp;
  Doctor *ptr_med = med_tmp.find ( ced , this->list_med );
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
  	ptr_med = med_tmp.find ( ced , this->list_med );
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
    cout << "Date inválida. Insira outra: " << endl;
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
  Date d( dia , mes , ano );
	cout << "Insira a hora da consulta separadas por um caracter (no formato hh:mm ): ";
  Hour h;
  try
 	{
 	  h = getHour();
  }
  catch (EOI &)
  {
    return false;
  }
	Consulta *ptr =  new Consulta ( ptr_med , NULL , d , h , 0);
  int pos = ptr->findPos( this->list_con );
 	if ( pos == -1 )
  {
    cout << "Não foi encontrada uma consulta com estas características. A abortar..." << endl;
    delete ptr;
    return false;
  }
  if (  this->list_con.at( pos )->getEst() != 'p' || this->list_con.at( pos )->getEst() != 'P' )
  {
    this->list_con.at( pos )->setEst('p' );
    cout << "Consulta Efectuada e paga." << endl;
  }
  else cout << "Esta consulta já foi paga anteriormente." << endl;
  return true;
}

template<class Comparable> std::vector <Comparable *> find_Id( const std::vector<Comparable *> & u )
{
  string nome;
  vector<Comparable *> lista;
	cout<<"Introduza o nome do utente:";
	getline( cin , nome );	
	if ( cin.eof() )
	{
	  cin.clear();
	  return lista;
	}
	for ( int i = 0; i < (int) u.size(); i++ )
	  if  ( u.at( i )->getName() == nome )
      lista.push_back( u.at( i ) );
  return lista;
}


template <class Comparable>void listar( const vector<Comparable *> & v)
{
  for ( int i = 0; i< (int) v.size() ; i++ )
   if ( v.at( i )->getSis() )
    cout << *( v.at( i ) ) << endl;
}


template std::vector<Patient *> find_Id<Patient>( const std::vector<Patient *> & );
template std::vector<Doctor *> find_Id<Doctor>( const std::vector<Doctor *> & );
template void listar<Patient> ( const std::vector<Patient *> & );
template void listar<Doctor> ( const std::vector<Doctor *> & );


void Clinic::load()
{
  this->files.loadEsp( this->list_esp ); 
  this->files.loadMed( this->list_med , this->list_esp ); 
  this->files.loadPac( this->list_pac ); 
  this->files.loadCon( this->list_con , this->list_pac , this->list_med ); 
}

void Clinic::save()
{
  this->files.savEsp( this->list_esp ); 
  this->files.savMed( this->list_med ); 
  this->files.savPac( this->list_pac ); 
  this->files.savCon( this->list_con ); 
}
