#include "classes/headers/consulta.h"

using namespace std;
int main()
{
  Medico a("ruca", "91542", "Women",0);
  Convencao adse("adse", 10),medis("medis",20);
  Hora h(23,45);
  Hora s(12,27);
  Hora b(12,27);
  cout << a <<"dif entre:" << h << " e " << s <<"= " <<h-s << endl;
  h = h + 75;
 //if (h==s)
  cout << h <<endl<<  endl;
/*  int ano;
  cin >> ano;
  if (bissexto(ano))
  cout << "bissexto\n";
  else
  cout << "não bissexto \n";*/
  if (adse>medis)
    cout << adse << " tem mais desconto que " << medis << endl;
  else
    cout << adse << " tem menos desconto que " << medis << endl;
  return 0;

}
