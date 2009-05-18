#include "classes/headers/MemoryHandling.h"
#include <vector>
#include <cstdlib>

using namespace std;

vector<Medico *> lista_med;
vector<Utente *> lista_pac;
vector<Especialidade *> lista_esp;
vector<Consulta *> lista_con;
  string file_med = "medico.txt",file_pac="utentes.txt",file_esp="especialidade.txt";
void Menu();
void menu_med();
int main()
{

  cout << "Medigai\nMedical Management for Linux Lovers.\n\n\n\n";

  if ( criaFile( file_med ) )
    fstream med( file_med.c_str() );
  else
  {
    cerr << "Erro: Verifique permissões no directório de execução."<<endl;
    return -1;
  }
  if ( criaFile( file_esp) )
    fstream med( file_esp.c_str() );
  else
  {
    cerr << "Erro: Verifique permissões no directório de execução."<<endl;
    return -1;
  }
  if ( criaFile( file_pac ) )
    fstream med( file_pac.c_str() );
  else
  {
    cerr << "Erro: Verifique permissões no directório de execução."<<endl;
    return -1;
  }
  char opcao;
  carregaEsp( file_esp , lista_esp );
  carregaMed( file_med , lista_med , lista_esp );
  listar( lista_med );
  cout << endl;
  listar( lista_esp );
  carregaPac ( file_pac , lista_pac );
  cout << endl;
  listar( lista_pac );
  cout << endl;
  Menu();
  while ( ! cin.eof() ) 
  {
    cin >> opcao;
    if ( ! cin.eof() && isdigit( opcao ) )
    {
      switch (opcao)
      {
        case '1': menu_med();
                  Menu();
                  cin.clear();
                  break;
        case '2': cout << "Insira os Dados do Utente.\n";
                  insPac( lista_pac );
                  listar( lista_pac );
                  Menu();
                  break;
        case '3': cout << "A guardar tudo...\n";
                  savPac ( file_pac , lista_pac );
                  savMed ( file_med , lista_med );
                  savEsp ( file_esp , lista_esp );
                  Menu();
                  break;
        default: cout << "\nOpção desconhecida.\n\n";
                 Menu();
                 break;
      }
    }

  }
  return 0;
}





void Menu()
{
  cout << "Menu:\nInsira o número da opção desejada.\n1. Corpo Clínico\n2. Gestão de Utentes\n3. Gestão de Consultas\n";
  cout << "CRTL-D para cancelar.\n";
}

void Menu_med()
{
  cout << "Gestão do Corpo Clínico:\nInsira o número da opção desejada.\n";
  cout << "1. Adicionar Médico\n2. Eliminar Médico\n3. Visualisar os médicos\n";
  cout << "CRTL-D para cancelar.\n";
}

void menu_med()
{
  char opcao;
  Menu_med();
  while ( ! cin.eof() ) 
  {
    cin >> opcao;
    if ( ! cin.eof() && isdigit( opcao ) )
    {
      switch (opcao)
      {
        case '1': cout << "Insira os Dados do Médico.\n";
                  insMed( lista_med , lista_esp );
                  listar( lista_med );
                  Menu_med();
                  break;
        case '2': cout << "Insira os Dados do Utente.\n";
                  Menu_med();
                  break;
        case '3': cout << "A guardar tudo...\n";
                  savPac ( file_pac , lista_pac );
                  savMed ( file_med , lista_med );
                  savEsp ( file_esp , lista_esp );
                  Menu_med();
                  break;
        default: cout << "\nOpção desconhecida.\n\n";
                 Menu();
                 break;
      }
    }
}
}

template <class Comparable>void listar( const vector<Comparable *> & v)
{
  for ( int i = 0; i< (int) v.size() ; i++ )
   cout << *( v.at( i ) ) << endl;
}