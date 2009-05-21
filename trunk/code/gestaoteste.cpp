#include "classes/headers/MemoryHandling.h"
#include <vector>
#include <cstdlib>

using namespace std;

vector<Medico *> lista_med;
vector<Utente *> lista_pac;
vector<Especialidade *> lista_esp;
vector<Consulta *> lista_con;

string file_med = "medico.txt",file_pac="utentes.txt",file_esp="especialidade.txt";
string file_con = "consultas.txt";

void Menu();
void menu_med();
void Menu_med();
void Menu_con();
void menu_con();

int main()
{

  cout << "Medigai\nMedical Management for Linux Lovers.\n\n\n\n";

  if ( !criaFile( file_med ) || !criaFile( file_pac) || !criaFile( file_esp) || !criaFile( file_con) )
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
  carregaCon ( file_con , lista_med , lista_pac , lista_con );
  listar( lista_con );
  cout << endl ;
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
                  cin.clear();
                  break;
        case '3': menu_con();
                  Menu();
                  cin.clear();
                  break;
        case '4': cout << "A guardar tudo...\n";
                  savPac ( file_pac , lista_pac );
                  savMed ( file_med , lista_med );
                  savEsp ( file_esp , lista_esp );
                  savCon ( file_con , lista_con );
                  carregaEsp( file_esp , lista_esp );
                  carregaMed( file_med , lista_med , lista_esp );
                  listar( lista_med );
                  cout << endl;
                  listar( lista_esp );
                  carregaPac ( file_pac , lista_pac );
                  cout << endl;
                  listar( lista_pac );
                  cout << endl;
                  carregaCon ( file_con , lista_med , lista_pac , lista_con );
                  listar( lista_con );
                  Menu();
                  cin.clear();
                  break;
        default: cout << "\nOpção desconhecida.\n\n";
                 Menu();
                 cin.clear();
                 break;
      }
    }

  }
  return 0;
}





void Menu()
{
  cout << "Menu:\nInsira o número da opção desejada.\n1. Corpo Clínico\n2. Gestão de Utentes\n";
  cout << "3. Gestão de Consultas\n4. Guardar as alterações\n";
  cout << "CRTL-D para sair.\n";
}

void Menu_med()
{
  cout << "Gestão do Corpo Clínico:\nInsira o número da opção desejada.\n";
  cout << "1. Adicionar Médico\n2. Eliminar Médico\n3. Visualisar os médicos\n";
  cout << "CRTL-D para voltar ao menu anterior.\n";
}

void Menu_con()
{
  cout << "Gestão de Consultas:\nInsira o número da opção desejada.\n";
  cout << "1. Marcar Consultas\n2. Desmarcar Consultas\n3. Visualisar o horário\n";
  cout << "CRTL-D para voltar ao menu anterior.\n";

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
                  cin.clear();
                  break;
        case '2': cout << "Insira a cédula do médico.\n";
                  long cedula;
                  cin >> cedula;
                  delMed ( cedula , lista_med );
                  Menu_med();
                  cin.clear();
                  break;
        case '3': cout << "Lista de Médicos activos\n";
                  listar ( lista_med );
                  cout << endl;
                  Menu_med();
                  cin.clear();
                  break;
        default: cout << "\nOpção desconhecida.\n\n";
                 Menu_med();
                 cin.clear();
                 break;
      }
    }
  }
}

void menu_con()
{
  char opcao;
  Menu_con();
  while ( ! cin.eof() ) 
  {
    cin >> opcao;
    if ( ! cin.eof() && isdigit( opcao ) )
    {
      switch (opcao)
      {
        case '1': cout << "Insira os Dados da Consulta.\n";
                  insCon( lista_med , lista_pac , lista_con );
                  listar ( lista_con );
                  Menu_con();
                  cin.clear();
                  break;
        case '2': cout << "Insira os dados da Consulta:" << endl;
                  delCon( lista_med , lista_con );
                  Menu_con();
                  cin.clear();
                  break;        
        case '3': cout << "Lista de Consultas:" << endl;
                  listar ( lista_con );
                  Menu_con();
                  cin.clear();
                  break;                  
        default: cout << "\nOpção desconhecida.\n\n";
                 Menu_con();
                 cin.clear();
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
