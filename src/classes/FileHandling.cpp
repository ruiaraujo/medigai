#include "FileHandling.h"
#include <cstdlib>
#include <vector>
#include <sstream>

using std::string;
using std::fstream;
using std::endl;
using std::cerr;
using std::vector;
using std::cout;
using std::ios_base;
using std::istringstream;
using std::ofstream;
using std::ifstream;

FileHandling::FileHandling( std::string file_m , std::string file_p, std::string file_e, std::string file_c):
                                file_med( file_m ) , file_pac( file_p ), 
                                file_esp( file_e ) , file_con( file_c )
{
  if ( existFile( file_m ) == 'n' )
  {
    std::cerr << "Unable to write to file called " << file_m << ". Aborting..." << endl;
    exit(1);
  }
  if ( existFile( file_p ) == 'n' )
  {
    std::cerr << "Unable to write to file called " << file_p << ". Aborting..." << endl;
    exit(1);
  }
  if ( existFile( file_e ) == 'n' )
  {
    std::cerr << "Unable to write to file called " << file_e << ". Aborting..." << endl;
    exit(1);
  }
  if ( existFile( file_c ) == 'n' )
  {
    std::cerr << "Unable to write to file called " << file_c << ". Aborting..." << endl;
    exit(1);
  }
}


bool FileHandling::loadEsp( std::vector<Specialty *> & list_esp )
{
  ifstream fin( this->file_esp.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  list_esp.clear();
  string line;
  while ( ! fin.eof() )
  {
    getline( fin, line );
    if ( ! line.empty() )
    {
      Specialty esp_tmp(line);
      if ( esp_tmp.find ( list_esp ) == NULL )
      {
        Specialty * a = new Specialty( line );
        list_esp.push_back( a );
      }
    }
  }
  fin.close();
  return true;
}

bool FileHandling::loadCon( std::vector<Consulta * > & list_con , std::vector<Patient *> & list_pac ,
                                                   std::vector<Doctor * > & list_med )
{
  unsigned long ced , id;
  int dia, mes , ano, duracao , hora , min;
  float preco;
  char estado;
  string tmp;
  ifstream fin(  this->file_con.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  list_con.clear();
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
      Doctor med_tmp;
      Doctor *ptr_m = med_tmp.find ( ced , list_med );
      Patient pac_tmp;
      Patient *ptr_u = pac_tmp.find ( id , list_pac );
      if ( ptr_u != NULL && ptr_m != NULL )
      {
        Date d( dia , mes , ano );
        Hour h( hora , min );
        Consulta *ptr = new Consulta( ptr_m , ptr_u , d , h , preco );
        ptr->setEst( estado );
        ptr->setDur( duracao );
        list_con.push_back(ptr);
      }
    }
  }
  fin.close();
  return true;
}

bool FileHandling::loadMed ( std::vector<Doctor * > & list_med , std::vector<Specialty *> & list_esp )
{
  string nome, tel, espe, tmp;
  int duracao, dur_max;
  int hora_i,hora_f, min_i, min_f;
  long ced;
  char espaco;
  ifstream fin( this->file_med.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  list_med.clear();
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
      Specialty espe_tmp(espe);
      Specialty *esp = espe_tmp.find( list_esp );
      if ( esp == NULL )
      {
        esp = new Specialty( espe );
        list_esp.push_back( esp );
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
      getline( fin , tmp , '|' );
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
        Doctor *ptr;
        ptr = new Doctor ( nome , tel , duracao , ced );
        Hour fim( hora_f , min_f );
        Hour inicio( hora_i , min_i );
        ptr->setDurM( dur_max );
        ptr->setIni( inicio );
        ptr->setFim( fim );
        ptr->setEspe( esp );
        ptr->insOrd( list_med );
      }
    }
  fin.close();
  return true;
}

bool FileHandling::loadPac( std::vector<Patient *> & list_pac )
{
  string nome, tel, seg, mor, tmp;
  int desconto;
  long id, apolice, ultimo = 0;
  bool sistema;
  ifstream fin( this->file_pac.c_str() );
  if ( fin.fail() )
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
  list_pac.clear();
  while ( !fin.eof() )
  {
    getline( fin , tmp , '|' ); 
    if (!fin.eof())
    {
      if ( !tmp.empty() )
      {
        istringstream ss ( tmp );
        ss >> id;
        if ( id >= ultimo ) ultimo = id + 1;
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
        Patient *ptr = new Patient ( nome , tel , mor, seg, desconto, apolice, id);
        ptr->setUN( ultimo );
        ptr->setSis( sistema );
        ptr->insOrd( list_pac );
      }
    }
  }
  fin.close();
  return true;
}
void FileHandling::savCon ( const vector<Consulta *> & c)
{
   ofstream fout( this->file_con.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << this->file_con << "." << endl;
  }
  else
  {
    for (int i = 0 ; i< (int) c.size() ; i++ )
    {
      fout << c.at( i )->getMed()->getId() << "|" << c.at( i )->getUte()->getId() << "|";
      fout << c.at( i )->getDat().getDate() << "|" << c.at( i )->getHor().getHour();
      fout << "|" << c.at( i )->getPre() << "|" << c.at( i )->getDur();
      fout << "|" << c.at( i )->getEst() <<endl;
    }
    fout.close();
  }
}

void FileHandling::savPac ( const vector<Patient *> & u )
{
  ofstream fout( this->file_pac.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << this->file_pac << "." << endl;
  }
  else
  {
    for (int i = 0 ; i< (int) u.size() ; i++ )
    {
      fout << u.at( i )->getId() << "|" << u.at( i )->getName() << "|";
      fout << u.at( i )->getTel() << "|" << u.at( i )->getAdd() << "|" << u.at( i )->getIns().getIns();
      fout << "|" << u.at( i )->getIns().getDis() << "|" << u.at( i )->getIns().getNum()<< "|" << u.at( i )->getSis() << endl;
    }
    fout.flush();
  }
}

void FileHandling::savEsp ( const vector<Specialty *> & e )
{
  ofstream fout( this->file_esp.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << this->file_esp << "." << endl;
  }
  else
  {
    for (int i = 0 ; i< (int) e.size() ; i++ )
      fout << e.at( i )->getName() << endl;
    fout.close();
  }
}
void FileHandling::savMed ( const vector<Doctor *> & u )
{
  ofstream fout( this->file_med.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << this->file_med << "." << endl;
  }
  else
  {
    for (int i = 0 ; i< (int) u.size() ; i++ )
    {
      fout << u.at( i )->getId() << "|" << u.at( i )->getName() << "|";
      fout << u.at( i )->getTel() << "|" << u.at( i )->getEspe()->getName() << "|"; 
      fout << u.at( i )->getIni().getHor() << ":" << u.at( i )->getIni().getMin() << "|";
      fout << u.at( i )->getFim().getHor() << ":" << u.at( i )->getFim().getMin() << "|";
      fout << u.at( i )->getDur() << "|" << u.at( i )->getDurM() << "|" << u.at( i )->getSis() << endl;
    }
    fout.close();
  }
}

char FileHandling::existFile( string f )
{
  ifstream fi( f.c_str() );
  if ( fi.fail() )
  {
    ofstream fo( f.c_str() );
    if ( fo.fail() )
    {
      fo.close();
      return 'n';  
    }
    fo.close();
    return 'c';
  }
  else
  {
    fi.close();
    return 'e';
  }
}
bool addMed(fstream &f,const Doctor &m)
{
  string line;
  unsigned long ced;
  while(!f.eof())
  {
    getline(f,line,'|');
    istringstream is(line);
    is >> ced;
    if (ced == m.getId())
      return false;
    getline(f,line);
  }
  f.clear();
  f.seekp(0,ios_base::end);
  f << m.getId() << "|" << m.getName() << "|" << m.getTel() << "|" <<m.getEspe()->getName() << "|";
  f << m.getIni().getHor() << ":" << m.getIni().getMin() << "|" << m.getFim().getHor() << ":" << m.getFim().getMin() << "|" << m.getDur() << "|" << m.getSis() << endl;
  f.flush();
  return true;
}
bool delMed(fstream &f, const Doctor &m)
{
  string line;
  unsigned long ced;
  while(!f.eof())
  {
    size_t pos=f.tellg();
    getline(f,line,'|');
    istringstream is(line);
    is >> ced;
    if (ced == m.getId())
    { 
      f.seekp(pos);
      f<<endl;
    return true;
    }
    getline(f,line);
  }
  return false;
}
bool delMed(fstream &f, unsigned long id)
{
  string line;
  unsigned long ced;
  while(!f.eof())
  {
    size_t pos=f.tellg();
    getline(f,line,'|');
    istringstream is(line);
    is >> ced;
    if (ced == id)
    { 
      f.seekp(pos);
      f<<endl;
    return true;
    }
    getline(f,line);
  }
  return false;
}
bool addPac(fstream &f, const Patient &u)
{
  string line;
  unsigned long id;
  while(!f.eof())
  {
    getline(f,line,'|');
    istringstream is(line);
    is >> id;
    if (id == u.getId())
      return false;
    getline(f,line);
  }
  f.clear();
  f.seekp(0,ios_base::end);
  f <<u.getId()<<"|"<< u.getName() << "|" << u.getTel() << "|" <<u.getAdd() << "|" << u.getIns().getIns() << "|" << u.getIns().getDis() << "|" << u.getIns().getNum() << "|" << u.getSis() << endl;
  f.flush();
  return true;
}
bool delPac(fstream &f, const Patient &u)
{
  string line;
  unsigned long id;
  while(!f.eof())
  {
    size_t pos=f.tellg();
    getline(f,line,'|');
    istringstream is(line);
    is >> id;
    if (id == u.getId())
    { 
      f.seekp(pos);
      f<<endl;
    return true;
    }
    getline(f,line);
  }
  return false;
}
bool delPac(fstream &f, unsigned long id)
{
  string line;
  unsigned long ced;
  while(!f.eof())
  {
    size_t pos=f.tellg();
    getline(f,line,'|');
    istringstream is(line);
    is >> ced;
    cout << ced << endl;
    if (ced == id)
    { 
      f.seekp(pos);
      f<<endl;
    return true;
    }
    getline(f,line);
  }
  return false;
}
