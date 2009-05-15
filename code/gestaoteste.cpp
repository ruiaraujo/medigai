#include "classes/headers/FileHandling.h"
#include <vector>

using namespace std;

vector<Medico *> lista_med;
vector<Utente *> lista_pac;
vector<Especialidade *> lista_espe;

Especialidade * findEsp(string);
void insMed();
bool carregaEsp(string);
Medico * findMed(unsigned long);
Medico * findMed(const Medico &);
int findMedPos(unsigned long);
int findMedPos(const Medico &);


int main()
{

  cout << "Medigai\nMedical Management for Linux Lovers.\n\n\n\n";
  string file_med = "medico.txt",file_pac="utentes.txt",file_espe="especialidade.txt";
  if (criaFile(file_med))
    fstream med(file_med.c_str());
  else
  {
    cerr << "Erro: Verifique permissões no directório de execução."<<endl;
    return -1;
  }
  int opcao;
  cout << "Menu:\nInsira o número da opção desejada.\n1. Corpo Clínico\n2. Gestão de Utentes\n3. Gestão de Consultas\n";
  cout << "CRTL-D para cancelar.\n";
  while (!cin.eof())
  {
    cin >> opcao;
    if (opcao!=EOF)
    {
      switch (opcao)
      {
        case 1: cout << "Opçao certa.\n";
                break;
        default:
                cout << "Opção desconhecida.\n";
                cout << "Menu:\nInsira o número da opção desejada.\n1. Corpo Clínico\n2. Gestão de Utentes\n3. Gestão de Consultas\n";
                cout << "CRTL-D para cancelar.\n";
                break;
      }
    }
  }
  return 0;
}

void insMed()
{
  string nome,tel,espe;
  int duracao;
  int hora_i,hora_f, min_i, min_f;
  cout << "Insira o nome do(a) médico(a): ";
  long cedula;
  getline(cin, nome);
  cout << "Insira o telefone do(a) médico(a): ";
  getline(cin, tel);
  cout << "Insira a especialidade do(a) médico(a): ";
  getline(cin, espe);
  Especialidade *esp = findEsp(espe);
  if (esp==NULL)
  {
    esp = new Especialidade;
    esp->setNom(espe);  
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
  Hora inicio(hora_i, min_i);
  Hora fim(hora_f, min_f);
  Medico a(nome, tel, duracao, cedula);
  a.setEspe(esp);
  Medico *ptr = findMed(a);
  if (ptr == NULL)
  {
    ptr = new Medico (nome, tel, duracao, cedula);
    ptr->setIni(inicio);
    ptr->setFim(fim);
    ptr->setEspe(esp);
    lista_med.push_back(ptr);
  }
  else
  {
    cout << "Já existe um médico com esse dados deseja alterá-los? (S/N)\n";
    char resposta;
    while (resposta!='S' && resposta!='N')
    {
      cin >> resposta;
      cout << "Insira uma resposta vállida. S para sim e N para não.\n";
    }
    if (resposta == 'S' )
    {
      int pos = findMedPos(a);
      lista_med.at(pos)->setNome(nome);
      lista_med.at(pos)->setTel(tel);
      lista_med.at(pos)->setDur(duracao);
      lista_med.at(pos)->setIni(inicio);
      lista_med.at(pos)->setFim(fim);
      lista_med.at(pos)->setEspe(esp);
    }
  }
}

int findMedPos(unsigned long ced)
{
  for(int i = 0; i < (int)lista_med.size(); i++)
  {
      if (ced==lista_med.at(i)->getCed())
        return i;
  }
  return -1;
}
int findMedPos(const Medico &m)
{
  for(int i = 0; i < (int)lista_med.size(); i++)
  {
      if (m.getCed()==lista_med.at(i)->getCed())
        return i;
  }
  return -1;
}

Medico * findMed(const Medico &m)
{
  for(int i = 0; i < (int)lista_med.size(); i++)
  {
      if (m.getCed()==lista_med.at(i)->getCed())
        return lista_med.at(i);
  }
  return NULL;
}
Medico * findMed(unsigned long ced)
{
  for(int i = 0; i < (int)lista_med.size(); i++)
  {
      if (ced==lista_med.at(i)->getCed())
        return lista_med.at(i);
  }
  return NULL;
}
Especialidade * findEsp(string m)
{
  for(int i=0; i < (int)lista_espe.size();i++)
  {
    if (m==lista_espe.at(i)->getNom())
      return lista_espe.at(i);
  }
  return NULL;
}

bool carregaEsp(string m)
{
  ifstream fin(m.c_str());
  if (fin.fail())
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
    string line;
    while (!fin.eof())
    {
      getline(fin, line);
      if (!line.empty())
        if (findEsp(m)==NULL)
        {
          Especialidade *a = new Especialidade(line);
          lista_espe.push_back(a);
          a->setNom(m);
        }
    }
  return true;
}

bool carregaMed(string m)
{
  string nome, tel, espe, tmp;
  int duracao;
  int hora_i,hora_f, min_i, min_f;
  long ced=-1;
  char espaco;
  ifstream fin(m.c_str());
  if (fin.fail())
  {
    cerr << "Ficheiro não encontrado." << endl;
    return false;
  }
    string line;
    while (!fin.eof())
    {
      getline(fin, tmp, '|');
      if (!tmp.empty())
      {
        istringstream ss(tmp);
        ss>>ced;
      }
      fin.get();
      getline(fin, nome, '|');
      fin.get();
      getline(fin, tel, '|');
      fin.get();
      getline(fin, espe, '|');
      fin.get();
      getline(fin, tmp , '|');
      fin.get();
    }
  return true;





}
