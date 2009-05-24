#include "classes/headers/MemoryHandling.h"
#include "classes/headers/horario.h"
#include <vector>
#include <cstdlib>
#include<iostream>

using namespace std;

//Variaveis globais
string file_med = "medico.txt",file_pac="utentes.txt";
string file_esp="especialidade.txt",file_con = "consultas.txt"; //nome dos ficheiros para leitura
vector<Medico *> lista_med;
vector<Utente *> lista_pac;
vector<Especialidade *> lista_esp;
vector<Consulta *> lista_con;
bool alteracoes = 0;


void menu_med();
void menu_utente();
void menu_consulta();



//Texto dos Menus
void Menu_med();
void Menu_consulta();
void Menu_utente();
void main_menu();
void logotipo();


int main()
{
  string lixo;
  if ( !criaFile( file_med ) || !criaFile( file_pac) || !criaFile( file_esp) || !criaFile( file_con) )
  {
    cerr << "Erro: Verifique permissões no directório de execução."<<endl;
    return -1;
  }
  carregaEsp( file_esp , lista_esp );
  carregaMed( file_med , lista_med , lista_esp );
  carregaPac ( file_pac , lista_pac );
  carregaCon ( file_con , lista_med , lista_pac , lista_con );
  main_menu();
  char opcao;
	cin.clear();
  while( !cin.eof() )
  {
    cin>>opcao;
    if ( !cin.eof() && isdigit(opcao) )
    {
      switch (opcao)
      {
        case '1': menu_med();
                  cin.clear();
                  main_menu();
                  break;
        case '2': menu_utente();
                  cin.clear();
                  main_menu();
	                break;
        case '3': menu_consulta();
                  cin.clear();
                  main_menu();
		              break;
	      case '4': system( "clear" );
	                cout << "A guardar tudo...\n";
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
                  getline( cin , lixo );
		              cout << "Enter para continuar...";
		              cin.get();
		              main_menu();
		              break;
        default:  cout << "\nOpção desconhecida.\n\n";
                  cin.clear();
                  main_menu();
		              break;
      }
    }
  }
  if ( alteracoes )
  {
    cout << "Provalvelmente há alterações não guardadas. Deseja guardá-las agora(S/N)?"<<endl;
    cin >> opcao;
    while (opcao != 'S' && opcao != 'N' && opcao != 's' && opcao != 'n' )
    {
      cout << "Opção desconhecida. Insira outra." << endl;
      cin >> opcao;
    }
    if ( opcao == 'S' || opcao == 's' )
    {
      cout << "A guardar tudo...\n";
      savPac ( file_pac , lista_pac );
      savMed ( file_med , lista_med );
      savEsp ( file_esp , lista_esp );
      savCon ( file_con , lista_con );
    }
  }
return 0;
}

void logotipo(){

cout<<"******************************************************************************"<<endl;
cout<<"*    __          __   ____   ________  ( )  _______        ______       ( )  *"<<endl;
cout<<"*   |  \\        /  | |____| |  __    |  _  |  _____|      /  __  \\       _   *"<<endl;
cout<<"*   |  |\\      /|  | |____  | |  |   | | | | |           /  /  \\  \\     | |  *"<<endl;
cout<<"*   |  | \\    / |  | |____| | |  |   | | | | |_____     /  /____\\  \\    | |  *"<<endl;
cout<<"*   |  |  \\  /  |  | |____  | |__|   | | | | |_____|   /  /______\\  \\   | |  *"<<endl;
cout<<"*   |__|   \\/   |__| |____| |________| |_| |_______|  /__/        \\__\\  |_|  *"<<endl;
cout<<"*                                                                            *"<<endl; 
cout<<"*                 Medical Management for Linux Lovers.                       *"<<endl;
cout<<"*                                                                            *"<<endl;
cout<<"******************************************************************************"<<endl;

}

void main_menu()
{
  system("clear");
  logotipo();
  cout << "Menu:\n\nInsira o número da opção desejada:\n\n1. Corpo Clínico\n2. Gestão de Utentes\n";
  cout << "3. Gestão de Consultas\n4. Guardar as alterações\n";
  cout << "Pressione CRTL-D para sair.\n";
}


void Menu_med()
{
  system("clear");
  logotipo();
  cout << "\n\nGestão do Corpo Clínico:\n\nInsira o número da opção desejada.\n\n";
  cout << "1. Adicionar Médico\n2. Eliminar Médico\n3. Visualisar os médicos\n4. Visualizar id\n";
  cout << "CRTL-D para voltar ao menu anterior.\n";
}
void menu_med()
{
  Menu_med();
  char op;
  while ( !cin.eof() )
  {
    cin>>op;
    if ( ! cin.eof() && isdigit( op ) )
    {
      switch(op)
      {
        case '1': cout << "Insira os Dados do Médico.\n";
                  cin.clear();
		              if ( insMed( lista_med , lista_esp ) != -1) alteracoes = true;
                  listar( lista_med );
                  Menu_med();
                  break;
        case '2': cout << "Insira a cédula do médico.\n";
                  cin.clear();
		              long cedula;
                  cin >> cedula;
                  while ( !cin.good() )
                  {
                    string lixo;
                    cin.clear();
                    getline ( cin , lixo );
                    cout << "Input inválido. Insira outro preço: ";
                    cin >> cedula;
                  }
                  if ( delMed ( cedula , lista_med ) ) alteracoes = true;
                  Menu_med();
                  break;
        case '3': listar ( lista_med );
                  cout << endl;
                  Menu_med();
                  break;
        case '4': cin.clear();
                  unsigned long id;
	                id = find_id_med(lista_med);
	                if ( id == 0 )
	                  cout << "\nNão foi encontrada um médico com esse nome.\n";
	                else
	                  cout << "\nId:" << id << endl;
	                break;
	                Menu_med();
	      default:  cout << "\nOpção desconhecida.\n\n";
		              Menu_med();
		              break;
      }
	  }
  }
}

void Menu_consulta()
{
  system("clear");
  logotipo();
  cout << "Menu:\n\nInsira o numero da opção desejada." << endl << endl;
  cout << "1. Marcar Consulta\n2. Alterar Consulta\n3. Desmarcar Consulta" << endl;
  cout << "4. Visualizar Horario\n5. Visualizar Consultas\n6. Ver Consulta\nCRTL-D para voltar ao menu anterior.\n";
}

void menu_consulta()
{
  cin.clear();
  Menu_consulta();  
  char opcao;
  while ( ! cin.eof() ) 
  {
    cin >> opcao;
    if ( ! cin.eof() && isdigit( opcao ) )
    {
      switch (opcao)
      {
        case '1': cout << "Insira os Dados da Consulta.\n";
                  if ( insCon( lista_med , lista_pac , lista_con ) != -1 ) alteracoes = true;
                  listar ( lista_con );
                  Menu_consulta();
                  cin.clear();
                  break;
        case '2': altCon(lista_con, lista_pac, lista_med);
		              Menu_consulta();
		              cin.clear();
		              break;        
        case '3': cout << "Insira os dados da Consulta:" << endl;
                  if ( delCon( lista_med , lista_con ) ) alteracoes = true;
                  Menu_consulta();
                  cin.clear();
                  break;       
	      case '4': Menu_consulta();
	                break;
        case '5': cout << "Lista de Consultas:" << endl;
                  listar ( lista_con );
                  cin.clear();
		              Menu_consulta();
                  break;  
	     case '6' : ver_Con(lista_con, lista_med);
		              cin.clear();
		              Menu_consulta();
		              break;                 
        default: cout << "\nOpção desconhecida.\n\n";
                 Menu_consulta();
                 cin.clear();
                 break;
      }
    }
  }
  cin.clear();
}

void Menu_utente()
{
  system("clear");
  logotipo();
  cout << "Menu:\n\nInsira o número da opção desejada:\n\n1. Adicionr Utente\n2. Eliminar Utente\n3. Visualizar Utentes\n4. Alterar Utente\n5. Visualizar Id.\n Pressione CRTL-D para voltar ao menu anterior.";
}

void menu_utente()
{
  Menu_utente();
  char op;
  cin.clear();
	while ( !cin.eof() )
	{
	  cin >> op;
		if ( ! cin.eof() && isdigit( op ) )
    {
			switch(op)
			{
        case '1': insPac(lista_pac);
                  Menu_utente();
                  cin.clear();
                  break;
        case '2': delPac( lista_pac );
							    Menu_utente();
							    cin.clear();
							    break;
        case '3': cin.clear();
                  listar(lista_pac);
                  Menu_utente();
                  cin.clear();
                  break;
        case '4': alt_Pac(lista_pac);
                  Menu_utente();
                  cin.clear();
                  break;
        case '5': unsigned long id;                  
                  id = find_id_ut( lista_pac );
                  if ( id == 0 ) 
                    cout << "\nNão foi encontrada um utente com esse nome.\n";
                  else
                    cout << "\nId:" << id << endl;
                  cout << "Enter para continuar...";
                  cin.clear();
                  cin.get();
                  Menu_utente();
                  break;
        default:  cout << "Opção Desconhecida. Insira outra opção.\nEnter para continuar: ";
		              cin.clear();
		              Menu_utente();
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
