#include "classes/MemoryHandling.h"
#include <cstdlib>
#include <curses.h>

using namespace std;

//Variaveis globais
string file_med = "medico.txt",file_pac="utentes.txt";
string file_esp="especialidade.txt",file_con = "consultas.txt"; //nome dos ficheiros para leitura
bool alteracoes = false;


void menu_med();
void menu_utente();
void menu_consulta();
void pauseM();

//Texto dos Menus
void Menu_med();
void Menu_consulta();
void Menu_utente();
void main_menu();
void logotipo();

Clinic clinic( file_med , file_pac , file_esp , file_con);

int main()
{
  string lixo;
  clinic.load();
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
                  clinic.save();
                  alteracoes = false;
                  pauseM();
		              main_menu();
		              break;
        default:  cout << "\nOpção desconhecida.\n";
                  pauseM();
                  cin.clear();
                  main_menu();
		              break;
      }
    }
    main_menu();
  }
  if ( alteracoes )
  {
    cin.clear();
    cout << "Há alterações não guardadas. Deseja guardá-las agora(S/N)?"<<endl;
    cin >> opcao;
    while (opcao != 'S' && opcao != 'N' && opcao != 's' && opcao != 'n' )
    {
      cin >> opcao;
      if ( opcao == 'S' || opcao == 's' )
      {
        cout << "A guardar tudo...\n";
        clinic.save();
      }
      else
        cout << "Opção desconhecida. Insira outra (S/N)." << endl;
      cin.clear();
    }
    
  }
return 0;
}

void logotipo(){

cout<<"******************************************************************************"<<endl;
cout<<"*   __          __   _____   ________  (_)  _______        ______       (_)  *"<<endl;
cout<<"*  |  \\        /  | | ____| |  __    |  _  |  _____|      /  __  \\       _   *"<<endl;
cout<<"*  |  |\\      /|  | | |___  | |  |   | | | | | ____      /  /  \\  \\     | |  *"<<endl;
cout<<"*  |  | \\    / |  | | ____| | |  |   | | | | | |___|    /  /____\\  \\    | |  *"<<endl;
cout<<"*  |  |  \\  /  |  | | |___  | |__|   | | | | |___|_|   /  /______\\  \\   | |  *"<<endl;
cout<<"*  |__|   \\/   |__| |_____| |________| |_| |_______|  /__/        \\__\\  |_|  *"<<endl;
cout<<"*                                                                            *"<<endl; 
cout<<"*                   Medical Management for Linux Lovers.                     *"<<endl;
cout<<"*                                                                            *"<<endl;
cout<<"******************************************************************************"<<endl;

char logotipo[13][80]  ={"*******************************************************************************",
                         "*                                                                             *",
                         "*    ###      ###   ######  ######   ####  ########        #####        ####  *",
                         "*    ## #    # ##   ##      #######   ##   ##             ##   ##        ##   *",
                         "*    ##  #  #  ##   ##      ##    ##  ##   ##            ##     ##       ##   *",
                         "*    ##   ##   ##   ####    ##    ##  ##   ##  ####     ###########      ##   *",
                         "*    ##        ##   ##      ##    ##  ##   ##    ##    #############     ##   *",
                         "*    ##        ##   ##      #######   ##   ##    ##   ##           ##    ##   *",
                         "*   ####      ####  ######  ######   ####  ########  ####         ####  ####  *",
                         "*                                                                             *",
                         "*                    Medical Management for Linux Lovers.                     *",
                         "*                                                                             *",
                         "*******************************************************************************"};

}

void main_menu()
{
  system("clear");
  logotipo();
  cout << "\nMenu:\n\nInsira o número da opção desejada:\n\n1. Corpo Clínico\n2. Gestão de Utentes\n";
  cout << "3. Gestão de Consultas\n4. Guardar as alterações\n";
  cout << "Pressione CRTL-D para sair.\n";
}


void Menu_med()
{
  system("clear");
  logotipo();
  cout << "\nGestão do Corpo Clínico:\n\nInsira o número da opção desejada.\n\n";
  cout << "1. Adicionar Médico\n2. Eliminar Médico\n3. Visualisar os médicos\n4. Visualizar id\n";
  cout << "5. Visualizar preço por minuto"  << endl;  
  cout << "CRTL-D para voltar ao menu anterior.\n";
}
void menu_med()
{
  Menu_med();
  char op;
  vector <Doctor *> ced;
  while ( !cin.eof() )
  {
    cin>>op;
    if ( ! cin.eof() && isdigit( op ) )
    {
      switch(op)
      {
        case '1': cout << endl << endl << "Insira os Dados do Médico.\n";
                  cin.clear();
		              system("clear");
		              logotipo();
		              if ( clinic.insMed() != -1) alteracoes = true;
                  pauseM();
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
                  if ( clinic.delMed ( cedula ) ) alteracoes = true;
                  cin.get();
                  pauseM();
                  Menu_med();
                  break;
        case '3': cout << endl << "Lista de Médicos:" << endl;
                  listar ( clinic.getListMed() );
                  cout << endl;
                  cin.get();
                  pauseM();
                  Menu_med();
                  break;
        case '4': cin.clear();
                  cin.get();
                  ced =  find_Id(clinic.getListMed());
	                if ( ced.empty() )
	                  cout << "\nNão foi encontrada um médico com esse nome.\n";
	                else
	                {
	                  cout << "\nLista de Médicos Possíveis:\n" << endl;
	                  listar( ced );
	                }
	                pauseM();
                  Menu_med();
	                break;
	      case '5': cin.clear();
	                cin.get();
	                clinic.precoMedio();
	                pauseM();
	                Menu_med();
	                break;
	      default:  cout << "\nOpção desconhecida.\n";
	                cin.get();
		              pauseM();
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
  cout << "4. Visualizar Horario\n5. Visualizar Consultas\n6. Ver Consulta\n7. Pagar a consulta." << endl;
  cout << "CRTL-D para voltar ao menu anterior.\n";
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
        	  case '1': system( "clear" );
        	            logotipo();
        	            cout << "Insira os Dados da Consulta.\n";
                 		  if ( clinic.insCon() != -1 ) alteracoes = true;
                 		  Menu_consulta();
				              cin.clear();
				              break;
        		case '2': if ( clinic.altCon() ) alteracoes = true;
        		          pauseM();
		                  Menu_consulta();
		                  break;        
		        case '3': cout << "Insira os dados da Consulta:" << endl;
		                  if ( clinic.delCon() ) alteracoes = true;
		                  Menu_consulta();
		                  cin.clear();
		                  break;       
	  	      case '4': clinic.horario_med();
	  	                pauseM();
	    	              Menu_consulta();
	    	           	  break;
	    	    case '5': cout << "Lista de Consultas:" << endl;
	      	            listar ( clinic.getListCon() );
	      	            pauseM();
      			          Menu_consulta();
                      break; 	
			      case '6': clinic.verCon();
			                pauseM();
			                Menu_consulta();
			                break;
			      case '7': cin.clear();
				              if ( clinic.pagarCon() ) alteracoes = true;
				              pauseM();
	                    Menu_consulta();
	                    break;
      			default:  cout << "\nOpção desconhecida." << endl;
      			          cin.get();
      			          pauseM();
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
  cout << "Menu:\n\nInsira o número da opção desejada:\n\n1. Adicionr Utente\n";
  cout << "2. Eliminar Utente\n3. Visualizar Utentes\n4. Alterar Utente\n5. Visualizar Id.\n";
  cout << "6. Visualizar preço médio por minuto pago"  << endl;  
  cout << "Pressione CRTL-D para voltar ao menu anterior." << endl;
}

void menu_utente()
{
  Menu_utente();
  char op;
  vector<Patient *> id;
  cin.clear();
	while ( !cin.eof() )
	{
	  cin >> op;
		if ( ! cin.eof() && isdigit( op ) )
    {
    switch(op)
      {
        case '1': cin.get();
                  clinic.insPac();
                  Menu_utente();
             		  cin.clear();
             		  break;
        case '2': cin.clear();
                  cin.get();
                  if ( clinic.delPac () ) alteracoes = true;
                  pauseM();
                  Menu_utente();
                  cin.clear();
                  break;
        case '3': cin.clear();
                  cin.get();
                  listar(clinic.getListPac());
                  pauseM();
                  Menu_utente();
                  cin.clear();
                  break;
        case '4': clinic.altPac();
                  Menu_utente();
                  cin.clear();
                  break;
        case '5': cin.get();
                  id = find_Id( clinic.getListPac() );
                  if ( id.empty() ) 
                    cout << "\nNão foi encontrada um utente com esse nome.\n";
                  else
                  {
                    cout << "\nLista de Utentes possíveis:" <<  endl;
                    listar ( id ); 
                  }
                  pauseM();
                  Menu_utente();
                  break;
			  case '6': cin.clear();
	                cin.get();
	                clinic.precoMedioP();
	                pauseM();
	                Menu_utente();
	                break;
        		default:  cout << "Opção Desconhecida." << endl;
        		          cin.get();
        		          pauseM();
		                  Menu_utente();
		                  break;
      }
    }
  }
}

void pauseM()
{
  cin.clear();
  flushinp();
  cout << endl << "Enter para continuar: ";
  cin.get();
}

