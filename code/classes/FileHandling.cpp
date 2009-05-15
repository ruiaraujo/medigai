#include "headers/FileHandling.h"


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
  f <<m.getCed()<<"|"<< m.getNome() << "|" << m.getTel() << "|" <<m.getEspe()->getNom() << "|"  << endl;
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
  f <<u.getId()<<"|"<< u.getNome() << "|" << u.getTel() << "|" <<u.getMor() << "|" << u.getSeg().getSeg() << "|" << u.getSeg().getDes() << "|" << u.getSeg().getApo()<< endl;
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
