#include "headers/FileHandling.h"

bool savCon ( string f , const vector<Consulta *> & c)
{
ofstream fout( f.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << f << "." << endl;
    return false;
  }
  for (int i = 0 ; i< (int) c.size() ; i++ )
  {
    fout << c.at( i )->getMed()->getCed() << "|" << c.at( i )->getUte()->getId() << "|";
    fout << c.at( i )->getDat().getDia() << "/" << c.at( i )->getDat().getMes() << "/" << c.at( i )->getDat().getAno();
    fout << "|" << c.at( i )->getHor().getHor() << ":" << c.at( i )->getHor().getMin();
    fout << "|" << c.at( i )->getPre() << "|" << c.at( i )->getDur();
    fout << "|" << c.at( i )->getEst() <<endl;
  }
  fout.flush();
  return true;
}

bool savPac ( string f , const vector<Utente *> & u )
{
  ofstream fout( f.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << f << "." << endl;
    return false;
  }
  for (int i = 0 ; i< (int) u.size() ; i++ )
  {
    fout << u.at( i )->getId() << "|" << u.at( i )->getNome() << "|";
    fout << u.at( i )->getTel() << "|" << u.at( i )->getMor() << "|" << u.at( i )->getSeg().getSeg();
    fout << "|" << u.at( i )->getSeg().getDes() << "|" << u.at( i )->getSeg().getApo()<< "|" << u.at( i )->getSis() << endl;
  }
  fout.flush();
  return true;
}

bool savEsp ( string f , const vector<Especialidade *> & e )
{
  ofstream fout( f.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << f << "." << endl;
    return false;
  }
  for (int i = 0 ; i< (int) e.size() ; i++ )
    fout << e.at( i )->getNom() << endl;
  fout.flush();
  return true;  
}

bool savMed ( string f , const vector<Medico *> & u )
{
  ofstream fout( f.c_str() );
  if ( fout.fail() )
  {
    cerr << "Não conseguiu escrever no ficheiro " << f << "." << endl;
    return false;
  }
  for (int i = 0 ; i< (int) u.size() ; i++ )
  {
    fout << u.at( i )->getCed() << "|" << u.at( i )->getNome() << "|";
    fout << u.at( i )->getTel() << "|" << u.at( i )->getEspe()->getNom() << "|"; 
    fout << u.at( i )->getIni().getHor() << ":" << u.at( i )->getIni().getMin() << "|";
    fout << u.at( i )->getFim().getHor() << ":" << u.at( i )->getFim().getMin() << "|";
    fout << u.at( i )->getDur() << "|" << u.at( i )->getDurM() << "|" << u.at( i )->getSis() << endl;
  }
  fout.flush();
  return true;
}

bool criaFile(string f)
{
  ifstream fi(f.c_str());
  if ( fi.fail() )
  {
    ofstream fo(f.c_str());
    if ( fo.fail() )
    {
      fo.close();
      return false;  
    }
    fo.close();
    return true;
  }
  else
  {
    fi.close();
    return true;
  }
}
bool addMed(fstream &f,const Medico &m)
{
  string line;
  unsigned long ced;
  while(!f.eof())
  {
    getline(f,line,'|');
    istringstream is(line);
    is >> ced;
    if (ced == m.getCed())
      return false;
    getline(f,line);
  }
  f.clear();
  f.seekp(0,ios_base::end);
  f << m.getCed() << "|" << m.getNome() << "|" << m.getTel() << "|" <<m.getEspe()->getNom() << "|";
  f << m.getIni().getHor() << ":" << m.getIni().getMin() << "|" << m.getFim().getHor() << ":" << m.getFim().getMin() << "|" << m.getDur() << "|" << m.getSis() << endl;
  f.flush();
  return true;
}
bool delMed(fstream &f, const Medico &m)
{
  string line;
  unsigned long ced;
  while(!f.eof())
  {
    size_t pos=f.tellg();
    getline(f,line,'|');
    istringstream is(line);
    is >> ced;
    if (ced == m.getCed())
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
bool addPac(fstream &f, const Utente &u)
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
  f <<u.getId()<<"|"<< u.getNome() << "|" << u.getTel() << "|" <<u.getMor() << "|" << u.getSeg().getSeg() << "|" << u.getSeg().getDes() << "|" << u.getSeg().getApo() << "|" << u.getSis() << endl;
  f.flush();
  return true;
}
bool delPac(fstream &f, const Utente &u)
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
bool addCon(fstream &, const Consulta &){return false;}
bool delCon(fstream &, const Consulta &){return false;}
