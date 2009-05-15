#include "headers/especialidade.h"

Especialidade::Especialidade (string e): nome(e) {}
Especialidade::Especialidade (Especialidade &e) : nome(e.nome) {}
void Especialidade::setNom(string e) {nome = e;}
string Especialidade::getNom() const {return nome;}
