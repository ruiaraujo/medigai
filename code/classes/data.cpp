#include "headers/data.h"

Data::Data (int d = 1, int m = 1, int a = 1970) : dia(d), mes(m), ano(a) {}
Data::Data (Data &d) : dia(d.dia), mes(d.mes), ano(d.ano) {} 
