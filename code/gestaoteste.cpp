#include "classes/headers/consulta.h"

using namespace std;
int main()
{
 Medico a("ruca", "91542", "Women",0,0);
  Convencao adse("adse", 10),medis("medis",20);
  Data d(29,2,2001);
  try
  {
  int dianovo,mesnovo,anonovo;
  cin >> dianovo >> mesnovo >> anonovo;
     d.setData(dianovo,mesnovo,anonovo);
  }
  catch ( DataImpossivel & dImpossivel) 
  {
     cout << "Ocorreu um erro: "  << dImpossivel.what() << endl;
  }
  cout << d << endl;
  Hora h(23,45);
  Hora s(12,27);
  cout <<"dif entre:" << h << " e " << s <<"= " <<h-s << endl;
/*  int a;
  cin >> a;
  try{
  h.setMin(a);}
    catch(MinImpossivel & moraImpossivel)
  {
   cout << "Erro:"<<moraImpossivel.what() << endl;  
  }
 //if (h==s)
  cout << h <<endl<< endl;
/*  int ano;
  cin >> ano;
  if (bissexto(ano))
  cout << "bissexto\n";
  else
  cout << "não bissexto \n";
  if (adse>medis)
    cout << adse << " tem mais desconto que " << medis << endl;
  else
    cout << adse << " tem menos desconto que " << medis << endl;
  return 0;*/

}
