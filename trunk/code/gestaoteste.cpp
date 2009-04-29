#include "classes/headers/consulta.h"

using namespace std;
int main()
{
  Medico a("ruca", "91542", "Women",0);
  Convencao adse("adse", 10),medis("medis",20);
  cout << a;
  if (adse>medis)
    cout << adse << "tem mais desconto que " << medis << endl;
  else
    cout << adse << "tem menos desconto que " << medis << endl;
  return 0;

}
