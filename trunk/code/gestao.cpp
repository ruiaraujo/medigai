#include "classes/headers/FileHandling.h"

using namespace std;
int main()
{

  cout << "Medigai\nMedical Management for Linux Lovers.\n";
  string line;
  fstream file("medico.txt");
//  Medico ruca("Ruca", "Women" , "9154244117", 20, 33400);
  //cout << "Addcionado: " << delMed(file, ruca) << endl;
  file.close();

  return 0;
}

