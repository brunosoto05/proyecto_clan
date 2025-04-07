#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <string>
#include "nodo.h"
#include "contribuidor.h"

Nodo** cargarFamilia(const std::string& filename, int& count);

void cargarContribuidores(const std::string& filename, Nodo** nodos, int count);

#endif
